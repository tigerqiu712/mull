#include "XCTest/XCTest_Test.h"

#include "llvm/IR/Function.h"

using namespace Mutang;

XCTest_Test::XCTest_Test(llvm::Function *Function) :
  Test(TK_XCTest), TestFunction(Function) {}

llvm::Function *XCTest_Test::GetTestFunction() {
  return TestFunction;
}

std::string XCTest_Test::getTestName() {
  return TestFunction->getName().str();
}
