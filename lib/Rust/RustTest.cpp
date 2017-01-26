#include "Rust/RustTest.h"

using namespace mull;
using namespace std;

RustTest::RustTest(std::string Name,
                   llvm::Function *TestBody,
                   std::vector<llvm::Function *> Ctors) :
  Test(TK_RustTest), TestName(Name), TestBodyFunction(TestBody), GlobalCtors(Ctors)
{
}

std::string RustTest::getTestName() {
  return TestName;
}

std::vector<llvm::Function *> &RustTest::GetGlobalCtors() {
  return GlobalCtors;
}

llvm::Function *RustTest::GetTestBodyFunction() {
  return TestBodyFunction;
}
