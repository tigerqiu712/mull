#pragma once

#include "Test.h"

namespace llvm {

class Function;

}

namespace Mutang {

class XCTest_Test : public Test {
  llvm::Function *TestFunction;

public:
  XCTest_Test(llvm::Function *Function);

  llvm::Function *GetTestFunction();

  std::string getTestName() override;

  static bool classof(const Test *T) {
    return T->getKind() == TK_XCTest;
  }
};

}
