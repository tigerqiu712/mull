#pragma once

#include "MutationOperators/MutationOperator.h"

#include <vector>

enum AND_OR_MutationType {
  AND_OR_MutationType_None = 0,
  AND_OR_MutationType_AND_to_OR = 1,
  AND_OR_MutationType_OR_to_AND = 2
};

namespace llvm {
  class BasicBlock;
  class BranchInst;
}

using namespace llvm;

namespace mull {

  class MutationPoint;
  class MutationPointAddress;
  class MutationOperatorFilter;

  class AndOrReplacementMutationOperator : public MutationOperator {

    AND_OR_MutationType findPossibleMutationInBranch(BranchInst *branchInst,
                                                     BranchInst **secondBranchInst);

    llvm::Value *applyMutationANDToOR(Module *M,
                                      BranchInst *firstBranch,
                                      BranchInst *secondBranch);

    llvm::Value *applyMutationORToAND(Module *M,
                                      BranchInst *firstBranch,
                                      BranchInst *secondBranch);

  public:
    static const std::string ID;

    std::vector<MutationPoint *> getMutationPoints(const Context &context,
                                                   llvm::Function *function,
                                                   MutationOperatorFilter &filter) override;

    std::string uniqueID() override {
      return ID;
    }
    std::string uniqueID() const override {
      return ID;
    }

    bool canBeApplied(llvm::Value &V) override;
    llvm::Value *applyMutation(llvm::Module *M, MutationPointAddress address, llvm::Value &OriginalValue) override;
  };
}
