#include "XCTest/XCTestRunner.h"

#include "Config.h"
#include "Logger.h"
#include "ForkProcessSandbox.h"
#include "XCTest/XCTest_Test.h"

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

class Mull_XCTest_Resolver : public RuntimeDyld::SymbolResolver {
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

XCTestRunner::XCTestRunner(llvm::TargetMachine &machine)
: TestRunner(machine) {
//  -load=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftCore.dylib \
//  -load=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftDarwin.dylib \
//  -load=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftObjectiveC.dylib \
//  -load=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftDispatch.dylib \
//  -load=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftSwiftOnoneSupport.dylib \
//  -load=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftIOKit.dylib \
//  -load=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftCoreGraphics.dylib \
//  -load=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftFoundation.dylib \
//  -load=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftCoreData.dylib \
//  -load=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftXPC.dylib \
//  -load=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftCoreImage.dylib \
//  -load=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftQuartzCore.dylib \
//  -load=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftAppKit.dylib \
//  -load=/Applications/Xcode.app/Contents//Developer/Platforms/MacOSX.platform/Developer/Library/Frameworks/XCTest.framework/XCTest \

assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftCore.dylib"));
assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftDarwin.dylib"));
assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftObjectiveC.dylib"));
assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftDispatch.dylib"));
  assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftSwiftOnoneSupport.dylib"));
  assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftIOKit.dylib"));
  assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftCoreGraphics.dylib"));
  assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftFoundation.dylib"));
  assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftCoreData.dylib"));
  assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftXPC.dylib"));
  assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftCoreImage.dylib"));
  assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftQuartzCore.dylib"));
  assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftAppKit.dylib"));
  assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents//Developer/Platforms/MacOSX.platform/Developer/Library/Frameworks/XCTest.framework/XCTest"));
  assert(!sys::DynamicLibrary::LoadLibraryPermanently("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx/libswiftXCTest.dylib"));


}

void *XCTestRunner::FunctionPointer(const char *functionName) {
  orc::JITSymbol symbol = objectLayer.findSymbol(functionName, false);

  void *FPointer =
  reinterpret_cast<void *>(static_cast<uintptr_t>(symbol.getAddress()));

  assert(FPointer && "Can't find pointer to function");

  return FPointer;
}

ExecutionResult XCTestRunner::runTest(Test *Test, ObjectFiles &objectFiles) {
  XCTest_Test *concreteTest = dyn_cast<XCTest_Test>(Test);

  auto handle = objectLayer.addObjectSet(objectFiles,
                                         make_unique<SectionMemoryManager>(),
                                         make_unique<Mull_XCTest_Resolver>());

  auto start = high_resolution_clock::now();

  printf("HELLO111111\n");

  void *mainPointer = FunctionPointer("_main");

  auto main = ((int (*)(int, const char **))(intptr_t)mainPointer);
  const int argc = 1;
  const char *argv[] = { "mull", NULL };
  auto res = main(argc, argv);

  auto elapsed = high_resolution_clock::now() - start;

  ExecutionResult Result;
  Result.Status = Passed;
  Result.RunningTime = duration_cast<std::chrono::milliseconds>(elapsed).count();

  objectLayer.removeObjectSet(handle);
  
  return Result;
}
