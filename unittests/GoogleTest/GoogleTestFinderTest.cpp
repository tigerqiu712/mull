#include "GoogleTest/GoogleTestFinder.h"

#include "Context.h"
#include "MutationOperators/AddMutationOperator.h"
#include "TestModuleFactory.h"
#include "GoogleTest/GoogleTest_Test.h"

#include "llvm/IR/CallSite.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/SourceMgr.h"

#include "gtest/gtest.h"

using namespace Mutang;
using namespace llvm;

static TestModuleFactory TestModuleFactory;

TEST(GoogleTestFinder, FindTest) {
  LLVMContext context;
  ModuleLoader loader(context);
  auto mutangModuleWithTests = loader.loadModuleAtPath(TestModuleFactory.googleTestTester_Bitcode_Path());

  Context Ctx;
  Ctx.addModule(std::move(mutangModuleWithTests));

  GoogleTestFinder finder;

  auto tests = finder.findTests(Ctx);

  ASSERT_EQ(1U, tests.size());

  GoogleTest_Test *Test = dyn_cast<GoogleTest_Test>(tests.begin()->get());

  ASSERT_EQ("Hello.sup", Test->getTestName());
}

TEST(GoogleTestFinder, FindTestee) {
  LLVMContext context;
  ModuleLoader loader(context);
  auto mutangModuleWithTests = loader.loadModuleAtPath(TestModuleFactory.googleTestTester_Bitcode_Path());
  auto mutangModuleWithTestees = loader.loadModuleAtPath(TestModuleFactory.googleTestTestee_Bitcode_Path());

  Context Ctx;
  Ctx.addModule(std::move(mutangModuleWithTests));
  Ctx.addModule(std::move(mutangModuleWithTestees));

  GoogleTestFinder Finder;
  auto Tests = Finder.findTests(Ctx);

  ASSERT_NE(0u, Tests.size());

  auto &Test = *(Tests.begin());

  std::vector<std::unique_ptr<Testee>> allTestees = Finder.findTestees(Test.get(), Ctx, 5);

  ASSERT_EQ(6U, allTestees.size());

  for (auto &testee: allTestees) {
    printf("Hello: %s\n", testee->getTesteeFunction()->getName().str().c_str());
  }

  Testee *testee1 = allTestees[0].get();
  Testee *testee2 = allTestees[1].get();
  Testee *testee3 = allTestees[2].get();
  Testee *testee4 = allTestees[3].get();
  Testee *testee5 = allTestees[4].get();
  Testee *testee6 = allTestees[5].get();

  ASSERT_EQ(testee6->
            getCallerTestee(), testee5);
  ASSERT_EQ(testee5->
            getCallerTestee(), testee4);
  ASSERT_EQ(testee4->
            getCallerTestee(), testee3);
  ASSERT_EQ(testee3->
            getCallerTestee(), testee2);
  ASSERT_EQ(testee2->
            getCallerTestee(), testee1);
  ASSERT_EQ(testee1->
            getCallerTestee(), nullptr);
}

TEST(GoogleTestFinder, DISABLED_FindMutationPoints) {
  auto ModuleWithTests   = TestModuleFactory.createTesterModule();
  auto ModuleWithTestees = TestModuleFactory.createTesteeModule();

  auto mutangModuleWithTests   = make_unique<MutangModule>(std::move(ModuleWithTests), "");
  auto mutangModuleWithTestees = make_unique<MutangModule>(std::move(ModuleWithTestees), "");

  Context Ctx;
  Ctx.addModule(std::move(mutangModuleWithTests));
  Ctx.addModule(std::move(mutangModuleWithTestees));

  GoogleTestFinder Finder;
  auto Tests = Finder.findTests(Ctx);

  ASSERT_NE(0u, Tests.size());

  auto &Test = *Tests.begin();

  std::vector<std::unique_ptr<Testee>> Testees = Finder.findTestees(Test.get(), Ctx, 4);

  ASSERT_EQ(1U, Testees.size());

  Function *Testee = Testees[0]->getTesteeFunction();
  ASSERT_FALSE(Testee->empty());

  AddMutationOperator MutOp;
  std::vector<MutationOperator *> MutOps({&MutOp});

  std::vector<std::unique_ptr<MutationPoint>> MutationPoints = Finder.findMutationPoints(MutOps, *Testee);
  ASSERT_EQ(1U, MutationPoints.size());

  MutationPoint *MP = (*(MutationPoints.begin())).get();
  ASSERT_EQ(&MutOp, MP->getOperator());
  ASSERT_TRUE(isa<BinaryOperator>(MP->getOriginalValue()));

  MutationPointAddress MPA = MP->getAddress();
  ASSERT_TRUE(MPA.getFnIndex() == 0);
  ASSERT_TRUE(MPA.getBBIndex() == 2);
  ASSERT_TRUE(MPA.getIIndex() == 1);
}
