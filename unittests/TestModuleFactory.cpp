
#include "TestModuleFactory.h"

#include "llvm/AsmParser/Parser.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/SourceMgr.h"

#include <iostream>

static LLVMContext GlobalCtx;

static std::unique_ptr<Module> parseIR(const char *IR) {
  SMDiagnostic Err;
  auto M = parseAssemblyString(IR, Err, GlobalCtx);

  /// FIXME: is there another way to check for errors?
  if (Err.getMessage().empty() == false) {
    Err.print("test", dbgs());
  }

  assert(M && "Expected module to be parsed correctly");

  return M;
}

std::unique_ptr<Module> TestModuleFactory::createTesterModule() {
    auto module = parseIR("@.str = private unnamed_addr constant [6 x i8] c\"ababa\\00\", align 1 \n"
                          "define i32 @test_count_letters() { \n"
                          "entry: \n"
                          "  %call = call i32 @count_letters(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i32 0, i32 0), i8 signext 97) \n"
                          "  %cmp = icmp eq i32 %call, 3 \n"
                          "  %conv = zext i1 %cmp to i32 \n"
                          "  ret i32 %conv \n"
                          "} \n"
                          ""
                          "declare i32 @count_letters(i8*, i8 signext) \n");

    return module;
}

std::unique_ptr<Module> TestModuleFactory::createTesteeModule() {
    auto module = parseIR("define i32 @count_letters(i8* %s, i8 signext %c) {\n"
                          "entry:\n"
                          "  %s.addr = alloca i8*, align 8\n"
                          "  %c.addr = alloca i8, align 1\n"
                          "  %count = alloca i32, align 4\n"
                          "  %found = alloca i8*, align 8\n"
                          "  store i8* %s, i8** %s.addr, align 8\n"
                          "  store i8 %c, i8* %c.addr, align 1\n"
                          "  store i32 0, i32* %count, align 4\n"
                          "  %0 = load i8*, i8** %s.addr, align 8\n"
                          "  store i8* %0, i8** %found, align 8\n"
                          "  br label %while.cond\n"
                          ""
                          "while.cond: ; preds = %while.body, %entry\n"
                          "  %1 = load i8*, i8** %found, align 8\n"
                          "  %2 = load i8, i8* %c.addr, align 1\n"
                          "  %conv = sext i8 %2 to i32\n"
                          "  %call = call i8* @strchr(i8* %1, i32 %conv)\n"
                          "  store i8* %call, i8** %found, align 8\n"
                          "  %tobool = icmp ne i8* %call, null\n"
                          "  br i1 %tobool, label %while.body, label %while.end\n"
                          ""
                          "while.body: ; preds = %while.cond\n"
                          "  %3 = load i32, i32* %count, align 4\n"
                          "  %add = add nsw i32 %3, 1\n"
                          "  store i32 %add, i32* %count, align 4\n"
                          "  %4 = load i8*, i8** %found, align 8\n"
                          "  %add.ptr = getelementptr inbounds i8, i8* %4, i64 1\n"
                          "  store i8* %add.ptr, i8** %found, align 8\n"
                          "  br label %while.cond\n"
                          ""
                          "while.end:  ; preds = %while.cond\n"
                          "  %5 = load i32, i32* %count, align 4\n"
                          "  ret i32 %5\n"
                          "}\n"
                          ""
                          "declare i8* @strchr(i8*, i32)");

    return module;
}

std::unique_ptr<Module> TestModuleFactory::createLibCTesterModule() {
    auto module = parseIR("declare i32 @sum(i32, i32)"
                          "define i32 @test_main() {\n"
                          "entry:\n"
                          "  %result = alloca i32, align 4\n"
                          "  %result_matches = alloca i32, align 4\n"
                          "  %call = call i32 @sum(i32 3, i32 5)\n"
                          "  store i32 %call, i32* %result, align 4\n"
                          "  %0 = load i32, i32* %result, align 4\n"
                          "  %cmp = icmp eq i32 %0, 8\n"
                          "  %conv = zext i1 %cmp to i32\n"
                          "  store i32 %conv, i32* %result_matches, align 4\n"
                          "  %1 = load i32, i32* %result_matches, align 4\n"
                          "  ret i32 %1\n"
                          "}\n");

    return module;
}

std::unique_ptr<Module> TestModuleFactory::createLibCTesteeModule() {
    auto module = parseIR("define i32 @sum(i32 %a, i32 %b) {\n"
                          "entry:\n"
                          "  %a.addr = alloca i32, align 4\n"
                          "  %b.addr = alloca i32, align 4\n"
                          "  store i32 %a, i32* %a.addr, align 4\n"
                          "  store i32 %b, i32* %b.addr, align 4\n"
                          "  %0 = load i32, i32* %a.addr, align 4\n"
                          "  %1 = load i32, i32* %b.addr, align 4\n"
                          "  %add = add nsw i32 %0, %1\n"
                          "  ret i32 %add\n"
                          "}");

    return module;
}

std::unique_ptr<Module> TestModuleFactory::createExternalLibTesterModule() {
    auto module = parseIR("define i32 @test_in_memory_db() #0 {\n"
                          "entry:\n"
                          "  %call = call i32 (...) @in_memory_db()\n"
                          "  %cmp = icmp eq i32 %call, 0\n"
                          "  %conv = zext i1 %cmp to i32\n"
                          "  ret i32 %conv\n"
                          "}\n"
                          ""
                          "declare i32 @in_memory_db(...)\n");

    return module;
}

std::unique_ptr<Module> TestModuleFactory::createExternalLibTesteeModule() {
    auto module = parseIR("%struct.sqlite3 = type opaque\n"
                          ""
                          "@.str = private unnamed_addr constant [9 x i8] c\":memory:\\00\", align 1\n"
                          ""
                          "define i32 @in_memory_db() #0 {\n"
                          "entry:\n"
                          "  %db = alloca %struct.sqlite3*, align 8\n"
                          "  %call = call i32 @sqlite3_open(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str, i32 0, i32 0), %struct.sqlite3** %db)\n"
                          "  ret i32 %call\n"
                          "}\n"
                          ""
                          "declare i32 @sqlite3_open(i8*, %struct.sqlite3**) #1\n");

    return module;
}

std::unique_ptr<Module> TestModuleFactory::createGoogleTestTesterModule() {
  auto module = parseIR("@.str = private unnamed_addr constant [6 x i8] c\"Hello\\00\", align 1 \n"
                        "@.str.1 = private unnamed_addr constant [6 x i8] c\"world\\00\", align 1 \n"

                        "%\"class.testing::internal::TestFactoryImpl\" = type opaque \n"
                        "%\"class.testing::internal::TestFactoryBase\" = type opaque \n"

                        "%\"class.testing::TestInfo\" = type opaque \n"

                        "@_ZN14Hello_world_Test10test_info_E = global %\"class.testing::TestInfo\"* null, align 8 \n"

                        "define void @__cxx_global_var_init() { \n"
                        "entry: \n"
                        "  %call = call i8* @_ZN7testing8internal13GetTestTypeIdEv() \n"
                        "  %call1 = call i8* @_Znwm(i64 8) \n"
                        "  %0 = bitcast i8* %call1 to %\"class.testing::internal::TestFactoryImpl\"* \n"
                        "  call void @_ZN7testing8internal15TestFactoryImplI14Hello_sup_TestEC1Ev(%\"class.testing::internal::TestFactoryImpl\"* %0) \n"
                        "  %1 = bitcast %\"class.testing::internal::TestFactoryImpl\"* %0 to %\"class.testing::internal::TestFactoryBase\"*  \n"
                        "  %call2 = call %\"class.testing::TestInfo\"* @_ZN7testing8internal23MakeAndRegisterTestInfoEPKcS2_S2_S2_PKvPFvvES6_PNS0_15TestFactoryBaseE(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i8* null, i8* null, i8* %call, void ()* @_ZN7testing4Test13SetUpTestCaseEv, void ()* @_ZN7testing4Test16TearDownTestCaseEv, %\"class.testing::internal::TestFactoryBase\"* %1) \n"
                        "  store %\"class.testing::TestInfo\"* %call2, %\"class.testing::TestInfo\"** @_ZN14Hello_world_Test10test_info_E, align 8 \n"
                        "  ret void \n"
                        "}\n"

                        "declare void @_ZN7testing4Test13SetUpTestCaseEv() \n"
                        "declare void @_ZN7testing4Test16TearDownTestCaseEv() \n"
                        "declare i8* @_ZN7testing8internal13GetTestTypeIdEv() \n"
                        "declare void @_ZN7testing8internal15TestFactoryImplI14Hello_sup_TestEC1Ev(%\"class.testing::internal::TestFactoryImpl\"* %this) \n"
                        "declare %\"class.testing::TestInfo\"* @_ZN7testing8internal23MakeAndRegisterTestInfoEPKcS2_S2_S2_PKvPFvvES6_PNS0_15TestFactoryBaseE(i8*, i8*, i8*, i8*, i8*, void ()*, void ()*, %\"class.testing::internal::TestFactoryBase\"*) \n"
                        "declare i8* @_Znwm(i64) \n"

                        "");

  return module;
}

static const char *XCTestDriverBitcode = R"foo(
; ModuleID = 'MUT_XCTestDriver.m'
source_filename = "MUT_XCTestDriver.m"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.11.0"

%0 = type opaque
%1 = type opaque
%2 = type opaque
%3 = type opaque
%4 = type opaque
%5 = type opaque
%6 = type opaque
%7 = type opaque
%8 = type opaque
%struct._objc_typeinfo = type { i8**, i8*, %struct._class_t* }
%struct._class_t = type { %struct._class_t*, %struct._class_t*, %struct._objc_cache*, i8* (i8*, i8*)**, %struct._class_ro_t* }
%struct._objc_cache = type opaque
%struct._class_ro_t = type { i32, i32, i32, i8*, i8*, %struct.__method_list_t*, %struct._objc_protocol_list*, %struct._ivar_list_t*, i8*, %struct._prop_list_t* }
%struct.__method_list_t = type { i32, i32, [0 x %struct._objc_method] }
%struct._objc_method = type { i8*, i8*, i8* }
%struct._objc_protocol_list = type { i64, [0 x %struct._protocol_t*] }
%struct._protocol_t = type { i8*, i8*, %struct._objc_protocol_list*, %struct.__method_list_t*, %struct.__method_list_t*, %struct.__method_list_t*, %struct.__method_list_t*, %struct._prop_list_t*, i32, i32, i8**, i8*, %struct._prop_list_t* }
%struct._ivar_list_t = type { i32, i32, [0 x %struct._ivar_t] }
%struct._ivar_t = type { i64*, i8*, i8*, i32, i32 }
%struct._prop_list_t = type { i32, i32, [0 x %struct._prop_t] }
%struct._prop_t = type { i8*, i8* }
%struct.__NSConstantString_tag = type { i32*, i32, i8*, i64 }
%struct._objc_super = type { i8*, i8* }

