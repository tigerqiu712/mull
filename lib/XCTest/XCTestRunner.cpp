#include "XCTest/XCTestRunner.h"


#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/OrcMCJITReplacement.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/RTDyldMemoryManager.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/TargetSelect.h"

#include "XCTest/XCTest_Test.h"

#include <chrono>

using namespace Mutang;
using namespace llvm;
using namespace std::chrono;

class MutangResolver : public JITSymbolResolver {
public:

  JITSymbol findSymbol(const std::string &Name) {
    if (auto SymAddr = RTDyldMemoryManager::getSymbolAddressInProcess(Name))
      return JITSymbol(SymAddr, JITSymbolFlags::Exported);
    return JITSymbol(nullptr);
  }

  JITSymbol findSymbolInLogicalDylib(const std::string &Name) {
    return JITSymbol(nullptr);
  }
};

std::string XCTestRunner::MangleName(const llvm::StringRef &Name) {
  std::string MangledName;
  {
    raw_string_ostream Stream(MangledName);
    Mangler.getNameWithPrefix(Stream, Name, TM->createDataLayout());
  }
  return MangledName;
}

void *XCTestRunner::TestFunctionPointer(const llvm::Function &Function) {

  printf("TestFunctionPointer: %s\n", Function.getName().str().c_str());
  //printf("TestFunctionPointer: %s\n", MangleName(Function.getName()).c_str());

  JITSymbol Symbol = ObjectLayer.findSymbol("_MUT_RunXCTests", false);

  void *FPointer = reinterpret_cast<void *>(static_cast<uintptr_t>(Symbol.getAddress()));
  assert(FPointer && "Can't find pointer to function");
  return FPointer;
}

ExecutionResult XCTestRunner::runTest(Test *Test, ObjectFiles &ObjectFiles) {
  assert(isa<XCTest_Test>(Test) && "Supposed to work only with");

  XCTest_Test *xcTest = dyn_cast<XCTest_Test>(Test);

  auto Handle = ObjectLayer.addObjectSet(ObjectFiles,
                                         make_unique<SectionMemoryManager>(),
                                         make_unique<MutangResolver>());
  void *FunctionPointer = TestFunctionPointer(*xcTest->GetTestFunction());

  auto start = high_resolution_clock::now();
  uint64_t result = ((int (*)())(intptr_t)FunctionPointer)();
  auto elapsed = high_resolution_clock::now() - start;

  ExecutionResult Result;
  Result.RunningTime = duration_cast<std::chrono::nanoseconds>(elapsed).count();

  ObjectLayer.removeObjectSet(Handle);

  if (result == 1) {
    Result.Status = ExecutionStatus::Passed;
  } else {
    Result.Status = ExecutionStatus::Failed;
  }

  return Result;
}
