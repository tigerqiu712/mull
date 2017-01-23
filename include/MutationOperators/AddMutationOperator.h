#pragma once

#include "MutationOperators/MutationOperator.h"

#include <vector>

namespace mull {

class MutationPoint;
class MutationPointAddress;
class MutationOperatorFilter;

class AddMutationOperator : public MutationOperator {

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
  llvm::Value *revertMutation(llvm::Value &Value) override __attribute__((unavailable));
};

}

