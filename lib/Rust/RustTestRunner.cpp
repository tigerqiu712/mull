#include "Rust/RustTestRunner.h"

#include "Rust/RustTest.h"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/OrcMCJITReplacement.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/RTDyldMemoryManager.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/TargetSelect.h"

#include <chrono>
#include <execinfo.h>

using namespace mull;
using namespace llvm;
using namespace std::chrono;

class Mull_Rust_Resolver : public RuntimeDyld::SymbolResolver {
public:

  RuntimeDyld::SymbolInfo findSymbol(const std::string &Name) {
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

ExecutionResult RustTestRunner::runTest(Test *Test, ObjectFiles &ObjectFiles) {

  //printf("%llu %s\n", result, GTest->getTestName().c_str());

  ExecutionResult Result;
//  Result.RunningTime = duration_cast<std::chrono::milliseconds>(elapsed).count();
//
//  ObjectLayer.removeObjectSet(Handle);
//
//  if (result == 0) {
//    Result.Status = ExecutionStatus::Passed;
//  } else {
//    Result.Status = ExecutionStatus::Failed;
//  }

  return Result;
}
