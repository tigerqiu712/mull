#pragma once

#include "Test.h"

#include <vector>

namespace llvm {

class Function;

}

namespace mull {

class RustTest : public Test {
  std::string testName;
  llvm::Function *function;
public:
  RustTest(std::string name, llvm::Function *function);

  std::string getTestName() override;

  std::string getUniqueIdentifier() override { return getTestName(); };

  std::vector<llvm::Function *> &GetGlobalCtors();
  llvm::Function *getFunction();

  static bool classof(const Test *T) {
    return T->getKind() == TK_RustTest;
  }
};

}
