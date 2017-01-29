#include "Rust/RustTestRunner.h"

#include "ForkProcessSandbox.h"
#include "Rust/RustTest.h"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/OrcMCJITReplacement.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/RTDyldMemoryManager.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/TargetSelect.h"

#include <chrono>
#include <dlfcn.h>
#include <execinfo.h>

using namespace mull;
using namespace llvm;
using namespace std::chrono;

extern "C" void mull_rust_exit(char *first, void *second) {
  printf("mull_rust_exit\n");
}

extern "C" int mull_rust_exit2(int code) {

  printf("mull_rust_exit2\n");

  exit(10);
}

class Mull_Rust_Resolver : public RuntimeDyld::SymbolResolver {
public:

  RuntimeDyld::SymbolInfo findSymbol(const std::string &Name) {
//    printf("OOOOO %s\n", Name.c_str());
//
//    if (Name == "__ZN3std9panicking20rust_panic_with_hook17h33761bada49f3713E") {
//      return findSymbol("mull_rust_exit");
//    }

    if (Name == "__exit") {
      return findSymbol("mull_rust_exit2");
    }

    if (auto SymAddr = RTDyldMemoryManager::getSymbolAddressInProcess(Name)) {
      return RuntimeDyld::SymbolInfo(SymAddr, JITSymbolFlags::Exported);
    }

    return RuntimeDyld::SymbolInfo(nullptr);
  }

  RuntimeDyld::SymbolInfo findSymbolInLogicalDylib(const std::string &Name) {
    return RuntimeDyld::SymbolInfo(nullptr);
  }
};

RustTestRunner::RustTestRunner(llvm::TargetMachine &machine)
  : TestRunner(machine) {}

void *RustTestRunner::FunctionPointer(const char *functionName) {
  orc::JITSymbol symbol = objectLayer.findSymbol(functionName, false);

  void *FPointer =
    reinterpret_cast<void *>(static_cast<uintptr_t>(symbol.getAddress()));

  assert(FPointer && "Can't find pointer to function");

  return FPointer;
}

ExecutionResult RustTestRunner::runTest(Test *Test, ObjectFiles &objectFiles) {
  auto handle = objectLayer.addObjectSet(objectFiles,
                                         make_unique<SectionMemoryManager>(),
                                         make_unique<Mull_Rust_Resolver>());

  auto start = high_resolution_clock::now();

  const char rustLib1_handle_path[] =
    "/Users/Stanislaw/.rustup/toolchains/nightly-x86_64-apple-darwin/lib/libstd-a260b5db713b337f.dylib";
  const char rustLib2_handle_path[] =
  "/Users/Stanislaw/.rustup/toolchains/nightly-x86_64-apple-darwin/lib/libtest-551a7b69d9c2ff2f.dylib";

  __unused void *rustLib1_handle = dlopen(rustLib1_handle_path, RTLD_LAZY|RTLD_GLOBAL);
  if (!rustLib1_handle) {
    printf("---- %s\n", dlerror());

    exit(1);
  }
  __unused void *rustLib2_handle = dlopen(rustLib2_handle_path, RTLD_LAZY|RTLD_GLOBAL);
  if (!rustLib1_handle) {
    printf("---- %s\n", dlerror());

    exit(1);
  }

  ForkProcessSandbox sandbox;
  ExecutionResult rustTestsExecutionResult =
    sandbox.run([&](ExecutionResult *SharedResult) {
      void *mainPtr = FunctionPointer("_main");

      auto mainFunction = ((int (*)())(intptr_t)mainPtr);
        __unused auto res = mainFunction();

      SharedResult->Status = Passed;
  }, 10);

  printf("BURRRR %d\n", rustTestsExecutionResult.Status);

  auto elapsed = high_resolution_clock::now() - start;

  ExecutionResult finalResult;
  finalResult.RunningTime = duration_cast<std::chrono::milliseconds>(elapsed).count();
  finalResult.Status = rustTestsExecutionResult.Status;

  objectLayer.removeObjectSet(handle);

  return finalResult;
}
