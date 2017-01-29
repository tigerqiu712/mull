#include "Rust/RustTestFinder.h"

#include "Context.h"
#include "Logger.h"
#include "MutationOperators/MutationOperator.h"
#include "MutationOperators/MutationOperatorFilter.h"

#include "llvm/IR/Constants.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

#include "Rust/RustTest.h"

#include "MutationOperators/AddMutationOperator.h"
#include "MutationOperators/NegateConditionMutationOperator.h"
#include "MutationOperators/RemoveVoidFunctionMutationOperator.h"

#include <queue>
#include <set>
#include <vector>

#include <cxxabi.h>

using namespace mull;
using namespace llvm;

class RustTestMutationOperatorFilter : public MutationOperatorFilter {
public:
  bool shouldSkipInstruction(llvm::Instruction *instruction) {
//    if (instruction->hasMetadata()) {
//      int debugInfoKindID = 0;
//      MDNode *debug = instruction->getMetadata(debugInfoKindID);
//
//      DILocation *location = dyn_cast<DILocation>(debug);
//      if (location) {
//        if (location->getFilename().str().find("include/c++/v1") != std::string::npos) {
//          return true;
//        }
//      }
//    }

    return false;
  };
};


RustTestFinder::RustTestFinder() : TestFinder() {
  /// FIXME: should come from outside
  mutationOperators.emplace_back(make_unique<AddMutationOperator>());
//  mutationOperators.emplace_back(make_unique<NegateConditionMutationOperator>());
//  mutationOperators.emplace_back(make_unique<RemoveVoidFunctionMutationOperator>());
}

/// The algorithm is the following:
///
/// Each test has an instance of type TestInfo associated with it
/// This instance is stored in a static variable
/// Before program starts this variable gets instantiated by registering
/// in the system.
///
/// The registration made by the following function:
///
///    TestInfo* internal::MakeAndRegisterTestInfo(
///              const char* test_case_name, const char* name,
///              const char* type_param,
///              const char* value_param,
///              internal::TypeId fixture_class_id,
///              Test::SetUpTestCaseFunc set_up_tc,
///              Test::TearDownTestCaseFunc tear_down_tc,
///              internal::TestFactoryBase* factory);
///
/// Here we particularly interested in the values of `test_case_name` and `name`
/// Note:
///   Values `type_param` and `value_param` are also important,
///   but ignored for the moment because we do not support Typed and
///   Value Parametrized tests yet.
///
/// To extract this information we need to find a global
/// variable of type `class.testing::TestInfo`, then find its usage (it used
/// only once), from this usage extract a call to
/// function `MakeAndRegisterTestInfo`, from the call extract values of
/// first and second parameters.
/// Concatenation of thsi parameters is exactly the test name.
/// Note: except of Typed and Value Prametrized Tests
///

std::vector<std::unique_ptr<Test>> RustTestFinder::findTests(Context &Ctx) {
  std::vector<std::unique_ptr<Test>> tests;

  for (auto &module : Ctx.getModules()) {
    auto &x = module->getModule()->getFunctionList();
    for (auto &Fn : x) {
      //Logger::info() << "RustTestFinder::findTests()> found function: "
      //  << Fn.getName() << '\n';

      if (Fn.getName().str().find("rusttest_") != std::string::npos) {
        Logger::info() << "RustTestFinder::findTests - found test: "
        << Fn.getName() << '\n';

        tests.push_back(make_unique<RustTest>(Fn.getName(), &Fn));
      }
    }
  }

  return tests;
}

static bool shouldSkipDefinedFunction(llvm::Function *definedFunction) {
  // _ZN3std9panicking11begin_panic17h6c6bf73f39cdbdacE
  if (definedFunction->getName().find(StringRef("begin_panic")) != StringRef::npos) {
    return true;
  }

  return false;
}

