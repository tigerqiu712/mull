#pragma once

#include "TestFinder.h"
#include "Test.h"

namespace llvm {

class Function;

}

namespace Mutang {

class Context;
class MutationOperator;
class MutationPoint;

class XCTestFinder : public TestFinder {

public:
  explicit XCTestFinder() {}

  // Finds all methods that start with "test_"
  std::vector<std::unique_ptr<Test>> findTests(Context &Ctx) override;
  std::vector<llvm::Function *> findTestees(Test *Test, Context &Ctx) override;
  std::vector<std::unique_ptr<MutationPoint>> findMutationPoints(
                          std::vector<MutationOperator *> &MutationOperators,
                          llvm::Function &F) override;

private:
  bool isRelevantFunction(llvm::Function *F);

};

}
