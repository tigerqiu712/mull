#pragma once

#include <string>

namespace llvm {
  class Function;
}

namespace mull {

class Test {
public:
  virtual std::string getTestName() = 0;
  virtual std::string getUniqueIdentifier() = 0;
  virtual ~Test() {}

  enum TestKind {
    TK_SimpleTest,
    TK_GoogleTest
  };
  TestKind getKind() const { return Kind; }
  Test(TestKind K) : Kind(K) {}

  virtual llvm::Function *getFunction() { return nullptr; }
private:
  const TestKind Kind;
};

}