std::vector<std::unique_ptr<Testee>>
RustTestFinder::findTestees(Test *Test,
                              Context &Ctx,
                              int maxDistance) {
  RustTest *googleTest = dyn_cast<RustTest>(Test);

  Function *testFunction = googleTest->getFunction();

  std::vector<std::unique_ptr<Testee>> testees;

  std::queue<std::unique_ptr<Testee>> traversees;
  std::set<Function *> checkedFunctions;

  Module *testBodyModule = testFunction->getParent();

  traversees.push(make_unique<Testee>(testFunction, nullptr, nullptr, 0));

  while (!traversees.empty()) {
    std::unique_ptr<Testee> traversee = std::move(traversees.front());
    Testee *traverseePointer = traversee.get();

    traversees.pop();

    Function *traverseeFunction = traversee->getTesteeFunction();
    const int mutationDistance = traversee->getDistance();

    testees.push_back(std::move(traversee));

    /// The function reached the max allowed distance
    /// Hence we don't go deeper
    if (mutationDistance == maxDistance) {
      continue;
    }

    for (auto &BB : *traverseeFunction) {
      for (auto &I : BB) {
        auto *instruction = &I;

        CallInst *callInstruction = dyn_cast<CallInst>(instruction);
        if (callInstruction == nullptr) {
          continue;
        }

        int callOperandIndex = callInstruction->getNumOperands() - 1;
        Value *callOperand = callInstruction->getOperand(callOperandIndex);
        Function *functionOperand = dyn_cast<Function>(callOperand);

        if (!functionOperand) {
          continue;
        }

        /// Two modules may have static function with the same name, e.g.:
        ///
        ///   // ModuleA
        ///   define range() {
        ///     // ...
        ///   }
        ///
        ///   define test_A() {
        ///     call range()
        ///   }
        ///
        ///   // ModuleB
        ///   define range() {
        ///     // ...
        ///   }
        ///
        ///   define test_B() {
        ///     call range()
        ///   }
        ///
        /// Depending on the order of processing either `range` from `A` or `B`
        /// will be added to the `context`, hence we may find function `range`
        /// from module `B` while processing body of the `test_A`.
        /// To avoid this problem we first look for function inside of a current
        /// module.
        ///
        /// FIXME: Context should report if a function being added already exist
        /// FIXME: What other problems such behaviour may bring?

        Function *definedFunction =
        testBodyModule->getFunction(functionOperand->getName());

        if (!definedFunction || definedFunction->isDeclaration()) {
          definedFunction =
          Ctx.lookupDefinedFunction(functionOperand->getName());
        } else {
//          Logger::debug() << "RustTestFinder> did not find a function: "
//                          << definedFunction->getName() << '\n';
        }

        if (definedFunction) {
          auto functionWasNotProcessed =
          checkedFunctions.find(definedFunction) == checkedFunctions.end();
          checkedFunctions.insert(definedFunction);

          if (functionWasNotProcessed) {
            /// Filtering
            if (shouldSkipDefinedFunction(definedFunction)) {
              continue;
            }

            /// The code below is not actually correct
            /// For each C++ constructor compiler can generate up to three
            /// functions*. Which means that the distance might be incorrect
            /// We need to find a clever way to fix this problem
            ///
            /// * Here is a good overview of what's going on:
            /// http://stackoverflow.com/a/6921467/829116
            ///
            traversees.push(make_unique<Testee>(definedFunction,
                                                callInstruction,
                                                traverseePointer,
                                                mutationDistance + 1));
          }
        }
      }
    }
  }
  
  return testees;
}

std::vector<MutationPoint *>
RustTestFinder::findMutationPoints(const Context &context,
                                     llvm::Function &testee) {

  if (MutationPointsRegistry.count(&testee) != 0) {
    return MutationPointsRegistry.at(&testee);
  }

  std::vector<MutationPoint *> points;

  RustTestMutationOperatorFilter filter;

  for (auto &mutationOperator : mutationOperators) {
    for (auto point : mutationOperator->getMutationPoints(context, &testee, filter)) {
      points.push_back(point);
      MutationPoints.emplace_back(std::unique_ptr<MutationPoint>(point));
    }
  }

  MutationPointsRegistry.insert(std::make_pair(&testee, points));
  return points;
}

std::vector<std::unique_ptr<MutationPoint>> RustTestFinder::findMutationPoints(
                             std::vector<MutationOperator *> &MutationOperators,
                             llvm::Function &F) {
  return std::vector<std::unique_ptr<MutationPoint>>();
}
