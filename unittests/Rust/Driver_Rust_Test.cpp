#include "Config.h"
#include "Context.h"
#include "Driver.h"
#include "ModuleLoader.h"
#include "MutationOperators/AddMutationOperator.h"
#include "MutationOperators/NegateConditionMutationOperator.h"
#include "MutationOperators/RemoveVoidFunctionMutationOperator.h"
#include "Result.h"
#include "Rust/RustTestFinder.h"
#include "Rust/RustTestRunner.h"
#include "XCTest/XCTestFinder.h"
#include "XCTest/XCTestRunner.h"

#include "TestModuleFactory.h"
#include "TestResult.h"

#include "Toolchain/Toolchain.h"

#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/Twine.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/YAMLParser.h"

#include "gtest/gtest.h"

using namespace mull;
using namespace llvm;

static LLVMContext GlobalCtx;

static TestModuleFactory TestModuleFactory;

class FakeRustModuleLoader : public ModuleLoader {
public:
  FakeRustModuleLoader() : ModuleLoader(GlobalCtx) {}

  std::unique_ptr<MullModule> loadModuleAtPath(const std::string &path) override {
    if (path == "swift") {
      auto module = TestModuleFactory.XCTestModule();
      return make_unique<MullModule>(std::move(module), "swift");
    }

    return make_unique<MullModule>(nullptr, "");
  }
};

TEST(Driver_Rust, AddMutationOperator__) {

  /// Create Config with fake BitcodePaths
  /// Create Fake Module Loader
  /// Initialize Driver using ModuleLoader and Config
  /// Driver should initialize (make them injectable? DI?)
  /// TestRunner and TestFinder based on the Config
  /// Then Run all the tests using driver

  std::string projectName("some-project");
  std::string testFramework("Rust");
  std::vector<std::string> ModulePaths({ "swift" });
  bool doFork = true;
  bool dryRun = false;
  bool useCache = false;
  int distance = 10;
  std::string cacheDirectory = "/tmp/mull_cache";

  Config config(projectName,
                testFramework,
                ModulePaths,
                {},
                {},
                {},
                doFork,
                dryRun,
                useCache,
                MullDefaultTimeoutMilliseconds,
                distance,
                cacheDirectory);

  FakeRustModuleLoader loader;

  std::vector<std::unique_ptr<MutationOperator>> mutationOperators;
  mutationOperators.emplace_back(make_unique<AddMutationOperator>());

  XCTestFinder testFinder(std::move(mutationOperators),
                            config.getTests());

  Toolchain toolchain(config);
  llvm::TargetMachine &machine = toolchain.targetMachine();
  XCTestRunner runner(machine);

  Driver Driver(config, loader, testFinder, runner, toolchain);

  auto result = Driver.Run();
}