@"OBJC_EHTYPE_$__XCTestCaseInterruptionException" = external global %struct._objc_typeinfo
@"OBJC_EHTYPE_$_NSException" = external global %struct._objc_typeinfo
@.str = private unnamed_addr constant [19 x i8] c"MUT_XCTestDriver.m\00", align 1
@"OBJC_CLASS_$_NSString" = external global %struct._class_t
@"OBJC_CLASSLIST_REFERENCES_$_" = private global %struct._class_t* @"OBJC_CLASS_$_NSString", section "__DATA, __objc_classrefs, regular, no_dead_strip", align 8
@__CFConstantStringClassReference = external global [0 x i32]
@.str.1 = private unnamed_addr constant [15 x i8] c"sum(2, 3) == 5\00", section "__TEXT,__cstring,cstring_literals", align 1
@_unnamed_cfstring_ = private constant %struct.__NSConstantString_tag { i32* getelementptr inbounds ([0 x i32], [0 x i32]* @__CFConstantStringClassReference, i32 0, i32 0), i32 1992, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.1, i32 0, i32 0), i64 14 }, section "__DATA,__cfstring", align 8
@OBJC_METH_VAR_NAME_ = private global [18 x i8] c"stringWithFormat:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_SELECTOR_REFERENCES_ = private externally_initialized global i8* getelementptr inbounds ([18 x i8], [18 x i8]* @OBJC_METH_VAR_NAME_, i32 0, i32 0), section "__DATA, __objc_selrefs, literal_pointers, no_dead_strip", align 8
@.str.2 = private unnamed_addr constant [1 x i8] zeroinitializer, section "__TEXT,__cstring,cstring_literals", align 1
@_unnamed_cfstring_.3 = private constant %struct.__NSConstantString_tag { i32* getelementptr inbounds ([0 x i32], [0 x i32]* @__CFConstantStringClassReference, i32 0, i32 0), i32 1992, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.2, i32 0, i32 0), i64 0 }, section "__DATA,__cfstring", align 8
@OBJC_METH_VAR_NAME_.4 = private global [6 x i8] c"raise\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_SELECTOR_REFERENCES_.5 = private externally_initialized global i8* getelementptr inbounds ([6 x i8], [6 x i8]* @OBJC_METH_VAR_NAME_.4, i32 0, i32 0), section "__DATA, __objc_selrefs, literal_pointers, no_dead_strip", align 8
@OBJC_METH_VAR_NAME_.6 = private global [7 x i8] c"reason\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_SELECTOR_REFERENCES_.7 = private externally_initialized global i8* getelementptr inbounds ([7 x i8], [7 x i8]* @OBJC_METH_VAR_NAME_.6, i32 0, i32 0), section "__DATA, __objc_selrefs, literal_pointers, no_dead_strip", align 8
@_objc_empty_cache = external global %struct._objc_cache
@"OBJC_METACLASS_$_NSObject" = external global %struct._class_t
@"OBJC_METACLASS_$_XCTestCase" = external global %struct._class_t
@OBJC_CLASS_NAME_ = private global [8 x i8] c"FooTest\00", section "__TEXT,__objc_classname,cstring_literals", align 1
@"\01l_OBJC_METACLASS_RO_$_FooTest" = private global %struct._class_ro_t { i32 1, i32 40, i32 40, i8* null, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_CLASS_NAME_, i32 0, i32 0), %struct.__method_list_t* null, %struct._objc_protocol_list* null, %struct._ivar_list_t* null, i8* null, %struct._prop_list_t* null }, section "__DATA, __objc_const", align 8
@"OBJC_METACLASS_$_FooTest" = global %struct._class_t { %struct._class_t* @"OBJC_METACLASS_$_NSObject", %struct._class_t* @"OBJC_METACLASS_$_XCTestCase", %struct._objc_cache* @_objc_empty_cache, i8* (i8*, i8*)** null, %struct._class_ro_t* @"\01l_OBJC_METACLASS_RO_$_FooTest" }, section "__DATA, __objc_data", align 8
@"OBJC_CLASS_$_XCTestCase" = external global %struct._class_t
@OBJC_METH_VAR_NAME_.8 = private global [8 x i8] c"testFoo\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_ = private global [8 x i8] c"v16@0:8\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@"\01l_OBJC_$_INSTANCE_METHODS_FooTest" = private global { i32, i32, [1 x %struct._objc_method] } { i32 24, i32 1, [1 x %struct._objc_method] [%struct._objc_method { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_NAME_.8, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_, i32 0, i32 0), i8* bitcast (void (%0*, i8*)* @"\01-[FooTest testFoo]" to i8*) }] }, section "__DATA, __objc_const", align 8
@"\01l_OBJC_CLASS_RO_$_FooTest" = private global %struct._class_ro_t { i32 0, i32 8, i32 8, i8* null, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_CLASS_NAME_, i32 0, i32 0), %struct.__method_list_t* bitcast ({ i32, i32, [1 x %struct._objc_method] }* @"\01l_OBJC_$_INSTANCE_METHODS_FooTest" to %struct.__method_list_t*), %struct._objc_protocol_list* null, %struct._ivar_list_t* null, i8* null, %struct._prop_list_t* null }, section "__DATA, __objc_const", align 8
@"OBJC_CLASS_$_FooTest" = global %struct._class_t { %struct._class_t* @"OBJC_METACLASS_$_FooTest", %struct._class_t* @"OBJC_CLASS_$_XCTestCase", %struct._objc_cache* @_objc_empty_cache, i8* (i8*, i8*)** null, %struct._class_ro_t* @"\01l_OBJC_CLASS_RO_$_FooTest" }, section "__DATA, __objc_data", align 8
@"OBJC_CLASS_$_MUT_XCTestObserver" = global %struct._class_t { %struct._class_t* @"OBJC_METACLASS_$_MUT_XCTestObserver", %struct._class_t* @"OBJC_CLASS_$_NSObject", %struct._objc_cache* @_objc_empty_cache, i8* (i8*, i8*)** null, %struct._class_ro_t* @"\01l_OBJC_CLASS_RO_$_MUT_XCTestObserver" }, section "__DATA, __objc_data", align 8
@"OBJC_CLASSLIST_SUP_REFS_$_" = private global %struct._class_t* @"OBJC_CLASS_$_MUT_XCTestObserver", section "__DATA, __objc_superrefs, regular, no_dead_strip", align 8
@OBJC_METH_VAR_NAME_.9 = private global [5 x i8] c"init\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_SELECTOR_REFERENCES_.10 = private externally_initialized global i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_METH_VAR_NAME_.9, i32 0, i32 0), section "__DATA, __objc_selrefs, literal_pointers, no_dead_strip", align 8
@OBJC_METH_VAR_NAME_.11 = private global [16 x i8] c"setTestsFailed:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_SELECTOR_REFERENCES_.12 = private externally_initialized global i8* getelementptr inbounds ([16 x i8], [16 x i8]* @OBJC_METH_VAR_NAME_.11, i32 0, i32 0), section "__DATA, __objc_selrefs, literal_pointers, no_dead_strip", align 8
@.str.13 = private unnamed_addr constant [24 x i8] c"testBundleWillStart: %@\00", section "__TEXT,__cstring,cstring_literals", align 1
@_unnamed_cfstring_.14 = private constant %struct.__NSConstantString_tag { i32* getelementptr inbounds ([0 x i32], [0 x i32]* @__CFConstantStringClassReference, i32 0, i32 0), i32 1992, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.13, i32 0, i32 0), i64 23 }, section "__DATA,__cfstring", align 8
@.str.15 = private unnamed_addr constant [24 x i8] c"testBundleDidFinish: %@\00", section "__TEXT,__cstring,cstring_literals", align 1
@_unnamed_cfstring_.16 = private constant %struct.__NSConstantString_tag { i32* getelementptr inbounds ([0 x i32], [0 x i32]* @__CFConstantStringClassReference, i32 0, i32 0), i32 1992, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.15, i32 0, i32 0), i64 23 }, section "__DATA,__cfstring", align 8
@.str.17 = private unnamed_addr constant [23 x i8] c"testSuiteWillStart: %@\00", section "__TEXT,__cstring,cstring_literals", align 1
@_unnamed_cfstring_.18 = private constant %struct.__NSConstantString_tag { i32* getelementptr inbounds ([0 x i32], [0 x i32]* @__CFConstantStringClassReference, i32 0, i32 0), i32 1992, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.17, i32 0, i32 0), i64 22 }, section "__DATA,__cfstring", align 8
@.str.19 = private unnamed_addr constant [22 x i8] c"testCaseWillStart: %@\00", section "__TEXT,__cstring,cstring_literals", align 1
@_unnamed_cfstring_.20 = private constant %struct.__NSConstantString_tag { i32* getelementptr inbounds ([0 x i32], [0 x i32]* @__CFConstantStringClassReference, i32 0, i32 0), i32 1992, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.19, i32 0, i32 0), i64 21 }, section "__DATA,__cfstring", align 8
@.str.21 = private unnamed_addr constant [23 x i8] c"testSuiteDidFinish: %@\00", section "__TEXT,__cstring,cstring_literals", align 1
@_unnamed_cfstring_.22 = private constant %struct.__NSConstantString_tag { i32* getelementptr inbounds ([0 x i32], [0 x i32]* @__CFConstantStringClassReference, i32 0, i32 0), i32 1992, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.21, i32 0, i32 0), i64 22 }, section "__DATA,__cfstring", align 8
@.str.23 = private unnamed_addr constant [61 x i8] c"testSuite:didFailWithDescription:inFile:atLine: %@ %@ %@ %tu\00", section "__TEXT,__cstring,cstring_literals", align 1
@_unnamed_cfstring_.24 = private constant %struct.__NSConstantString_tag { i32* getelementptr inbounds ([0 x i32], [0 x i32]* @__CFConstantStringClassReference, i32 0, i32 0), i32 1992, i8* getelementptr inbounds ([61 x i8], [61 x i8]* @.str.23, i32 0, i32 0), i64 60 }, section "__DATA,__cfstring", align 8
@.str.25 = private unnamed_addr constant [60 x i8] c"testCase:didFailWithDescription:inFile:atLine: %@ %@ %@ %tu\00", section "__TEXT,__cstring,cstring_literals", align 1
@_unnamed_cfstring_.26 = private constant %struct.__NSConstantString_tag { i32* getelementptr inbounds ([0 x i32], [0 x i32]* @__CFConstantStringClassReference, i32 0, i32 0), i32 1992, i8* getelementptr inbounds ([60 x i8], [60 x i8]* @.str.25, i32 0, i32 0), i64 59 }, section "__DATA,__cfstring", align 8
@OBJC_METH_VAR_NAME_.27 = private global [12 x i8] c"testsFailed\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_SELECTOR_REFERENCES_.28 = private externally_initialized global i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_METH_VAR_NAME_.27, i32 0, i32 0), section "__DATA, __objc_selrefs, literal_pointers, no_dead_strip", align 8
@.str.29 = private unnamed_addr constant [23 x i8] c"testCaseWillFinish: %@\00", section "__TEXT,__cstring,cstring_literals", align 1
@_unnamed_cfstring_.30 = private constant %struct.__NSConstantString_tag { i32* getelementptr inbounds ([0 x i32], [0 x i32]* @__CFConstantStringClassReference, i32 0, i32 0), i32 1992, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.29, i32 0, i32 0), i64 22 }, section "__DATA,__cfstring", align 8
@"OBJC_IVAR_$_MUT_XCTestObserver._testsFailed" = hidden global i64 8, section "__DATA, __objc_ivar", align 8
@OBJC_CLASS_NAME_.31 = private global [19 x i8] c"MUT_XCTestObserver\00", section "__TEXT,__objc_classname,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.32 = private global [21 x i8] c"testBundleWillStart:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.33 = private global [11 x i8] c"v24@0:8@16\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.34 = private global [21 x i8] c"v24@0:8@\22NSBundle\2216\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.35 = private global [21 x i8] c"testBundleDidFinish:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.36 = private global [20 x i8] c"testSuiteWillStart:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.37 = private global [24 x i8] c"v24@0:8@\22XCTestSuite\2216\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.38 = private global [48 x i8] c"testSuite:didFailWithDescription:inFile:atLine:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.39 = private global [20 x i8] c"v48@0:8@16@24@32Q40\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.40 = private global [53 x i8] c"v48@0:8@\22XCTestSuite\2216@\22NSString\2224@\22NSString\2232Q40\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.41 = private global [20 x i8] c"testSuiteDidFinish:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.42 = private global [19 x i8] c"testCaseWillStart:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.43 = private global [23 x i8] c"v24@0:8@\22XCTestCase\2216\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.44 = private global [47 x i8] c"testCase:didFailWithDescription:inFile:atLine:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.45 = private global [52 x i8] c"v48@0:8@\22XCTestCase\2216@\22NSString\2224@\22NSString\2232Q40\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.46 = private global [19 x i8] c"testCaseDidFinish:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_CLASS_NAME_.47 = private global [18 x i8] c"XCTestObservation\00", section "__TEXT,__objc_classname,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.48 = private global [9 x i8] c"isEqual:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.49 = private global [11 x i8] c"c24@0:8@16\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.50 = private global [6 x i8] c"class\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.51 = private global [8 x i8] c"#16@0:8\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.52 = private global [5 x i8] c"self\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.53 = private global [8 x i8] c"@16@0:8\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.54 = private global [17 x i8] c"performSelector:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.55 = private global [11 x i8] c"@24@0:8:16\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.56 = private global [28 x i8] c"performSelector:withObject:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.57 = private global [14 x i8] c"@32@0:8:16@24\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.58 = private global [39 x i8] c"performSelector:withObject:withObject:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.59 = private global [17 x i8] c"@40@0:8:16@24@32\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.60 = private global [8 x i8] c"isProxy\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.61 = private global [8 x i8] c"c16@0:8\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.62 = private global [15 x i8] c"isKindOfClass:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.63 = private global [11 x i8] c"c24@0:8#16\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.64 = private global [17 x i8] c"isMemberOfClass:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.65 = private global [20 x i8] c"conformsToProtocol:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.66 = private global [21 x i8] c"c24@0:8@\22Protocol\2216\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.67 = private global [20 x i8] c"respondsToSelector:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.68 = private global [11 x i8] c"c24@0:8:16\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.69 = private global [7 x i8] c"retain\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.70 = private global [8 x i8] c"release\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.71 = private global [9 x i8] c"Vv16@0:8\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.72 = private global [12 x i8] c"autorelease\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.73 = private global [12 x i8] c"retainCount\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.74 = private global [8 x i8] c"Q16@0:8\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.75 = private global [5 x i8] c"zone\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.76 = private global [18 x i8] c"^{_NSZone=}16@0:8\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.77 = private global [5 x i8] c"hash\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.78 = private global [11 x i8] c"superclass\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.79 = private global [12 x i8] c"description\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.80 = private global [18 x i8] c"@\22NSString\2216@0:8\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@OBJC_METH_VAR_NAME_.81 = private global [17 x i8] c"debugDescription\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_CLASS_NAME_.82 = private global [9 x i8] c"NSObject\00", section "__TEXT,__objc_classname,cstring_literals", align 1
@"\01l_OBJC_$_PROTOCOL_INSTANCE_METHODS_NSObject" = private global { i32, i32, [19 x %struct._objc_method] } { i32 24, i32 19, [19 x %struct._objc_method] [%struct._objc_method { i8* getelementptr inbounds ([9 x i8], [9 x i8]* @OBJC_METH_VAR_NAME_.48, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.49, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @OBJC_METH_VAR_NAME_.50, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.51, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_METH_VAR_NAME_.52, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.53, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_METH_VAR_NAME_.54, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.55, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([28 x i8], [28 x i8]* @OBJC_METH_VAR_NAME_.56, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @OBJC_METH_VAR_TYPE_.57, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([39 x i8], [39 x i8]* @OBJC_METH_VAR_NAME_.58, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_METH_VAR_TYPE_.59, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_NAME_.60, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.61, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([15 x i8], [15 x i8]* @OBJC_METH_VAR_NAME_.62, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.63, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_METH_VAR_NAME_.64, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.63, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_NAME_.65, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.49, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_NAME_.67, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.68, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @OBJC_METH_VAR_NAME_.69, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.53, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_NAME_.70, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @OBJC_METH_VAR_TYPE_.71, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_METH_VAR_NAME_.72, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.53, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_METH_VAR_NAME_.73, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.74, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_METH_VAR_NAME_.75, i32 0, i32 0), i8* getelementptr inbounds ([18 x i8], [18 x i8]* @OBJC_METH_VAR_TYPE_.76, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_METH_VAR_NAME_.77, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.74, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_NAME_.78, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.51, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_METH_VAR_NAME_.79, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.53, i32 0, i32 0), i8* null }] }, section "__DATA, __objc_const", align 8
@"\01l_OBJC_$_PROTOCOL_INSTANCE_METHODS_OPT_NSObject" = private global { i32, i32, [1 x %struct._objc_method] } { i32 24, i32 1, [1 x %struct._objc_method] [%struct._objc_method { i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_METH_VAR_NAME_.81, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.53, i32 0, i32 0), i8* null }] }, section "__DATA, __objc_const", align 8
@OBJC_PROP_NAME_ATTR_ = private global [5 x i8] c"hash\00", section "__TEXT,__cstring,cstring_literals", align 1
@OBJC_PROP_NAME_ATTR_.83 = private global [5 x i8] c"TQ,R\00", section "__TEXT,__cstring,cstring_literals", align 1
@OBJC_PROP_NAME_ATTR_.84 = private global [11 x i8] c"superclass\00", section "__TEXT,__cstring,cstring_literals", align 1
@OBJC_PROP_NAME_ATTR_.85 = private global [5 x i8] c"T#,R\00", section "__TEXT,__cstring,cstring_literals", align 1
@OBJC_PROP_NAME_ATTR_.86 = private global [12 x i8] c"description\00", section "__TEXT,__cstring,cstring_literals", align 1
@OBJC_PROP_NAME_ATTR_.87 = private global [17 x i8] c"T@\22NSString\22,R,C\00", section "__TEXT,__cstring,cstring_literals", align 1
@OBJC_PROP_NAME_ATTR_.88 = private global [17 x i8] c"debugDescription\00", section "__TEXT,__cstring,cstring_literals", align 1
@"\01l_OBJC_$_PROP_LIST_NSObject" = private global { i32, i32, [4 x %struct._prop_t] } { i32 16, i32 4, [4 x %struct._prop_t] [%struct._prop_t { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_PROP_NAME_ATTR_, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_PROP_NAME_ATTR_.83, i32 0, i32 0) }, %struct._prop_t { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_PROP_NAME_ATTR_.84, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_PROP_NAME_ATTR_.85, i32 0, i32 0) }, %struct._prop_t { i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_PROP_NAME_ATTR_.86, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_PROP_NAME_ATTR_.87, i32 0, i32 0) }, %struct._prop_t { i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_PROP_NAME_ATTR_.88, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_PROP_NAME_ATTR_.87, i32 0, i32 0) }] }, section "__DATA, __objc_const", align 8
@"\01l_OBJC_$_PROTOCOL_METHOD_TYPES_NSObject" = private global [20 x i8*] [i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.49, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.51, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.53, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.55, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @OBJC_METH_VAR_TYPE_.57, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_METH_VAR_TYPE_.59, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.61, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.63, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.63, i32 0, i32 0), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @OBJC_METH_VAR_TYPE_.66, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.68, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.53, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @OBJC_METH_VAR_TYPE_.71, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.53, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.74, i32 0, i32 0), i8* getelementptr inbounds ([18 x i8], [18 x i8]* @OBJC_METH_VAR_TYPE_.76, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.74, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.51, i32 0, i32 0), i8* getelementptr inbounds ([18 x i8], [18 x i8]* @OBJC_METH_VAR_TYPE_.80, i32 0, i32 0), i8* getelementptr inbounds ([18 x i8], [18 x i8]* @OBJC_METH_VAR_TYPE_.80, i32 0, i32 0)], section "__DATA, __objc_const", align 8
@"\01l_OBJC_PROTOCOL_$_NSObject" = weak hidden global %struct._protocol_t { i8* null, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @OBJC_CLASS_NAME_.82, i32 0, i32 0), %struct._objc_protocol_list* null, %struct.__method_list_t* bitcast ({ i32, i32, [19 x %struct._objc_method] }* @"\01l_OBJC_$_PROTOCOL_INSTANCE_METHODS_NSObject" to %struct.__method_list_t*), %struct.__method_list_t* null, %struct.__method_list_t* bitcast ({ i32, i32, [1 x %struct._objc_method] }* @"\01l_OBJC_$_PROTOCOL_INSTANCE_METHODS_OPT_NSObject" to %struct.__method_list_t*), %struct.__method_list_t* null, %struct._prop_list_t* bitcast ({ i32, i32, [4 x %struct._prop_t] }* @"\01l_OBJC_$_PROP_LIST_NSObject" to %struct._prop_list_t*), i32 96, i32 0, i8** getelementptr inbounds ([20 x i8*], [20 x i8*]* @"\01l_OBJC_$_PROTOCOL_METHOD_TYPES_NSObject", i32 0, i32 0), i8* null, %struct._prop_list_t* null }, align 8
@"\01l_OBJC_LABEL_PROTOCOL_$_NSObject" = weak hidden global %struct._protocol_t* @"\01l_OBJC_PROTOCOL_$_NSObject", section "__DATA, __objc_protolist, coalesced, no_dead_strip", align 8
@"\01l_OBJC_$_PROTOCOL_REFS_XCTestObservation" = private global { i64, [2 x %struct._protocol_t*] } { i64 1, [2 x %struct._protocol_t*] [%struct._protocol_t* @"\01l_OBJC_PROTOCOL_$_NSObject", %struct._protocol_t* null] }, section "__DATA, __objc_const", align 8
@"\01l_OBJC_$_PROTOCOL_INSTANCE_METHODS_OPT_XCTestObservation" = private global { i32, i32, [8 x %struct._objc_method] } { i32 24, i32 8, [8 x %struct._objc_method] [%struct._objc_method { i8* getelementptr inbounds ([21 x i8], [21 x i8]* @OBJC_METH_VAR_NAME_.32, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.33, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([21 x i8], [21 x i8]* @OBJC_METH_VAR_NAME_.35, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.33, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_NAME_.36, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.33, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([48 x i8], [48 x i8]* @OBJC_METH_VAR_NAME_.38, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_TYPE_.39, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_NAME_.41, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.33, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([19 x i8], [19 x i8]* @OBJC_METH_VAR_NAME_.42, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.33, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([47 x i8], [47 x i8]* @OBJC_METH_VAR_NAME_.44, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_TYPE_.39, i32 0, i32 0), i8* null }, %struct._objc_method { i8* getelementptr inbounds ([19 x i8], [19 x i8]* @OBJC_METH_VAR_NAME_.46, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.33, i32 0, i32 0), i8* null }] }, section "__DATA, __objc_const", align 8
@"\01l_OBJC_$_PROTOCOL_METHOD_TYPES_XCTestObservation" = private global [8 x i8*] [i8* getelementptr inbounds ([21 x i8], [21 x i8]* @OBJC_METH_VAR_TYPE_.34, i32 0, i32 0), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @OBJC_METH_VAR_TYPE_.34, i32 0, i32 0), i8* getelementptr inbounds ([24 x i8], [24 x i8]* @OBJC_METH_VAR_TYPE_.37, i32 0, i32 0), i8* getelementptr inbounds ([53 x i8], [53 x i8]* @OBJC_METH_VAR_TYPE_.40, i32 0, i32 0), i8* getelementptr inbounds ([24 x i8], [24 x i8]* @OBJC_METH_VAR_TYPE_.37, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @OBJC_METH_VAR_TYPE_.43, i32 0, i32 0), i8* getelementptr inbounds ([52 x i8], [52 x i8]* @OBJC_METH_VAR_TYPE_.45, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @OBJC_METH_VAR_TYPE_.43, i32 0, i32 0)], section "__DATA, __objc_const", align 8
@"\01l_OBJC_PROTOCOL_$_XCTestObservation" = weak hidden global %struct._protocol_t { i8* null, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @OBJC_CLASS_NAME_.47, i32 0, i32 0), %struct._objc_protocol_list* bitcast ({ i64, [2 x %struct._protocol_t*] }* @"\01l_OBJC_$_PROTOCOL_REFS_XCTestObservation" to %struct._objc_protocol_list*), %struct.__method_list_t* null, %struct.__method_list_t* null, %struct.__method_list_t* bitcast ({ i32, i32, [8 x %struct._objc_method] }* @"\01l_OBJC_$_PROTOCOL_INSTANCE_METHODS_OPT_XCTestObservation" to %struct.__method_list_t*), %struct.__method_list_t* null, %struct._prop_list_t* null, i32 96, i32 0, i8** getelementptr inbounds ([8 x i8*], [8 x i8*]* @"\01l_OBJC_$_PROTOCOL_METHOD_TYPES_XCTestObservation", i32 0, i32 0), i8* null, %struct._prop_list_t* null }, align 8
@"\01l_OBJC_LABEL_PROTOCOL_$_XCTestObservation" = weak hidden global %struct._protocol_t* @"\01l_OBJC_PROTOCOL_$_XCTestObservation", section "__DATA, __objc_protolist, coalesced, no_dead_strip", align 8
@"\01l_OBJC_CLASS_PROTOCOLS_$_MUT_XCTestObserver" = private global { i64, [2 x %struct._protocol_t*] } { i64 1, [2 x %struct._protocol_t*] [%struct._protocol_t* @"\01l_OBJC_PROTOCOL_$_XCTestObservation", %struct._protocol_t* null] }, section "__DATA, __objc_const", align 8
@"\01l_OBJC_METACLASS_RO_$_MUT_XCTestObserver" = private global %struct._class_ro_t { i32 1, i32 40, i32 40, i8* null, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @OBJC_CLASS_NAME_.31, i32 0, i32 0), %struct.__method_list_t* null, %struct._objc_protocol_list* bitcast ({ i64, [2 x %struct._protocol_t*] }* @"\01l_OBJC_CLASS_PROTOCOLS_$_MUT_XCTestObserver" to %struct._objc_protocol_list*), %struct._ivar_list_t* null, i8* null, %struct._prop_list_t* null }, section "__DATA, __objc_const", align 8
@"OBJC_METACLASS_$_MUT_XCTestObserver" = global %struct._class_t { %struct._class_t* @"OBJC_METACLASS_$_NSObject", %struct._class_t* @"OBJC_METACLASS_$_NSObject", %struct._objc_cache* @_objc_empty_cache, i8* (i8*, i8*)** null, %struct._class_ro_t* @"\01l_OBJC_METACLASS_RO_$_MUT_XCTestObserver" }, section "__DATA, __objc_data", align 8
@"OBJC_CLASS_$_NSObject" = external global %struct._class_t
@OBJC_METH_VAR_TYPE_.89 = private global [11 x i8] c"v24@0:8Q16\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@"\01l_OBJC_$_INSTANCE_METHODS_MUT_XCTestObserver" = private global { i32, i32, [11 x %struct._objc_method] } { i32 24, i32 11, [11 x %struct._objc_method] [%struct._objc_method { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_METH_VAR_NAME_.9, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.53, i32 0, i32 0), i8* bitcast (i8* (%5*, i8*)* @"\01-[MUT_XCTestObserver init]" to i8*) }, %struct._objc_method { i8* getelementptr inbounds ([21 x i8], [21 x i8]* @OBJC_METH_VAR_NAME_.32, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.33, i32 0, i32 0), i8* bitcast (void (%5*, i8*, %6*)* @"\01-[MUT_XCTestObserver testBundleWillStart:]" to i8*) }, %struct._objc_method { i8* getelementptr inbounds ([21 x i8], [21 x i8]* @OBJC_METH_VAR_NAME_.35, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.33, i32 0, i32 0), i8* bitcast (void (%5*, i8*, %6*)* @"\01-[MUT_XCTestObserver testBundleDidFinish:]" to i8*) }, %struct._objc_method { i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_NAME_.36, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.33, i32 0, i32 0), i8* bitcast (void (%5*, i8*, %7*)* @"\01-[MUT_XCTestObserver testSuiteWillStart:]" to i8*) }, %struct._objc_method { i8* getelementptr inbounds ([19 x i8], [19 x i8]* @OBJC_METH_VAR_NAME_.42, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.33, i32 0, i32 0), i8* bitcast (void (%5*, i8*, %4*)* @"\01-[MUT_XCTestObserver testCaseWillStart:]" to i8*) }, %struct._objc_method { i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_NAME_.41, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.33, i32 0, i32 0), i8* bitcast (void (%5*, i8*, %7*)* @"\01-[MUT_XCTestObserver testSuiteDidFinish:]" to i8*) }, %struct._objc_method { i8* getelementptr inbounds ([48 x i8], [48 x i8]* @OBJC_METH_VAR_NAME_.38, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_TYPE_.39, i32 0, i32 0), i8* bitcast (void (%5*, i8*, %7*, %1*, %1*, i64)* @"\01-[MUT_XCTestObserver testSuite:didFailWithDescription:inFile:atLine:]" to i8*) }, %struct._objc_method { i8* getelementptr inbounds ([47 x i8], [47 x i8]* @OBJC_METH_VAR_NAME_.44, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_TYPE_.39, i32 0, i32 0), i8* bitcast (void (%5*, i8*, %4*, %1*, %1*, i64)* @"\01-[MUT_XCTestObserver testCase:didFailWithDescription:inFile:atLine:]" to i8*) }, %struct._objc_method { i8* getelementptr inbounds ([19 x i8], [19 x i8]* @OBJC_METH_VAR_NAME_.46, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.33, i32 0, i32 0), i8* bitcast (void (%5*, i8*, %4*)* @"\01-[MUT_XCTestObserver testCaseDidFinish:]" to i8*) }, %struct._objc_method { i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_METH_VAR_NAME_.27, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.74, i32 0, i32 0), i8* bitcast (i64 (%5*, i8*)* @"\01-[MUT_XCTestObserver testsFailed]" to i8*) }, %struct._objc_method { i8* getelementptr inbounds ([16 x i8], [16 x i8]* @OBJC_METH_VAR_NAME_.11, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.89, i32 0, i32 0), i8* bitcast (void (%5*, i8*, i64)* @"\01-[MUT_XCTestObserver setTestsFailed:]" to i8*) }] }, section "__DATA, __objc_const", align 8
@OBJC_METH_VAR_NAME_.90 = private global [13 x i8] c"_testsFailed\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_METH_VAR_TYPE_.91 = private global [2 x i8] c"Q\00", section "__TEXT,__objc_methtype,cstring_literals", align 1
@"\01l_OBJC_$_INSTANCE_VARIABLES_MUT_XCTestObserver" = private global { i32, i32, [1 x %struct._ivar_t] } { i32 32, i32 1, [1 x %struct._ivar_t] [%struct._ivar_t { i64* @"OBJC_IVAR_$_MUT_XCTestObserver._testsFailed", i8* getelementptr inbounds ([13 x i8], [13 x i8]* @OBJC_METH_VAR_NAME_.90, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @OBJC_METH_VAR_TYPE_.91, i32 0, i32 0), i32 3, i32 8 }] }, section "__DATA, __objc_const", align 8
@OBJC_PROP_NAME_ATTR_.92 = private global [12 x i8] c"testsFailed\00", section "__TEXT,__cstring,cstring_literals", align 1
@OBJC_PROP_NAME_ATTR_.93 = private global [19 x i8] c"TQ,N,V_testsFailed\00", section "__TEXT,__cstring,cstring_literals", align 1
@"\01l_OBJC_$_PROP_LIST_MUT_XCTestObserver" = private global { i32, i32, [5 x %struct._prop_t] } { i32 16, i32 5, [5 x %struct._prop_t] [%struct._prop_t { i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_PROP_NAME_ATTR_.92, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @OBJC_PROP_NAME_ATTR_.93, i32 0, i32 0) }, %struct._prop_t { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_PROP_NAME_ATTR_, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_PROP_NAME_ATTR_.83, i32 0, i32 0) }, %struct._prop_t { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_PROP_NAME_ATTR_.84, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_PROP_NAME_ATTR_.85, i32 0, i32 0) }, %struct._prop_t { i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_PROP_NAME_ATTR_.86, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_PROP_NAME_ATTR_.87, i32 0, i32 0) }, %struct._prop_t { i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_PROP_NAME_ATTR_.88, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_PROP_NAME_ATTR_.87, i32 0, i32 0) }] }, section "__DATA, __objc_const", align 8
@"\01l_OBJC_CLASS_RO_$_MUT_XCTestObserver" = private global %struct._class_ro_t { i32 0, i32 8, i32 16, i8* null, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @OBJC_CLASS_NAME_.31, i32 0, i32 0), %struct.__method_list_t* bitcast ({ i32, i32, [11 x %struct._objc_method] }* @"\01l_OBJC_$_INSTANCE_METHODS_MUT_XCTestObserver" to %struct.__method_list_t*), %struct._objc_protocol_list* bitcast ({ i64, [2 x %struct._protocol_t*] }* @"\01l_OBJC_CLASS_PROTOCOLS_$_MUT_XCTestObserver" to %struct._objc_protocol_list*), %struct._ivar_list_t* bitcast ({ i32, i32, [1 x %struct._ivar_t] }* @"\01l_OBJC_$_INSTANCE_VARIABLES_MUT_XCTestObserver" to %struct._ivar_list_t*), i8* null, %struct._prop_list_t* bitcast ({ i32, i32, [5 x %struct._prop_t] }* @"\01l_OBJC_$_PROP_LIST_MUT_XCTestObserver" to %struct._prop_list_t*) }, section "__DATA, __objc_const", align 8
@"OBJC_CLASSLIST_REFERENCES_$_.94" = private global %struct._class_t* @"OBJC_CLASS_$_MUT_XCTestObserver", section "__DATA, __objc_classrefs, regular, no_dead_strip", align 8
@OBJC_METH_VAR_NAME_.95 = private global [4 x i8] c"new\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_SELECTOR_REFERENCES_.96 = private externally_initialized global i8* getelementptr inbounds ([4 x i8], [4 x i8]* @OBJC_METH_VAR_NAME_.95, i32 0, i32 0), section "__DATA, __objc_selrefs, literal_pointers, no_dead_strip", align 8
@"OBJC_CLASS_$_XCTestObservationCenter" = external global %struct._class_t
@"OBJC_CLASSLIST_REFERENCES_$_.97" = private global %struct._class_t* @"OBJC_CLASS_$_XCTestObservationCenter", section "__DATA, __objc_classrefs, regular, no_dead_strip", align 8
@OBJC_METH_VAR_NAME_.98 = private global [28 x i8] c"sharedTestObservationCenter\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_SELECTOR_REFERENCES_.99 = private externally_initialized global i8* getelementptr inbounds ([28 x i8], [28 x i8]* @OBJC_METH_VAR_NAME_.98, i32 0, i32 0), section "__DATA, __objc_selrefs, literal_pointers, no_dead_strip", align 8
@OBJC_METH_VAR_NAME_.100 = private global [17 x i8] c"addTestObserver:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_SELECTOR_REFERENCES_.101 = private externally_initialized global i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_METH_VAR_NAME_.100, i32 0, i32 0), section "__DATA, __objc_selrefs, literal_pointers, no_dead_strip", align 8
@"OBJC_CLASS_$_XCTestSuite" = external global %struct._class_t
@"OBJC_CLASSLIST_REFERENCES_$_.102" = private global %struct._class_t* @"OBJC_CLASS_$_XCTestSuite", section "__DATA, __objc_classrefs, regular, no_dead_strip", align 8
@OBJC_METH_VAR_NAME_.103 = private global [17 x i8] c"defaultTestSuite\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_SELECTOR_REFERENCES_.104 = private externally_initialized global i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_METH_VAR_NAME_.103, i32 0, i32 0), section "__DATA, __objc_selrefs, literal_pointers, no_dead_strip", align 8
@OBJC_METH_VAR_NAME_.105 = private global [8 x i8] c"runTest\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_SELECTOR_REFERENCES_.106 = private externally_initialized global i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_NAME_.105, i32 0, i32 0), section "__DATA, __objc_selrefs, literal_pointers, no_dead_strip", align 8
@.str.107 = private unnamed_addr constant [34 x i8] c"MUT_RunXCTests: tests failed: %tu\00", section "__TEXT,__cstring,cstring_literals", align 1
@_unnamed_cfstring_.108 = private constant %struct.__NSConstantString_tag { i32* getelementptr inbounds ([0 x i32], [0 x i32]* @__CFConstantStringClassReference, i32 0, i32 0), i32 1992, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.107, i32 0, i32 0), i64 33 }, section "__DATA,__cfstring", align 8
@"OBJC_LABEL_CLASS_$" = private global [2 x i8*] [i8* bitcast (%struct._class_t* @"OBJC_CLASS_$_FooTest" to i8*), i8* bitcast (%struct._class_t* @"OBJC_CLASS_$_MUT_XCTestObserver" to i8*)], section "__DATA, __objc_classlist, regular, no_dead_strip", align 8
@llvm.compiler.used = appending global [111 x i8*] [i8* bitcast (%struct._class_t** @"OBJC_CLASSLIST_REFERENCES_$_" to i8*), i8* getelementptr inbounds ([18 x i8], [18 x i8]* @OBJC_METH_VAR_NAME_, i32 0, i32 0), i8* bitcast (i8** @OBJC_SELECTOR_REFERENCES_ to i8*), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @OBJC_METH_VAR_NAME_.4, i32 0, i32 0), i8* bitcast (i8** @OBJC_SELECTOR_REFERENCES_.5 to i8*), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @OBJC_METH_VAR_NAME_.6, i32 0, i32 0), i8* bitcast (i8** @OBJC_SELECTOR_REFERENCES_.7 to i8*), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_CLASS_NAME_, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_NAME_.8, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_, i32 0, i32 0), i8* bitcast ({ i32, i32, [1 x %struct._objc_method] }* @"\01l_OBJC_$_INSTANCE_METHODS_FooTest" to i8*), i8* bitcast (%struct._class_t** @"OBJC_CLASSLIST_SUP_REFS_$_" to i8*), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_METH_VAR_NAME_.9, i32 0, i32 0), i8* bitcast (i8** @OBJC_SELECTOR_REFERENCES_.10 to i8*), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @OBJC_METH_VAR_NAME_.11, i32 0, i32 0), i8* bitcast (i8** @OBJC_SELECTOR_REFERENCES_.12 to i8*), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_METH_VAR_NAME_.27, i32 0, i32 0), i8* bitcast (i8** @OBJC_SELECTOR_REFERENCES_.28 to i8*), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @OBJC_CLASS_NAME_.31, i32 0, i32 0), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @OBJC_METH_VAR_NAME_.32, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.33, i32 0, i32 0), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @OBJC_METH_VAR_TYPE_.34, i32 0, i32 0), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @OBJC_METH_VAR_NAME_.35, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_NAME_.36, i32 0, i32 0), i8* getelementptr inbounds ([24 x i8], [24 x i8]* @OBJC_METH_VAR_TYPE_.37, i32 0, i32 0), i8* getelementptr inbounds ([48 x i8], [48 x i8]* @OBJC_METH_VAR_NAME_.38, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_TYPE_.39, i32 0, i32 0), i8* getelementptr inbounds ([53 x i8], [53 x i8]* @OBJC_METH_VAR_TYPE_.40, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_NAME_.41, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @OBJC_METH_VAR_NAME_.42, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @OBJC_METH_VAR_TYPE_.43, i32 0, i32 0), i8* getelementptr inbounds ([47 x i8], [47 x i8]* @OBJC_METH_VAR_NAME_.44, i32 0, i32 0), i8* getelementptr inbounds ([52 x i8], [52 x i8]* @OBJC_METH_VAR_TYPE_.45, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @OBJC_METH_VAR_NAME_.46, i32 0, i32 0), i8* getelementptr inbounds ([18 x i8], [18 x i8]* @OBJC_CLASS_NAME_.47, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @OBJC_METH_VAR_NAME_.48, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.49, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @OBJC_METH_VAR_NAME_.50, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.51, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_METH_VAR_NAME_.52, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.53, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_METH_VAR_NAME_.54, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.55, i32 0, i32 0), i8* getelementptr inbounds ([28 x i8], [28 x i8]* @OBJC_METH_VAR_NAME_.56, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @OBJC_METH_VAR_TYPE_.57, i32 0, i32 0), i8* getelementptr inbounds ([39 x i8], [39 x i8]* @OBJC_METH_VAR_NAME_.58, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_METH_VAR_TYPE_.59, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_NAME_.60, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.61, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @OBJC_METH_VAR_NAME_.62, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.63, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_METH_VAR_NAME_.64, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_NAME_.65, i32 0, i32 0), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @OBJC_METH_VAR_TYPE_.66, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_NAME_.67, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.68, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @OBJC_METH_VAR_NAME_.69, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_NAME_.70, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @OBJC_METH_VAR_TYPE_.71, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_METH_VAR_NAME_.72, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_METH_VAR_NAME_.73, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_TYPE_.74, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_METH_VAR_NAME_.75, i32 0, i32 0), i8* getelementptr inbounds ([18 x i8], [18 x i8]* @OBJC_METH_VAR_TYPE_.76, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_METH_VAR_NAME_.77, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_NAME_.78, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_METH_VAR_NAME_.79, i32 0, i32 0), i8* getelementptr inbounds ([18 x i8], [18 x i8]* @OBJC_METH_VAR_TYPE_.80, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_METH_VAR_NAME_.81, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @OBJC_CLASS_NAME_.82, i32 0, i32 0), i8* bitcast ({ i32, i32, [19 x %struct._objc_method] }* @"\01l_OBJC_$_PROTOCOL_INSTANCE_METHODS_NSObject" to i8*), i8* bitcast ({ i32, i32, [1 x %struct._objc_method] }* @"\01l_OBJC_$_PROTOCOL_INSTANCE_METHODS_OPT_NSObject" to i8*), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_PROP_NAME_ATTR_, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_PROP_NAME_ATTR_.83, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_PROP_NAME_ATTR_.84, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @OBJC_PROP_NAME_ATTR_.85, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_PROP_NAME_ATTR_.86, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_PROP_NAME_ATTR_.87, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_PROP_NAME_ATTR_.88, i32 0, i32 0), i8* bitcast ({ i32, i32, [4 x %struct._prop_t] }* @"\01l_OBJC_$_PROP_LIST_NSObject" to i8*), i8* bitcast ([20 x i8*]* @"\01l_OBJC_$_PROTOCOL_METHOD_TYPES_NSObject" to i8*), i8* bitcast (%struct._protocol_t* @"\01l_OBJC_PROTOCOL_$_NSObject" to i8*), i8* bitcast (%struct._protocol_t** @"\01l_OBJC_LABEL_PROTOCOL_$_NSObject" to i8*), i8* bitcast ({ i64, [2 x %struct._protocol_t*] }* @"\01l_OBJC_$_PROTOCOL_REFS_XCTestObservation" to i8*), i8* bitcast ({ i32, i32, [8 x %struct._objc_method] }* @"\01l_OBJC_$_PROTOCOL_INSTANCE_METHODS_OPT_XCTestObservation" to i8*), i8* bitcast ([8 x i8*]* @"\01l_OBJC_$_PROTOCOL_METHOD_TYPES_XCTestObservation" to i8*), i8* bitcast (%struct._protocol_t* @"\01l_OBJC_PROTOCOL_$_XCTestObservation" to i8*), i8* bitcast (%struct._protocol_t** @"\01l_OBJC_LABEL_PROTOCOL_$_XCTestObservation" to i8*), i8* bitcast ({ i64, [2 x %struct._protocol_t*] }* @"\01l_OBJC_CLASS_PROTOCOLS_$_MUT_XCTestObserver" to i8*), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OBJC_METH_VAR_TYPE_.89, i32 0, i32 0), i8* bitcast ({ i32, i32, [11 x %struct._objc_method] }* @"\01l_OBJC_$_INSTANCE_METHODS_MUT_XCTestObserver" to i8*), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @OBJC_METH_VAR_NAME_.90, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @OBJC_METH_VAR_TYPE_.91, i32 0, i32 0), i8* bitcast ({ i32, i32, [1 x %struct._ivar_t] }* @"\01l_OBJC_$_INSTANCE_VARIABLES_MUT_XCTestObserver" to i8*), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @OBJC_PROP_NAME_ATTR_.92, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @OBJC_PROP_NAME_ATTR_.93, i32 0, i32 0), i8* bitcast ({ i32, i32, [5 x %struct._prop_t] }* @"\01l_OBJC_$_PROP_LIST_MUT_XCTestObserver" to i8*), i8* bitcast (%struct._class_t** @"OBJC_CLASSLIST_REFERENCES_$_.94" to i8*), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @OBJC_METH_VAR_NAME_.95, i32 0, i32 0), i8* bitcast (i8** @OBJC_SELECTOR_REFERENCES_.96 to i8*), i8* bitcast (%struct._class_t** @"OBJC_CLASSLIST_REFERENCES_$_.97" to i8*), i8* getelementptr inbounds ([28 x i8], [28 x i8]* @OBJC_METH_VAR_NAME_.98, i32 0, i32 0), i8* bitcast (i8** @OBJC_SELECTOR_REFERENCES_.99 to i8*), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_METH_VAR_NAME_.100, i32 0, i32 0), i8* bitcast (i8** @OBJC_SELECTOR_REFERENCES_.101 to i8*), i8* bitcast (%struct._class_t** @"OBJC_CLASSLIST_REFERENCES_$_.102" to i8*), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @OBJC_METH_VAR_NAME_.103, i32 0, i32 0), i8* bitcast (i8** @OBJC_SELECTOR_REFERENCES_.104 to i8*), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OBJC_METH_VAR_NAME_.105, i32 0, i32 0), i8* bitcast (i8** @OBJC_SELECTOR_REFERENCES_.106 to i8*), i8* bitcast ([2 x i8*]* @"OBJC_LABEL_CLASS_$" to i8*)], section "llvm.metadata"

