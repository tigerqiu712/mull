#include "Driver.h"

#include "Config.h"
#include "Context.h"
#include "Logger.h"
#include "ModuleLoader.h"
#include "Result.h"
#include "TestResult.h"

#include "llvm/IR/CallSite.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Transforms/Utils/Cloning.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/DebugInfoMetadata.h"

#include "TestFinder.h"
#include "TestRunner.h"

/// FIXME: Should be abstract
#include "MutationOperators/AddMutationOperator.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <map>
#include <set>
#include <vector>

using namespace llvm;
using namespace llvm::object;
using namespace mull;
using namespace std;
using namespace std::chrono;

struct CallTree {
  int depth;
  Function *function;
  vector<unique_ptr<CallTree>> children;

  set<Module *> uniqueModules() {
    set<Module *> modules;
    return uniqueModules(modules);
  }

  set<Module *> uniqueModules(set<Module *> modules) {
    modules.insert(function->getParent());
    for (auto &ct : children) {
      modules = ct->uniqueModules(modules);
    }
    return modules;
  }
};

static set<Function *> functions;

static unique_ptr<CallTree> callTreeForFunction(Context &context, Function *function, int depth) {
  functions.insert(function);

  auto callTree = make_unique<CallTree>();
  callTree->depth = depth;
  callTree->function = function;

  Module *currentModule = function->getParent();

  for (inst_iterator I = inst_begin(function), E = inst_end(function); I != E; ++I) {
    CallSite cs(&*I);
    if (!cs.isCall() && !cs.isInvoke()) {
      continue;
    }

    Function *callee = dyn_cast<Function>(cs.getCalledValue());
    if (!callee) {
      continue;
    }

    if (callee->isDeclaration()) {
      callee = currentModule->getFunction(callee->getName());
      if (callee->isDeclaration()) {
        callee = context.lookupDefinedFunction(callee->getName());
        if (!callee) {
          continue;
        }
      }
    }

    if (functions.find(callee) != functions.end()) {
      continue;
    }

    callTree->children.emplace_back(callTreeForFunction(context, callee, depth + 1));
  }

  return callTree;
}

static void dumpCallTree(CallTree *callTree) {
  Logger::debug().indent(callTree->depth * 2)
    << callTree->function->getName() << "\n";
  Logger::debug().indent(callTree->depth * 2)
    << callTree->function->getParent()->getModuleIdentifier() << "\n";
  for (auto &ct : callTree->children) {
    dumpCallTree(ct.get());
  }

  Logger::debug() << "\n";
}

/// Populate mull::Context with modules using
/// ModulePaths from mull::Config.
/// mull::Context should be populated using ModuleLoader
/// so that we could inject modules from string for testing purposes

/// Having mull::Context in place we could instantiate TestFinder and find all tests
/// Using same TestFinder we could find mutation points, apply them sequentially and
/// run tests/mutants using newly created TestRunner

/// This method should return (somehow) results of the tests/mutants execution
/// So that we could easily plug in some TestReporter

/// UPD: The method returns set of results
/// Number of results equals to a number of tests
/// Each result contains result of execution of an original test and
/// all the results of each mutant within corresponding MutationPoint

