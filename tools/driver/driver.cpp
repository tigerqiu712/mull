#include "Driver.h"
#include "ConfigParser.h"
#include "Config.h"
#include "ModuleLoader.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/YAMLParser.h"

using namespace Mutang;
using namespace llvm;

static const char *ExecutionResultToString(ExecutionResult Result) {
  switch (Result) {
    case Failed:
      return "Failed";
    case Passed:
      return "Passed";
    case Invalid:
      llvm_unreachable("Must not reach here");
      break;
  }

  llvm_unreachable("Must not reach here");
}

int main(int argc, char *argv[]) {
  assert(argc == 2);

  ConfigParser Parser;
  auto Cfg = Parser.loadConfig(argv[1]);

  LLVMContext Ctx;
  ModuleLoader Loader(Ctx);

  Driver D(*Cfg.get(), Loader);

  auto Results = D.Run();
  for (auto &R : Results) {

    printf("Result for '%s'\n", R->getTestFunction()->getName().str().c_str());
    printf("\tOriginal test '%s'\n", ExecutionResultToString(R->getOriginalTestResult()));
    printf("\tMutants:\n");

    for (auto &MR : R->getMutationResults()) {
      printf("\t\tMutant '%s'\n", ExecutionResultToString(MR->getExecutionResult()));
    }

  }

  return 0;
}