; Function Attrs: nounwind ssp uwtable
define i32 @sum(i32, i32) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %4, align 4
  %7 = add nsw i32 %5, %6
  ret i32 %7
  }

  ; Function Attrs: ssp uwtable
  define internal void @"\01-[FooTest testFoo]"(%0*, i8*) #1 personality i8* bitcast (i32 (...)* @__objc_personality_v0 to i8*) {
    %3 = alloca %0*, align 8
    %4 = alloca i8*, align 8
    %5 = alloca i8, align 1
    %6 = alloca i8*
    %7 = alloca i32
    %8 = alloca %1*, align 8
    %9 = alloca %2*, align 8
    %10 = alloca %3*, align 8
    %11 = alloca %1*, align 8
    %12 = alloca %1*, align 8
    store %0* %0, %0** %3, align 8
    store i8* %1, i8** %4, align 8
    %13 = invoke i32 @sum(i32 2, i32 3)
    to label %14 unwind label %35

    ; <label>:14                                      ; preds = %2
    %15 = icmp eq i32 %13, 5
    %16 = xor i1 %15, true
    %17 = xor i1 %16, true
    %18 = zext i1 %17 to i32
    %19 = trunc i32 %18 to i8
    store i8 %19, i8* %5, align 1
    %20 = load i8, i8* %5, align 1
    %21 = icmp ne i8 %20, 0
    br i1 %21, label %46, label %22

    ; <label>:22                                      ; preds = %14
    %23 = load %0*, %0** %3, align 8
    %24 = bitcast %0* %23 to %4*
    %25 = load %struct._class_t*, %struct._class_t** @"OBJC_CLASSLIST_REFERENCES_$_", align 8
    %26 = invoke %1* @_XCTFailureFormat(i64 13, i64 0)
    to label %27 unwind label %35

    ; <label>:27                                      ; preds = %22
    %28 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_, align 8, !invariant.load !7
    %29 = bitcast %struct._class_t* %25 to i8*
    %30 = invoke i8* (i8*, i8*, %1*, ...) bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to i8* (i8*, i8*, %1*, ...)*)(i8* %29, i8* %28, %1* %26, %1* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_ to %1*))
    to label %31 unwind label %35

    ; <label>:31                                      ; preds = %27
    %32 = bitcast i8* %30 to %1*
    store %1* %32, %1** %8, align 8
    %33 = load %1*, %1** %8, align 8
    invoke void (%4*, i8, i8*, i64, %1*, %1*, ...) @_XCTFailureHandler(%4* %24, i8 signext 1, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i64 20, %1* %33, %1* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_.3 to %1*))
    to label %34 unwind label %35

    ; <label>:34                                      ; preds = %31
    br label %46

    ; <label>:35                                      ; preds = %31, %27, %22, %2
    %36 = landingpad { i8*, i32 }
    catch %struct._objc_typeinfo* @"OBJC_EHTYPE_$__XCTestCaseInterruptionException"
    catch %struct._objc_typeinfo* @"OBJC_EHTYPE_$_NSException"
    catch i8* null
    %37 = extractvalue { i8*, i32 } %36, 0
    store i8* %37, i8** %6, align 8
    %38 = extractvalue { i8*, i32 } %36, 1
    store i32 %38, i32* %7, align 4
    br label %39

    ; <label>:39                                      ; preds = %35
    %40 = load i32, i32* %7, align 4
    %41 = call i32 @llvm.eh.typeid.for(i8* bitcast (%struct._objc_typeinfo* @"OBJC_EHTYPE_$__XCTestCaseInterruptionException" to i8*)) #5
    %42 = icmp eq i32 %40, %41
    br i1 %42, label %48, label %43

    ; <label>:43                                      ; preds = %39
    %44 = call i32 @llvm.eh.typeid.for(i8* bitcast (%struct._objc_typeinfo* @"OBJC_EHTYPE_$_NSException" to i8*)) #5
    %45 = icmp eq i32 %40, %44
    br i1 %45, label %60, label %85

    ; <label>:46                                      ; preds = %34, %14
    br label %47

    ; <label>:47                                      ; preds = %46, %99, %80, %55
    ret void

    ; <label>:48                                      ; preds = %39
    %49 = load i8*, i8** %6, align 8
    %50 = call i8* @objc_begin_catch(i8* %49) #5
    %51 = bitcast i8* %50 to %2*
    store %2* %51, %2** %9, align 8
    %52 = load %2*, %2** %9, align 8
    %53 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_.5, align 8, !invariant.load !7
    %54 = bitcast %2* %52 to i8*
    invoke void bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to void (i8*, i8*)*)(i8* %54, i8* %53)
    to label %55 unwind label %56

    ; <label>:55                                      ; preds = %48
    call void @objc_end_catch() #5
    br label %47

    ; <label>:56                                      ; preds = %48
    %57 = landingpad { i8*, i32 }
    cleanup
    %58 = extractvalue { i8*, i32 } %57, 0
    store i8* %58, i8** %6, align 8
    %59 = extractvalue { i8*, i32 } %57, 1
    store i32 %59, i32* %7, align 4
    call void @objc_end_catch() #5
    br label %105

    ; <label>:60                                      ; preds = %43
    %61 = load i8*, i8** %6, align 8
    %62 = call i8* @objc_begin_catch(i8* %61) #5
    %63 = bitcast i8* %62 to %3*
    store %3* %63, %3** %10, align 8
    %64 = load %0*, %0** %3, align 8
    %65 = bitcast %0* %64 to %4*
    %66 = load %struct._class_t*, %struct._class_t** @"OBJC_CLASSLIST_REFERENCES_$_", align 8
    %67 = invoke %1* @_XCTFailureFormat(i64 13, i64 1)
    to label %68 unwind label %81

    ; <label>:68                                      ; preds = %60
    %69 = load %3*, %3** %10, align 8
    %70 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_.7, align 8, !invariant.load !7
    %71 = bitcast %3* %69 to i8*
    %72 = invoke %1* bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to %1* (i8*, i8*)*)(i8* %71, i8* %70)
    to label %73 unwind label %81

    ; <label>:73                                      ; preds = %68
    %74 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_, align 8, !invariant.load !7
    %75 = bitcast %struct._class_t* %66 to i8*
    %76 = invoke i8* (i8*, i8*, %1*, ...) bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to i8* (i8*, i8*, %1*, ...)*)(i8* %75, i8* %74, %1* %67, %1* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_ to %1*), %1* %72)
    to label %77 unwind label %81

    ; <label>:77                                      ; preds = %73
    %78 = bitcast i8* %76 to %1*
    store %1* %78, %1** %11, align 8
    %79 = load %1*, %1** %11, align 8
    invoke void (%4*, i8, i8*, i64, %1*, %1*, ...) @_XCTFailureHandler(%4* %65, i8 signext 0, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i64 20, %1* %79, %1* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_.3 to %1*))
    to label %80 unwind label %81

    ; <label>:80                                      ; preds = %77
    call void @objc_end_catch() #5
    br label %47

    ; <label>:81                                      ; preds = %77, %73, %68, %60
    %82 = landingpad { i8*, i32 }
    cleanup
    %83 = extractvalue { i8*, i32 } %82, 0
    store i8* %83, i8** %6, align 8
    %84 = extractvalue { i8*, i32 } %82, 1
    store i32 %84, i32* %7, align 4
    call void @objc_end_catch() #5
    br label %105

    ; <label>:85                                      ; preds = %43
    %86 = load i8*, i8** %6, align 8
    %87 = call i8* @objc_begin_catch(i8* %86) #5
    %88 = load %0*, %0** %3, align 8
    %89 = bitcast %0* %88 to %4*
    %90 = load %struct._class_t*, %struct._class_t** @"OBJC_CLASSLIST_REFERENCES_$_", align 8
    %91 = invoke %1* @_XCTFailureFormat(i64 13, i64 2)
    to label %92 unwind label %100

    ; <label>:92                                      ; preds = %85
    %93 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_, align 8, !invariant.load !7
    %94 = bitcast %struct._class_t* %90 to i8*
    %95 = invoke i8* (i8*, i8*, %1*, ...) bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to i8* (i8*, i8*, %1*, ...)*)(i8* %94, i8* %93, %1* %91, %1* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_ to %1*))
    to label %96 unwind label %100

    ; <label>:96                                      ; preds = %92
    %97 = bitcast i8* %95 to %1*
    store %1* %97, %1** %12, align 8
    %98 = load %1*, %1** %12, align 8
    invoke void (%4*, i8, i8*, i64, %1*, %1*, ...) @_XCTFailureHandler(%4* %89, i8 signext 0, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i64 20, %1* %98, %1* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_.3 to %1*))
    to label %99 unwind label %100

    ; <label>:99                                      ; preds = %96
    call void @objc_end_catch()
    br label %47

    ; <label>:100                                     ; preds = %96, %92, %85
    %101 = landingpad { i8*, i32 }
    cleanup
    %102 = extractvalue { i8*, i32 } %101, 0
    store i8* %102, i8** %6, align 8
    %103 = extractvalue { i8*, i32 } %101, 1
    store i32 %103, i32* %7, align 4
    invoke void @objc_end_catch()
    to label %104 unwind label %110

    ; <label>:104                                     ; preds = %100
    br label %105

    ; <label>:105                                     ; preds = %104, %81, %56
    %106 = load i8*, i8** %6, align 8
    %107 = load i32, i32* %7, align 4
    %108 = insertvalue { i8*, i32 } undef, i8* %106, 0
    %109 = insertvalue { i8*, i32 } %108, i32 %107, 1
    resume { i8*, i32 } %109

    ; <label>:110                                     ; preds = %100
    %111 = landingpad { i8*, i32 }
    catch i8* null
    call void @objc_terminate() #6
    unreachable
  }

  declare i8* @objc_begin_catch(i8*)

  declare void @objc_end_catch()

  declare void @objc_exception_rethrow()

  declare i32 @__objc_personality_v0(...)

  declare void @_XCTFailureHandler(%4*, i8 signext, i8*, i64, %1*, %1*, ...) #2

  declare %1* @_XCTFailureFormat(i64, i64) #2

  ; Function Attrs: nonlazybind
  declare i8* @objc_msgSend(i8*, i8*, ...) #3

  ; Function Attrs: nounwind readnone
  declare i32 @llvm.eh.typeid.for(i8*) #4

  declare void @objc_terminate()

  ; Function Attrs: ssp uwtable
  define internal i8* @"\01-[MUT_XCTestObserver init]"(%5*, i8*) #1 {
    %3 = alloca %5*, align 8
    %4 = alloca i8*, align 8
    %5 = alloca %struct._objc_super, align 8
    store %5* %0, %5** %3, align 8
    store i8* %1, i8** %4, align 8
    %6 = load %5*, %5** %3, align 8
    %7 = bitcast %5* %6 to i8*
    %8 = getelementptr inbounds %struct._objc_super, %struct._objc_super* %5, i32 0, i32 0
    store i8* %7, i8** %8, align 8
    %9 = load %struct._class_t*, %struct._class_t** @"OBJC_CLASSLIST_SUP_REFS_$_", align 8
    %10 = bitcast %struct._class_t* %9 to i8*
    %11 = getelementptr inbounds %struct._objc_super, %struct._objc_super* %5, i32 0, i32 1
    store i8* %10, i8** %11, align 8
    %12 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_.10, align 8, !invariant.load !7
    %13 = call i8* bitcast (i8* (%struct._objc_super*, i8*, ...)* @objc_msgSendSuper2 to i8* (%struct._objc_super*, i8*)*)(%struct._objc_super* %5, i8* %12)
    %14 = bitcast i8* %13 to %5*
    store %5* %14, %5** %3, align 8
    %15 = load %5*, %5** %3, align 8
    %16 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_.12, align 8, !invariant.load !7
    %17 = bitcast %5* %15 to i8*
    call void bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to void (i8*, i8*, i64)*)(i8* %17, i8* %16, i64 0)
    %18 = load %5*, %5** %3, align 8
    %19 = bitcast %5* %18 to i8*
    ret i8* %19
    }

    declare i8* @objc_msgSendSuper2(%struct._objc_super*, i8*, ...)

    ; Function Attrs: ssp uwtable
    define internal void @"\01-[MUT_XCTestObserver testBundleWillStart:]"(%5*, i8*, %6*) #1 {
      %4 = alloca %5*, align 8
      %5 = alloca i8*, align 8
      %6 = alloca %6*, align 8
      store %5* %0, %5** %4, align 8
      store i8* %1, i8** %5, align 8
      store %6* %2, %6** %6, align 8
      %7 = load %6*, %6** %6, align 8
      call void (i8*, ...) @NSLog(i8* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_.14 to i8*), %6* %7)
      ret void
      }

      declare void @NSLog(i8*, ...) #2

      ; Function Attrs: ssp uwtable
      define internal void @"\01-[MUT_XCTestObserver testBundleDidFinish:]"(%5*, i8*, %6*) #1 {
        %4 = alloca %5*, align 8
        %5 = alloca i8*, align 8
        %6 = alloca %6*, align 8
        store %5* %0, %5** %4, align 8
        store i8* %1, i8** %5, align 8
        store %6* %2, %6** %6, align 8
        %7 = load %6*, %6** %6, align 8
        call void (i8*, ...) @NSLog(i8* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_.16 to i8*), %6* %7)
        ret void
        }

        ; Function Attrs: ssp uwtable
        define internal void @"\01-[MUT_XCTestObserver testSuiteWillStart:]"(%5*, i8*, %7*) #1 {
          %4 = alloca %5*, align 8
          %5 = alloca i8*, align 8
          %6 = alloca %7*, align 8
          store %5* %0, %5** %4, align 8
          store i8* %1, i8** %5, align 8
          store %7* %2, %7** %6, align 8
          %7 = load %7*, %7** %6, align 8
          call void (i8*, ...) @NSLog(i8* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_.18 to i8*), %7* %7)
          ret void
          }

          ; Function Attrs: ssp uwtable
          define internal void @"\01-[MUT_XCTestObserver testCaseWillStart:]"(%5*, i8*, %4*) #1 {
            %4 = alloca %5*, align 8
            %5 = alloca i8*, align 8
            %6 = alloca %4*, align 8
            store %5* %0, %5** %4, align 8
            store i8* %1, i8** %5, align 8
            store %4* %2, %4** %6, align 8
            %7 = load %4*, %4** %6, align 8
            call void (i8*, ...) @NSLog(i8* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_.20 to i8*), %4* %7)
            ret void
            }

            ; Function Attrs: ssp uwtable
            define internal void @"\01-[MUT_XCTestObserver testSuiteDidFinish:]"(%5*, i8*, %7*) #1 {
              %4 = alloca %5*, align 8
              %5 = alloca i8*, align 8
              %6 = alloca %7*, align 8
              store %5* %0, %5** %4, align 8
              store i8* %1, i8** %5, align 8
              store %7* %2, %7** %6, align 8
              %7 = load %7*, %7** %6, align 8
              call void (i8*, ...) @NSLog(i8* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_.22 to i8*), %7* %7)
              ret void
              }

              ; Function Attrs: ssp uwtable
              define internal void @"\01-[MUT_XCTestObserver testSuite:didFailWithDescription:inFile:atLine:]"(%5*, i8*, %7*, %1*, %1*, i64) #1 {
                %7 = alloca %5*, align 8
                %8 = alloca i8*, align 8
                %9 = alloca %7*, align 8
                %10 = alloca %1*, align 8
                %11 = alloca %1*, align 8
                %12 = alloca i64, align 8
                store %5* %0, %5** %7, align 8
                store i8* %1, i8** %8, align 8
                store %7* %2, %7** %9, align 8
                store %1* %3, %1** %10, align 8
                store %1* %4, %1** %11, align 8
                store i64 %5, i64* %12, align 8
                %13 = load %7*, %7** %9, align 8
                %14 = load %1*, %1** %10, align 8
                %15 = load %1*, %1** %11, align 8
                %16 = load i64, i64* %12, align 8
                call void (i8*, ...) @NSLog(i8* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_.24 to i8*), %7* %13, %1* %14, %1* %15, i64 %16)
                ret void
                }

                ; Function Attrs: ssp uwtable
                define internal void @"\01-[MUT_XCTestObserver testCase:didFailWithDescription:inFile:atLine:]"(%5*, i8*, %4*, %1*, %1*, i64) #1 {
                  %7 = alloca %5*, align 8
                  %8 = alloca i8*, align 8
                  %9 = alloca %4*, align 8
                  %10 = alloca %1*, align 8
                  %11 = alloca %1*, align 8
                  %12 = alloca i64, align 8
                  store %5* %0, %5** %7, align 8
                  store i8* %1, i8** %8, align 8
                  store %4* %2, %4** %9, align 8
                  store %1* %3, %1** %10, align 8
                  store %1* %4, %1** %11, align 8
                  store i64 %5, i64* %12, align 8
                  %13 = load %4*, %4** %9, align 8
                  %14 = load %1*, %1** %10, align 8
                  %15 = load %1*, %1** %11, align 8
                  %16 = load i64, i64* %12, align 8
                  call void (i8*, ...) @NSLog(i8* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_.26 to i8*), %4* %13, %1* %14, %1* %15, i64 %16)
                  %17 = load %5*, %5** %7, align 8
                  %18 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_.28, align 8, !invariant.load !7
                  %19 = bitcast %5* %17 to i8*
                  %20 = call i64 bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to i64 (i8*, i8*)*)(i8* %19, i8* %18)
                  %21 = add i64 %20, 1
                  %22 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_.12, align 8, !invariant.load !7
                  %23 = bitcast %5* %17 to i8*
                  call void bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to void (i8*, i8*, i64)*)(i8* %23, i8* %22, i64 %21)
                  ret void
                  }

                  ; Function Attrs: ssp uwtable
                  define internal void @"\01-[MUT_XCTestObserver testCaseDidFinish:]"(%5*, i8*, %4*) #1 {
                    %4 = alloca %5*, align 8
                    %5 = alloca i8*, align 8
                    %6 = alloca %4*, align 8
                    store %5* %0, %5** %4, align 8
                    store i8* %1, i8** %5, align 8
                    store %4* %2, %4** %6, align 8
                    %7 = load %4*, %4** %6, align 8
                    call void (i8*, ...) @NSLog(i8* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_.30 to i8*), %4* %7)
                    ret void
                    }

                    ; Function Attrs: ssp uwtable
                    define internal i64 @"\01-[MUT_XCTestObserver testsFailed]"(%5*, i8*) #1 {
                      %3 = alloca %5*, align 8
                      %4 = alloca i8*, align 8
                      store %5* %0, %5** %3, align 8
                      store i8* %1, i8** %4, align 8
                      %5 = load %5*, %5** %3, align 8
                      %6 = load i64, i64* @"OBJC_IVAR_$_MUT_XCTestObserver._testsFailed", align 8, !invariant.load !7
                      %7 = bitcast %5* %5 to i8*
                      %8 = getelementptr inbounds i8, i8* %7, i64 %6
                      %9 = bitcast i8* %8 to i64*
                      %10 = load i64, i64* %9, align 8
                      ret i64 %10
                      }

                      ; Function Attrs: ssp uwtable
                      define internal void @"\01-[MUT_XCTestObserver setTestsFailed:]"(%5*, i8*, i64) #1 {
                        %4 = alloca %5*, align 8
                        %5 = alloca i8*, align 8
                        %6 = alloca i64, align 8
                        store %5* %0, %5** %4, align 8
                        store i8* %1, i8** %5, align 8
                        store i64 %2, i64* %6, align 8
                        %7 = load i64, i64* %6, align 8
                        %8 = load %5*, %5** %4, align 8
                        %9 = load i64, i64* @"OBJC_IVAR_$_MUT_XCTestObserver._testsFailed", align 8, !invariant.load !7
                        %10 = bitcast %5* %8 to i8*
                        %11 = getelementptr inbounds i8, i8* %10, i64 %9
                        %12 = bitcast i8* %11 to i64*
                        store i64 %7, i64* %12, align 8
                        ret void
                        }

                        ; Function Attrs: ssp uwtable
                        define i32 @MUT_RunXCTests() #1 {
                          %1 = alloca i32, align 4
                          %2 = alloca %5*, align 8
                          %3 = alloca %8*, align 8
                          %4 = alloca %7*, align 8
                          %5 = load %struct._class_t*, %struct._class_t** @"OBJC_CLASSLIST_REFERENCES_$_.94", align 8
                          %6 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_.96, align 8, !invariant.load !7
                          %7 = bitcast %struct._class_t* %5 to i8*
                          %8 = call i8* bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to i8* (i8*, i8*)*)(i8* %7, i8* %6)
                          %9 = bitcast i8* %8 to %5*
                          store %5* %9, %5** %2, align 8
                          %10 = load %struct._class_t*, %struct._class_t** @"OBJC_CLASSLIST_REFERENCES_$_.97", align 8
                          %11 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_.99, align 8, !invariant.load !7
                          %12 = bitcast %struct._class_t* %10 to i8*
                          %13 = call %8* bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to %8* (i8*, i8*)*)(i8* %12, i8* %11)
                          store %8* %13, %8** %3, align 8
                          %14 = load %8*, %8** %3, align 8
                          %15 = load %5*, %5** %2, align 8
                          %16 = bitcast %5* %15 to i8*
                          %17 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_.101, align 8, !invariant.load !7
                          %18 = bitcast %8* %14 to i8*
                          call void bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to void (i8*, i8*, i8*)*)(i8* %18, i8* %17, i8* %16)
                          %19 = load %struct._class_t*, %struct._class_t** @"OBJC_CLASSLIST_REFERENCES_$_.102", align 8
                          %20 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_.104, align 8, !invariant.load !7
                          %21 = bitcast %struct._class_t* %19 to i8*
                          %22 = call i8* bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to i8* (i8*, i8*)*)(i8* %21, i8* %20)
                          %23 = bitcast i8* %22 to %7*
                          store %7* %23, %7** %4, align 8
                          %24 = load %7*, %7** %4, align 8
                          %25 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_.106, align 8, !invariant.load !7
                          %26 = bitcast %7* %24 to i8*
                          call void bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to void (i8*, i8*)*)(i8* %26, i8* %25)
                          %27 = load %5*, %5** %2, align 8
                          %28 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_.28, align 8, !invariant.load !7
                          %29 = bitcast %5* %27 to i8*
                          %30 = call i64 bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to i64 (i8*, i8*)*)(i8* %29, i8* %28)
                          call void (i8*, ...) @NSLog(i8* bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_.108 to i8*), i64 %30)
                          %31 = load %5*, %5** %2, align 8
                          %32 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_.28, align 8, !invariant.load !7
                          %33 = bitcast %5* %31 to i8*
                          %34 = call i64 bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to i64 (i8*, i8*)*)(i8* %33, i8* %32)
                          %35 = icmp ugt i64 %34, 0
                          br i1 %35, label %36, label %37
                          
                          ; <label>:36                                      ; preds = %0
                          store i32 1, i32* %1, align 4
                          br label %38
                          
                          ; <label>:37                                      ; preds = %0
                          store i32 0, i32* %1, align 4
                          br label %38
                          
                          ; <label>:38                                      ; preds = %37, %36
                          %39 = load i32, i32* %1, align 4
                          ret i32 %39
                          }
                          
                          attributes #0 = { nounwind ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3" "unsafe-fp-math"="false" "use-soft-float"="false" }
                          attributes #1 = { ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3" "unsafe-fp-math"="false" "use-soft-float"="false" }
                          attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3" "unsafe-fp-math"="false" "use-soft-float"="false" }
                          attributes #3 = { nonlazybind }
                          attributes #4 = { nounwind readnone }
                          attributes #5 = { nounwind }
                          attributes #6 = { noreturn nounwind }
                          
                          !llvm.module.flags = !{!0, !1, !2, !3, !4, !5}
                          !llvm.ident = !{!6}
                          
                          !0 = !{i32 1, !"Objective-C Version", i32 2}
                          !1 = !{i32 1, !"Objective-C Image Info Version", i32 0}
                          !2 = !{i32 1, !"Objective-C Image Info Section", !"__DATA, __objc_imageinfo, regular, no_dead_strip"}
                          !3 = !{i32 4, !"Objective-C Garbage Collection", i32 0}
                          !4 = !{i32 1, !"Objective-C Class Properties", i32 64}
                          !5 = !{i32 1, !"PIC Level", i32 2}
                          !6 = !{!"Apple LLVM version 8.0.0 (clang-800.0.38)"}
                          !7 = !{}
)foo";

std::unique_ptr<Module> TestModuleFactory::createXCTest_TesterModule() {
  auto module = parseIR(XCTestDriverBitcode);

  return module;
}