std::unique_ptr<Result> Driver::Run() {
  Logger::debug() << "Driver::Run> starting with config:\n"
                  << "\tdistance: " << Cfg.getMaxDistance() << '\n'
                  << "\tdry_run: " << Cfg.isDryRun() << '\n'
                  << "\tfork: " << Cfg.getFork() << '\n';

  std::vector<std::unique_ptr<TestResult>> Results;
  std::vector<std::unique_ptr<Testee>> allTestees;

  /// Assumption: all modules will be used during the execution
  /// Therefore we load them into memory and compile immediately
  /// Later on modules used only for generating of mutants
  for (auto ModulePath : Cfg.getBitcodePaths()) {
    unique_ptr<MullModule> ownedModule = Loader.loadModuleAtPath(ModulePath);
    assert(ownedModule && "Can't load module");
    Ctx.addModule(std::move(ownedModule));
  }

  auto foundTests = Finder.findTests(Ctx);
  const int testsCount = foundTests.size();

  Logger::debug() << "Driver::Run> found "
                  << testsCount
                  << " tests\n";

  vector<unique_ptr<CallTree>> callTrees;

  for (auto &test : foundTests) {
    Function *function = test->getFunction();
    callTrees.emplace_back(callTreeForFunction(Ctx, function, 0));
  }

  Function *testDriver = Ctx.lookupDefinedFunction("_ZN7testing14InitGoogleTestEPiPPc");
  callTrees.emplace_back(callTreeForFunction(Ctx, testDriver, 0));

  Function *errorHack = Ctx.lookupDefinedFunction("_ZN4llvm13ErrorInfoBase6anchorEv");
  callTrees.emplace_back(callTreeForFunction(Ctx, errorHack, 0));

  Function *cliHack = Ctx.lookupDefinedFunction("_ZN4llvm2cl6parserIjE5parseERNS0_6OptionENS_9StringRefES5_Rj");
  callTrees.emplace_back(callTreeForFunction(Ctx, cliHack, 0));

//  Logger::debug() << "\n\n";
//  for (auto &callTree : callTrees) {
//    dumpCallTree(callTree.get());
//  }

  set<Module *> allModules;
  for (auto &callTree : callTrees) {
//    printf("%lu\n", callTree->uniqueModules().size());
    auto modules = callTree->uniqueModules();
    allModules.insert(modules.begin(), modules.end());
  }

  printf("%lu\n", allModules.size());

  for (auto module : allModules) {
    MullModule *mullModule = Ctx.mullModuleForLLVMModule(module);
    ObjectFile *objectFile = toolchain.cache().getObject(*mullModule);

    if (objectFile == nullptr) {
      auto owningObjectFile = toolchain.compiler().compileModule(*mullModule->clone().get());
      objectFile = owningObjectFile.getBinary();
      toolchain.cache().putObject(std::move(owningObjectFile), *mullModule);
    }

    InnerCache.insert(std::make_pair(module, objectFile));
  }

  auto constructors = Ctx.getStaticConstructors(allModules);

//  exit(42);

  int testIndex = 1;
  for (auto &test : foundTests) {
    auto ObjectFiles = AllObjectFiles();

    Logger::debug().indent(4)
      << "Driver::Run> current test "
      << "[" << testIndex++ << "/" << testsCount << "]: "
      << test->getTestName()
      << "\n";

    ExecutionResult ExecResult = Sandbox->run([&](ExecutionResult *SharedResult) {
      *SharedResult = Runner.runTest(test.get(), ObjectFiles, constructors);
    }, Cfg.getTimeout());

    auto BorrowedTest = test.get();
    auto Result = make_unique<TestResult>(ExecResult, std::move(test));

    auto testees = Finder.findTestees(BorrowedTest, Ctx, Cfg.getMaxDistance());

    /// -1 since we are skipping the first testee
    const int testeesCount = testees.size() - 1;

    Logger::debug().indent(4)
      << "Driver::Run> found "
      << testeesCount << " testees\n";

    int testeeIndex = 1;
    for (auto testee_it = std::next(testees.begin()), ee = testees.end();
         testee_it != ee;
         ++testee_it) {

      auto &&testee = *testee_it;

      Logger::debug().indent(8)
        << "Driver::Run::process testee "
        << "[" << testeeIndex++ << "/" << testeesCount << "]: "
        << testee->getTesteeFunction()->getName()
        << ", ";

      auto MPoints = Finder.findMutationPoints(Ctx, *(testee->getTesteeFunction()));
      if (MPoints.empty()) {
        Logger::debug() << "no mutation points, skipping.\n";

        continue;
      }

      Logger::debug() << "against " << MPoints.size() << " mutation points\n";
      Logger::debug().indent(8) << "";

      auto ObjectFiles = AllButOne(testee->getTesteeFunction()->getParent());
      for (auto mutationPoint : MPoints) {
        //        Logger::info() << "\t\t\tDriver::Run::run mutant:" << "\t";
        //        mutationPoint->getOriginalValue()->print(Logger::info());
        //        Logger::info() << "\n";

        Logger::debug() << ".";

        ExecutionResult result;
        bool dryRun = Cfg.isDryRun();
        if (dryRun) {
          result.Status = DryRun;
          result.RunningTime = ExecResult.RunningTime * 10;
        } else {
          ObjectFile *mutant = toolchain.cache().getObject(*mutationPoint);
          if (mutant == nullptr) {
            auto owningObject = mutationPoint->applyMutation(toolchain.compiler());
            mutant = owningObject.getBinary();
            toolchain.cache().putObject(std::move(owningObject), *mutationPoint);
          }
          ObjectFiles.push_back(mutant);

          result = Sandbox->run([&](ExecutionResult *SharedResult) {
            ExecutionResult R = Runner.runTest(BorrowedTest, ObjectFiles, constructors);

            assert(R.Status != ExecutionStatus::Invalid && "Expect to see valid TestResult");

            *SharedResult = R;
          }, ExecResult.RunningTime * 100);
          ObjectFiles.pop_back();

          assert(result.Status != ExecutionStatus::Invalid && "Expect to see valid TestResult");
        }

        auto MutResult = make_unique<MutationResult>(result, mutationPoint, testee.get());
        Result->addMutantResult(std::move(MutResult));
      }

      Logger::debug() << "\n";
    }

    allTestees.insert(allTestees.end(),std::make_move_iterator(testees.begin()),
                      std::make_move_iterator(testees.end()));

    Results.push_back(std::move(Result));
  }

  //  Logger::info() << "Driver::Run::end\n";

  std::unique_ptr<Result> result = make_unique<Result>(std::move(Results),
                                                       std::move(allTestees));

  return result;
}

