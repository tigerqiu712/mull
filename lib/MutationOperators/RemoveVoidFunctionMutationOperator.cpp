#include "MutationOperators/RemoveVoidFunctionMutationOperator.h"
#include "MutationOperators/MutationOperatorFilter.h"

#include "MutationPoint.h"
#include "Context.h"

#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/DebugInfoMetadata.h"

#include <fstream>
#include <iterator>

using namespace llvm;
using namespace mull;

const std::string RemoveVoidFunctionMutationOperator::ID =
  "remove_void_function_mutation_operator";

static int GetFunctionIndex(llvm::Function *function) {
  auto PM = function->getParent();

  auto FII = std::find_if(PM->begin(), PM->end(),
                          [function] (llvm::Function &f) {
                            return &f == function;
                          });

  assert(FII != PM->end() && "Expected function to be found in module");
  int FIndex = std::distance(PM->begin(), FII);

  return FIndex;
}

std::vector<MutationPoint *>
RemoveVoidFunctionMutationOperator::getMutationPoints(const Context &context,
                                                   llvm::Function *function,
                                                   MutationOperatorFilter &filter) {
  int functionIndex = GetFunctionIndex(function);
  int basicBlockIndex = 0;

  std::vector<MutationPoint *> mutationPoints;

  for (auto &basicBlock : function->getBasicBlockList()) {

    int instructionIndex = 0;

    for (auto &instruction : basicBlock.getInstList()) {
      if (canBeApplied(instruction) && !filter.shouldSkipInstruction(&instruction)) {
        auto moduleID = instruction.getModule()->getModuleIdentifier();
        MullModule *module = context.moduleWithIdentifier(moduleID);

        MutationPointAddress address(functionIndex, basicBlockIndex, instructionIndex);
        auto mutationPoint = new MutationPoint(this, address, &instruction, module);
        mutationPoints.push_back(mutationPoint);
      }
      instructionIndex++;
    }
    basicBlockIndex++;
  }

  return mutationPoints;
}

bool RemoveVoidFunctionMutationOperator::canBeApplied(Value &V) {
  if (CallInst *callInst = dyn_cast<CallInst>(&V)) {

    /// How it can be that there is no a called function?
    if (Function *calledFunction = callInst->getCalledFunction()) {
      if (calledFunction->getName().startswith("llvm.dbg.declare")) {
        return false;
      }

      /// TODO: This might also filter out important code. Review this later.
      if (calledFunction->getName().endswith("D1Ev") || calledFunction->getName().endswith("D2Ev") ||
          calledFunction->getName().contains("C1E") || calledFunction->getName().contains("C2E")) {
        return false;
      }

      if (calledFunction->getReturnType()->getTypeID() == Type::VoidTyID) {
        return true;
      }
    }
  }

  return false;
}

llvm::Value *RemoveVoidFunctionMutationOperator::applyMutation(Module *M, MutationPointAddress address, Value &_V) {
  llvm::Function &F    = *(std::next(M->begin(), address.getFnIndex()));
  llvm::BasicBlock &B  = *(std::next(F.begin(), address.getBBIndex()));
  llvm::Instruction &I = *(std::next(B.begin(), address.getIIndex()));

  CallInst *callInst = dyn_cast<CallInst>(&I);
  callInst->eraseFromParent();

  /// return value here is not used and doesn't do anything outside.
  /// TODO: remove?
  return callInst;
}

Value *RemoveVoidFunctionMutationOperator::revertMutation(Value &V)  {
  LLVM_BUILTIN_UNREACHABLE;
  return nullptr;
}
