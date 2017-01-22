#include "GoogleTest/GoogleTestFinder.h"

#include "Context.h"
#include "MutationOperators/AddMutationOperator.h"
#include "MutationOperators/NegateConditionMutationOperator.h"
#include "MutationOperators/RemoveVoidFunctionMutationOperator.h"
#include "TestModuleFactory.h"
#include "GoogleTest/GoogleTest_Test.h"

#include "llvm/IR/CallSite.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/SourceMgr.h"

#include "gtest/gtest.h"

using namespace mull;
using namespace llvm;

static TestModuleFactory TestModuleFactory;

TEST(GoogleTestFinder, FindTest) {
  auto ModuleWithTests       = TestModuleFactory.createGoogleTestTesterModule();
  auto mullModuleWithTests = make_unique<MullModule>(std::move(ModuleWithTests), "");

  Context Ctx;
  Ctx.addModule(std::move(mullModuleWithTests));
  
  std::vector<std::unique_ptr<MutationOperator>> mutationOperators;
  mutationOperators.emplace_back(make_unique<AddMutationOperator>());
  mutationOperators.emplace_back(make_unique<NegateConditionMutationOperator>());
  mutationOperators.emplace_back(make_unique<RemoveVoidFunctionMutationOperator>());
  GoogleTestFinder Finder(std::move(mutationOperators));

  auto tests = Finder.findTests(Ctx);

  ASSERT_EQ(1U, tests.size());

  GoogleTest_Test *Test = dyn_cast<GoogleTest_Test>(tests.begin()->get());

  ASSERT_EQ("Hello.world", Test->getTestName());
}

TEST(GoogleTestFinder, DISABLED_FindTestee) {
  auto ModuleWithTests   = TestModuleFactory.createGoogleTestTesterModule();

  auto ModuleWithTestees = TestModuleFactory.createGoogleTestTesteeModule();

  auto mullModuleWithTests   = make_unique<MullModule>(std::move(ModuleWithTests), "");
  auto mullModuleWithTestees = make_unique<MullModule>(std::move(ModuleWithTestees), "");

  Context Ctx;
  Ctx.addModule(std::move(mullModuleWithTests));
  Ctx.addModule(std::move(mullModuleWithTestees));
  
  std::vector<std::unique_ptr<MutationOperator>> mutationOperators;
  mutationOperators.emplace_back(make_unique<AddMutationOperator>());
  mutationOperators.emplace_back(make_unique<NegateConditionMutationOperator>());
  mutationOperators.emplace_back(make_unique<RemoveVoidFunctionMutationOperator>());
  GoogleTestFinder Finder(std::move(mutationOperators));
  
  auto Tests = Finder.findTests(Ctx);

  ASSERT_NE(0u, Tests.size());

  auto &Test = *(Tests.begin());

  std::vector<std::unique_ptr<Testee>> Testees = Finder.findTestees(Test.get(), Ctx, 4);

  ASSERT_EQ(1U, Testees.size());

  Function *Testee = Testees[0]->getTesteeFunction();
  ASSERT_FALSE(Testee->empty());
}

TEST(GoogleTestFinder, DISABLED_FindMutationPoints) {
  auto ModuleWithTests   = TestModuleFactory.createTesterModule();
  auto ModuleWithTestees = TestModuleFactory.createTesteeModule();

  auto mullModuleWithTests   = make_unique<MullModule>(std::move(ModuleWithTests), "");
  auto mullModuleWithTestees = make_unique<MullModule>(std::move(ModuleWithTestees), "");

  Context Ctx;
  Ctx.addModule(std::move(mullModuleWithTests));
  Ctx.addModule(std::move(mullModuleWithTestees));

  std::vector<std::unique_ptr<MutationOperator>> mutationOperators;
  mutationOperators.emplace_back(make_unique<AddMutationOperator>());
  mutationOperators.emplace_back(make_unique<NegateConditionMutationOperator>());
  mutationOperators.emplace_back(make_unique<RemoveVoidFunctionMutationOperator>());
  GoogleTestFinder Finder(std::move(mutationOperators));
  
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