std::vector<llvm::object::ObjectFile *> Driver::AllButOne(llvm::Module *One) {
  std::vector<llvm::object::ObjectFile *> Objects;

  for (auto &CachedEntry : InnerCache) {
    if (One != CachedEntry.first) {
      Objects.push_back(CachedEntry.second);
    }
  }

  return Objects;
}

std::vector<llvm::object::ObjectFile *> Driver::AllObjectFiles() {
  std::vector<llvm::object::ObjectFile *> Objects;

  for (auto &CachedEntry : InnerCache) {
    Objects.push_back(CachedEntry.second);
  }

  return Objects;
}

#pragma mark - Debug

void Driver::debug_PrintTestNames() {
  for (auto ModulePath : Cfg.getBitcodePaths()) {
    auto OwnedModule = Loader.loadModuleAtPath(ModulePath);
//    assert(OwnedModule && "Can't load module");
//    Ctx.addModule(std::move(OwnedModule));
  }

  for (auto &Test : Finder.findTests(Ctx)) {
    Logger::info() << Test->getTestName() << "\n";
  }
}

void Driver::debug_PrintTesteeNames() {
  for (auto ModulePath : Cfg.getBitcodePaths()) {
    auto OwnedModule = Loader.loadModuleAtPath(ModulePath);
//    assert(OwnedModule && "Can't load module");
//    Ctx.addModule(std::move(OwnedModule));
  }

  for (auto &Test : Finder.findTests(Ctx)) {
    Logger::info() << Test->getTestName() << "\n";
    for (auto &testee : Finder.findTestees(Test.get(), Ctx, Cfg.getMaxDistance())) {
      Logger::info().indent(2) << testee.get()->getTesteeFunction()->getName() << "\n";
    }
  }
}

void Driver::debug_PrintMutationPoints() {
  for (auto ModulePath : Cfg.getBitcodePaths()) {
    auto OwnedModule = Loader.loadModuleAtPath(ModulePath);
//    assert(OwnedModule && "Can't load module");
//    Ctx.addModule(std::move(OwnedModule));
  }

  for (auto &Test : Finder.findTests(Ctx)) {
    Logger::info() << Test->getTestName() << "\n";
    for (auto &testee: Finder.findTestees(Test.get(), Ctx, Cfg.getMaxDistance())) {
      auto MPoints = Finder.findMutationPoints(Ctx, *(testee.get()->getTesteeFunction()));
      if (MPoints.size()) {
        Logger::info().indent(2) << testee.get()->getTesteeFunction()->getName() << "\n";
      }
      for (auto &MPoint : MPoints) {
        Logger::info().indent(4);
        MPoint->getOriginalValue()->print(Logger::info());
        Logger::info() << "\n";

        if (Instruction *I = dyn_cast<Instruction>(MPoint->getOriginalValue())) {
          auto DL = I->getDebugLoc();
          auto Filename = DL->getFilename();
          auto LineNo = DL->getLine();

          std::string line;
          std::ifstream SourceFile(Filename);
          unsigned int curLine = 1;
          if (SourceFile.is_open()) {
            while (!SourceFile.eof()) {
              getline(SourceFile, line);
              if (curLine == LineNo) {
                Logger::info().indent(4) << Filename << ":" << LineNo << '\n';
                Logger::info().indent(4) << line << ":" << LineNo << '\n';
                break;
              }
              curLine++;
            }
            SourceFile.close();
          } else {
            Logger::error() << "Unable to open file";
          }
        }
      }
    }
  }
}
