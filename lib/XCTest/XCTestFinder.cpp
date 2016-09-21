#include "XCTest/XCTestFinder.h"

#include "Context.h"
#include "MutationPoint.h"

#include "MutationOperators/MutationOperator.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/IR/CallSite.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Debug.h"

#include "XCTest/XCTest_Test.h"

#include <algorithm>
#include <cassert>
#include <vector>

using namespace Mutang;
using namespace llvm;

bool XCTestFinder::isRelevantFunction(Function *F) {

  /// Skips XCTest methods:
  /// _XCTFailureHandler
  /// _XCTFailureFormat
  if (F->getName().find("XCT") != StringRef::npos) {
    //printf("skipping XCTest function\n");

    return false;
  }

  /// Skips LLVM methods:
  /// llvm.stackprotector
  if (F->getName().find("llvm") != StringRef::npos) {
    //printf("skipping llvm function\n");

    return false;
  }

  /// Skips Objective-C system methods:
  /// objc_begin_catch
  /// objc_end_catch
  /// objc_exception_rethrow
  /// __objc_personality_v0
  /// objc_msgSend
  /// objc_terminate
  /// objc_msgSendSuper2
  if (F->getName().find("objc") != StringRef::npos) {
    //printf("skipping objc function\n");

    return false;
  }

  return true;
}

std::vector<std::unique_ptr<Test>> XCTestFinder::findTests(Context &Ctx) {
  std::vector<std::unique_ptr<Test>> tests;

  for (auto &M : Ctx.getModules()) {
    auto &x = M->getFunctionList();
    for (auto &Fn : x) {
      printf("XCTestFinder::findTests, looking at function: %s\n", Fn.getName().str().c_str());

      if (isRelevantFunction(&Fn) == false) {
        continue;
      }

      /// TODO: The best way would be to look directly in XCTestCase subclasses
      if (Fn.getName().find("test") != StringRef::npos) {
        printf("XCTestFinder::findTests, found test function: %s\n", Fn.getName().str().c_str());

        tests.emplace_back(make_unique<XCTest_Test>(&Fn));
      }
    }
  }

  return tests;
}

std::vector<Function *> XCTestFinder::findTestees(Test *Test, Context &Ctx) {
  XCTest_Test *XCTest = dyn_cast<XCTest_Test>(Test);

  Function &TestFunction = *(XCTest->GetTestFunction());
  printf("XCTestFinder::findTestees, starting for test function: %s\n", TestFunction.getName().str().c_str());

  std::vector<Function *> testees;

  for (inst_iterator I = inst_begin(TestFunction), E = inst_end(TestFunction); I != E; ++I) {
    Instruction *Inst = &*I;
    if (auto CS = CallSite(Inst)) {
      Function *F = CS.getCalledFunction();

      if (F == NULL) {
        /// indirect call
        /// http://stackoverflow.com/questions/11686951/how-can-i-get-function-name-from-callinst-in-llvm

        continue;
      }

      if (isRelevantFunction(F) == false) {
        continue;
      }

      /// FIXME: Export all declared functions to external registry
      /// while looking for tests
      for (auto &M : Ctx.getModules()) {
        for (auto &Fn : M->getFunctionList()) {
          if (isRelevantFunction(&Fn) == false) {
            continue;
          }

          if (Fn.getName() == F->getName()) {
            if (!Fn.empty()) {
              testees.push_back(&Fn);
            } else {
              llvm_unreachable("Should not reach here: got empty testee function!");
            }
          }
        }
      }

    }
  }

  return testees;
}

std::vector<std::unique_ptr<MutationPoint>> XCTestFinder::findMutationPoints(
                          std::vector<MutationOperator *> &MutationOperators,
                          llvm::Function &F) {
  std::vector<std::unique_ptr<MutationPoint>> MutPoints;


  Module *PM = F.getParent();

  auto FII = std::find_if(PM->begin(), PM->end(),
                          [&F] (llvm::Function &f) {
                            return &f == &F;
                          });

  assert(FII != PM->end() && "Expected function to be found in module");
  int FIndex = std::distance(PM->begin(), FII);

  for (Function::iterator B = F.begin(), E = F.end(); B != E; ++B) {
    BasicBlock &BB = *B;

    for (BasicBlock::iterator I = BB.begin(), E = BB.end(); I != E; ++I) {
      Instruction &Instr = *I;

      for (auto &MutOp : MutationOperators) {
        if (MutOp->canBeApplied(Instr)) {
          BasicBlock *BB = Instr.getParent();

          auto BII = std::find_if(F.begin(), F.end(),
                                  [&BB] (llvm::BasicBlock &bb) {
                                    return &bb == BB;
                                  });
          assert(BII != F.end() && "Expected block to be found in function");

          int BBIndex = std::distance(F.begin(), BII);

          int IIndex = std::distance(B->begin(), I);

          MutationPointAddress Address(FIndex, BBIndex, IIndex);

          MutPoints.emplace_back(make_unique<MutationPoint>(MutOp, Address, &Instr));
        }
      }
    }
  }

  return MutPoints;
}
