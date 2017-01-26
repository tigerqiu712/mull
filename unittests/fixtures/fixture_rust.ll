; ModuleID = 'example.cgu-0.rs'
source_filename = "example.cgu-0.rs"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-darwin"

%str_slice = type { i8*, i64 }
%"2.std::any::TypeId" = type { i64 }
%"12.__test::test::TestDescAndFn" = type { %"12.__test::test::TestDesc", %"12.__test::test::TestFn" }
%"12.__test::test::TestDesc" = type { %"12.__test::test::TestName", i8, %"12.__test::test::ShouldPanic" }
%"12.__test::test::TestName" = type { i64, [0 x i64], [3 x i64] }
%"12.__test::test::ShouldPanic" = type { i64, [0 x i64], [2 x i64] }
%"12.__test::test::TestFn" = type { i64, [0 x i64], [2 x i64] }
%"8.unwind::libunwind::_Unwind_Exception" = type { i64, void (i32, %"8.unwind::libunwind::_Unwind_Exception"*)*, [6 x i64] }
%"8.unwind::libunwind::_Unwind_Context" = type {}

@vtable.0 = internal unnamed_addr constant { void (i8*)*, i64, i64, i64 (%str_slice*)* } { void (i8*)* @_ZN4drop17h7115f936263dd8e8E, i64 16, i64 8, i64 (%str_slice*)* @"_ZN36_$LT$T$u20$as$u20$core..any..Any$GT$11get_type_id17h4bed9676a70da661E" }, align 8
@str.1 = internal constant [10 x i8] c"example.rs"
@str.2 = internal constant [28 x i8] c"attempt to add with overflow"
@panic_loc.3 = internal unnamed_addr constant { %str_slice, %str_slice, i32 } { %str_slice { i8* getelementptr inbounds ([28 x i8], [28 x i8]* @str.2, i32 0, i32 0), i64 28 }, %str_slice { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @str.1, i32 0, i32 0), i64 10 }, i32 3 }, align 8
@str.4 = internal constant [32 x i8] c"assertion failed: sum(3, 4) == 7"
@_ZN7example12foo_test_sum10_FILE_LINE17h710238568b16f65dE = internal constant { %str_slice, i32, [4 x i8] } { %str_slice { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @str.1, i32 0, i32 0), i64 10 }, i32 8, [4 x i8] undef }, align 8
@str.5 = internal constant [12 x i8] c"foo_test_sum"
@ref.6 = internal unnamed_addr constant { { { { i64, %str_slice, [8 x i8] }, i1, [7 x i8], { i64, [16 x i8] } }, { i64, void ()*, [8 x i8] } } } { { { { i64, %str_slice, [8 x i8] }, i1, [7 x i8], { i64, [16 x i8] } }, { i64, void ()*, [8 x i8] } } { { { i64, %str_slice, [8 x i8] }, i1, [7 x i8], { i64, [16 x i8] } } { { i64, %str_slice, [8 x i8] } { i64 0, %str_slice { i8* getelementptr inbounds ([12 x i8], [12 x i8]* @str.5, i32 0, i32 0), i64 12 }, [8 x i8] undef }, i1 false, [7 x i8] undef, { i64, [16 x i8] } { i64 0, [16 x i8] undef } }, { i64, void ()*, [8 x i8] } { i64 0, void ()* @_ZN7example12foo_test_sum17h5bd19e140b55e128E, [8 x i8] undef } } }, align 8

; Function Attrs: uwtable
define internal i64 @"_ZN36_$LT$T$u20$as$u20$core..any..Any$GT$11get_type_id17h4bed9676a70da661E"(%str_slice* noalias readonly dereferenceable(16)) unnamed_addr #0 !dbg !25 {
entry-block:
  %arg0 = alloca %str_slice*
  %_0 = alloca %"2.std::any::TypeId"
  %self = alloca %str_slice*
  %abi_cast = alloca i64
  store %str_slice* %0, %str_slice** %arg0
  call void @llvm.dbg.declare(metadata %str_slice** %arg0, metadata !39, metadata !40), !dbg !41
  call void @llvm.dbg.declare(metadata %str_slice** %self, metadata !42, metadata !40), !dbg !44
  br label %start

start:                                            ; preds = %entry-block
  %1 = load %str_slice*, %str_slice** %arg0, !dbg !45, !nonnull !5
  store %str_slice* %1, %str_slice** %self, !dbg !45
  %2 = call i64 @_ZN4core3any6TypeId2of17hbcd2920c2d5de549E(), !dbg !44
  store i64 %2, i64* %abi_cast, !dbg !44
  %3 = bitcast %"2.std::any::TypeId"* %_0 to i8*, !dbg !44
  %4 = bitcast i64* %abi_cast to i8*, !dbg !44
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* %4, i64 8, i32 8, i1 false), !dbg !44
  br label %bb1, !dbg !44

bb1:                                              ; preds = %start
  %5 = bitcast %"2.std::any::TypeId"* %_0 to i64*, !dbg !44
  %6 = load i64, i64* %5, align 8, !dbg !44
  ret i64 %6, !dbg !44
}

; Function Attrs: cold noinline noreturn uwtable
define internal void @_ZN3std9panicking11begin_panic17h634e2b37a96f78d4E(i8* noalias nonnull readonly, i64, { %str_slice, i32 }* noalias readonly dereferenceable(24)) unnamed_addr #1 personality i32 (i32, i32, i64, %"8.unwind::libunwind::_Unwind_Exception"*, %"8.unwind::libunwind::_Unwind_Context"*)* @rust_eh_personality !dbg !46 {
entry-block:
  %arg0.i = alloca %str_slice
  call void @llvm.dbg.declare(metadata %str_slice* %arg0.i, metadata !56, metadata !40), !dbg !65
  %x.i = alloca %str_slice
  call void @llvm.dbg.declare(metadata %str_slice* %x.i, metadata !68, metadata !40), !dbg !70
  %arg0 = alloca %str_slice
  %arg1 = alloca { %str_slice, i32 }*
  %msg = alloca %str_slice
  %file_line = alloca { %str_slice, i32 }*
  %personalityslot = alloca { i8*, i32 }
  %3 = getelementptr inbounds %str_slice, %str_slice* %arg0, i32 0, i32 0
  store i8* %0, i8** %3
  %4 = getelementptr inbounds %str_slice, %str_slice* %arg0, i32 0, i32 1
  store i64 %1, i64* %4
  call void @llvm.dbg.declare(metadata %str_slice* %arg0, metadata !71, metadata !40), !dbg !72
  store { %str_slice, i32 }* %2, { %str_slice, i32 }** %arg1
  call void @llvm.dbg.declare(metadata { %str_slice, i32 }** %arg1, metadata !73, metadata !40), !dbg !72
  call void @llvm.dbg.declare(metadata %str_slice* %msg, metadata !74, metadata !40), !dbg !75
  call void @llvm.dbg.declare(metadata { %str_slice, i32 }** %file_line, metadata !76, metadata !40), !dbg !75
  br label %start

start:                                            ; preds = %entry-block
  %5 = getelementptr inbounds %str_slice, %str_slice* %arg0, i32 0, i32 0, !dbg !77
  %6 = load i8*, i8** %5, !dbg !77, !nonnull !5
  %7 = getelementptr inbounds %str_slice, %str_slice* %arg0, i32 0, i32 1, !dbg !77
  %8 = load i64, i64* %7, !dbg !77
  %9 = getelementptr inbounds %str_slice, %str_slice* %msg, i32 0, i32 0, !dbg !77
  store i8* %6, i8** %9, !dbg !77
  %10 = getelementptr inbounds %str_slice, %str_slice* %msg, i32 0, i32 1, !dbg !77
  store i64 %8, i64* %10, !dbg !77
  %11 = load { %str_slice, i32 }*, { %str_slice, i32 }** %arg1, !dbg !77, !nonnull !5
  store { %str_slice, i32 }* %11, { %str_slice, i32 }** %file_line, !dbg !77
  %12 = getelementptr inbounds %str_slice, %str_slice* %msg, i32 0, i32 0, !dbg !78
  %13 = load i8*, i8** %12, !dbg !78, !nonnull !5
  %14 = getelementptr inbounds %str_slice, %str_slice* %msg, i32 0, i32 1, !dbg !78
  %15 = load i64, i64* %14, !dbg !78
  %16 = getelementptr inbounds %str_slice, %str_slice* %arg0.i, i32 0, i32 0, !dbg !78
  store i8* %13, i8** %16, !dbg !78, !noalias !79
  %17 = getelementptr inbounds %str_slice, %str_slice* %arg0.i, i32 0, i32 1, !dbg !78
  store i64 %15, i64* %17, !dbg !78, !noalias !79
  %18 = getelementptr inbounds %str_slice, %str_slice* %arg0.i, i32 0, i32 0, !dbg !82
  %19 = load i8*, i8** %18, !dbg !82, !noalias !79, !nonnull !5
  %20 = getelementptr inbounds %str_slice, %str_slice* %arg0.i, i32 0, i32 1, !dbg !82
  %21 = load i64, i64* %20, !dbg !82, !noalias !79
  %22 = getelementptr inbounds %str_slice, %str_slice* %x.i, i32 0, i32 0, !dbg !82
  store i8* %19, i8** %22, !dbg !82, !noalias !79
  %23 = getelementptr inbounds %str_slice, %str_slice* %x.i, i32 0, i32 1, !dbg !82
  store i64 %21, i64* %23, !dbg !82, !noalias !79
  %24 = invoke i8* @_ZN5alloc4heap15exchange_malloc17h48324f7e7f415602E(i64 16, i64 8)
          to label %"_ZN5alloc5boxed30_$LT$impl$u20$Box$LT$T$GT$$GT$3new17h206de9ebd9c06f29E.exit" unwind label %cleanup, !dbg !83

"_ZN5alloc5boxed30_$LT$impl$u20$Box$LT$T$GT$$GT$3new17h206de9ebd9c06f29E.exit": ; preds = %start
  %25 = bitcast i8* %24 to %str_slice*, !dbg !83
  %26 = getelementptr inbounds %str_slice, %str_slice* %x.i, i32 0, i32 0, !dbg !83
  %27 = load i8*, i8** %26, !dbg !83, !noalias !79, !nonnull !5
  %28 = getelementptr inbounds %str_slice, %str_slice* %x.i, i32 0, i32 1, !dbg !83
  %29 = load i64, i64* %28, !dbg !83, !noalias !79
  %30 = getelementptr inbounds %str_slice, %str_slice* %25, i32 0, i32 0, !dbg !83
  store i8* %27, i8** %30, !dbg !83
  %31 = getelementptr inbounds %str_slice, %str_slice* %25, i32 0, i32 1, !dbg !83
  store i64 %29, i64* %31, !dbg !83
  br label %bb2, !dbg !84

bb1:                                              ; preds = %cleanup
  %32 = load { i8*, i32 }, { i8*, i32 }* %personalityslot, !dbg !77
  resume { i8*, i32 } %32, !dbg !77

bb2:                                              ; preds = %"_ZN5alloc5boxed30_$LT$impl$u20$Box$LT$T$GT$$GT$3new17h206de9ebd9c06f29E.exit"
  %33 = bitcast %str_slice* %25 to i8*, !dbg !78
  %34 = load { %str_slice, i32 }*, { %str_slice, i32 }** %file_line, !dbg !78, !nonnull !5
  invoke void @_ZN3std9panicking20rust_panic_with_hook17h109e116a3a861224E(i8* noalias nonnull %33, void (i8*)** nonnull getelementptr inbounds ({ void (i8*)*, i64, i64, i64 (%str_slice*)* }, { void (i8*)*, i64, i64, i64 (%str_slice*)* }* @vtable.0, i32 0, i32 0), { %str_slice, i32 }* noalias readonly dereferenceable(24) %34)
          to label %unreachable unwind label %cleanup, !dbg !78

cleanup:                                          ; preds = %start, %bb2
  %35 = landingpad { i8*, i32 }
          cleanup
  store { i8*, i32 } %35, { i8*, i32 }* %personalityslot
  br label %bb1

unreachable:                                      ; preds = %bb2
  unreachable
}

; Function Attrs: uwtable
define internal i64 @_ZN4core3any6TypeId2of17hbcd2920c2d5de549E() unnamed_addr #0 !dbg !85 {
entry-block:
  %_0 = alloca %"2.std::any::TypeId"
  %tmp_ret = alloca i64
  br label %start

start:                                            ; preds = %entry-block
  store i64 3020856465566936866, i64* %tmp_ret
  %0 = load i64, i64* %tmp_ret, !dbg !88
  br label %bb1, !dbg !88

bb1:                                              ; preds = %start
  %1 = getelementptr inbounds %"2.std::any::TypeId", %"2.std::any::TypeId"* %_0, i32 0, i32 0, !dbg !89
  store i64 %0, i64* %1, !dbg !89
  %2 = bitcast %"2.std::any::TypeId"* %_0 to i64*, !dbg !90
  %3 = load i64, i64* %2, align 8, !dbg !90
  ret i64 %3, !dbg !90
}

; Function Attrs: inlinehint uwtable
define internal zeroext i1 @"_ZN4core3ptr31_$LT$impl$u20$$BP$mut$u20$T$GT$7is_null17h0e69dab9481e4a3cE"(i8*) unnamed_addr #2 !dbg !91 {
entry-block:
  %arg0 = alloca i8*
  %self = alloca i8*
  store i8* %0, i8** %arg0
  call void @llvm.dbg.declare(metadata i8** %arg0, metadata !101, metadata !40), !dbg !102
  call void @llvm.dbg.declare(metadata i8** %self, metadata !103, metadata !40), !dbg !105
  br label %start

start:                                            ; preds = %entry-block
  %1 = load i8*, i8** %arg0, !dbg !106
  store i8* %1, i8** %self, !dbg !106
  %2 = load i8*, i8** %self, !dbg !107
  %3 = call i8* @_ZN4core3ptr8null_mut17h6b7dc6e8748e0386E(), !dbg !107
  br label %bb1, !dbg !107

bb1:                                              ; preds = %start
  %4 = icmp eq i8* %2, %3, !dbg !107
  ret i1 %4, !dbg !108
}

; Function Attrs: inlinehint uwtable
define internal i8* @_ZN4core3ptr8null_mut17h6b7dc6e8748e0386E() unnamed_addr #2 !dbg !109 {
entry-block:
  br label %start

start:                                            ; preds = %entry-block
  ret i8* null, !dbg !112
}

define internal void @_ZN4drop17h7115f936263dd8e8E(i8*) unnamed_addr #3 {
entry-block:
  ret void
}

; Function Attrs: inlinehint uwtable
define internal i8* @_ZN5alloc4heap15exchange_malloc17h48324f7e7f415602E(i64, i64) unnamed_addr #2 !dbg !113 {
entry-block:
  %arg0 = alloca i64
  %arg1 = alloca i64
  %_0 = alloca i8*
  %size = alloca i64
  %align = alloca i64
  %ptr = alloca i8*
  %_10 = alloca {}
  store i64 %0, i64* %arg0
  call void @llvm.dbg.declare(metadata i64* %arg0, metadata !118, metadata !40), !dbg !119
  store i64 %1, i64* %arg1
  call void @llvm.dbg.declare(metadata i64* %arg1, metadata !120, metadata !40), !dbg !119
  call void @llvm.dbg.declare(metadata i64* %size, metadata !121, metadata !40), !dbg !123
  call void @llvm.dbg.declare(metadata i64* %align, metadata !124, metadata !40), !dbg !123
  call void @llvm.dbg.declare(metadata i8** %ptr, metadata !125, metadata !40), !dbg !127
  br label %start

start:                                            ; preds = %entry-block
  %2 = load i64, i64* %arg0, !dbg !128
  store i64 %2, i64* %size, !dbg !128
  %3 = load i64, i64* %arg1, !dbg !128
  store i64 %3, i64* %align, !dbg !128
  %4 = load i64, i64* %size, !dbg !129
  %5 = icmp eq i64 %4, 0, !dbg !129
  br i1 %5, label %bb1, label %bb2, !dbg !129

bb1:                                              ; preds = %start
  store i8* inttoptr (i64 1 to i8*), i8** %_0, !dbg !130
  br label %bb7, !dbg !129

bb2:                                              ; preds = %start
  %6 = load i64, i64* %size, !dbg !131
  %7 = load i64, i64* %align, !dbg !131
  %8 = call i8* @_ZN5alloc4heap8allocate17h36ab8478f42466f5E(i64 %6, i64 %7), !dbg !131
  store i8* %8, i8** %ptr, !dbg !131
  br label %bb3, !dbg !131

bb3:                                              ; preds = %bb2
  %9 = load i8*, i8** %ptr, !dbg !132
  %10 = call zeroext i1 @"_ZN4core3ptr31_$LT$impl$u20$$BP$mut$u20$T$GT$7is_null17h0e69dab9481e4a3cE"(i8* %9), !dbg !132
  br label %bb4, !dbg !132

bb4:                                              ; preds = %bb3
  br i1 %10, label %bb5, label %bb6, !dbg !132

bb5:                                              ; preds = %bb4
  call void @_ZN5alloc3oom3oom17hcac7549e1d9cf2ccE(), !dbg !133
  unreachable, !dbg !133

bb6:                                              ; preds = %bb4
  %11 = load i8*, i8** %ptr, !dbg !134
  store i8* %11, i8** %_0, !dbg !134
  br label %bb7, !dbg !129

bb7:                                              ; preds = %bb1, %bb6
  %12 = load i8*, i8** %_0, !dbg !135
  ret i8* %12, !dbg !135
}

; Function Attrs: inlinehint uwtable
define internal i8* @_ZN5alloc4heap8allocate17h36ab8478f42466f5E(i64, i64) unnamed_addr #2 !dbg !136 {
entry-block:
  %arg0.i = alloca i64
  call void @llvm.dbg.declare(metadata i64* %arg0.i, metadata !137, metadata !40), !dbg !141
  %arg1.i = alloca i64
  call void @llvm.dbg.declare(metadata i64* %arg1.i, metadata !144, metadata !40), !dbg !141
  %_0.i = alloca {}
  %size.i = alloca i64
  call void @llvm.dbg.declare(metadata i64* %size.i, metadata !145, metadata !40), !dbg !147
  %align.i = alloca i64
  call void @llvm.dbg.declare(metadata i64* %align.i, metadata !148, metadata !40), !dbg !147
  %_5.i = alloca {}
  %_6.i = alloca {}
  %_7.i = alloca {}
  %arg0 = alloca i64
  %arg1 = alloca i64
  %size = alloca i64
  %align = alloca i64
  store i64 %0, i64* %arg0
  call void @llvm.dbg.declare(metadata i64* %arg0, metadata !149, metadata !40), !dbg !150
  store i64 %1, i64* %arg1
  call void @llvm.dbg.declare(metadata i64* %arg1, metadata !151, metadata !40), !dbg !150
  call void @llvm.dbg.declare(metadata i64* %size, metadata !152, metadata !40), !dbg !153
  call void @llvm.dbg.declare(metadata i64* %align, metadata !154, metadata !40), !dbg !153
  br label %start

start:                                            ; preds = %entry-block
  %2 = load i64, i64* %arg0, !dbg !155
  store i64 %2, i64* %size, !dbg !155
  %3 = load i64, i64* %arg1, !dbg !155
  store i64 %3, i64* %align, !dbg !155
  %4 = load i64, i64* %size, !dbg !156
  %5 = load i64, i64* %align, !dbg !156
  store i64 %4, i64* %arg0.i, !dbg !156
  store i64 %5, i64* %arg1.i, !dbg !156
  %6 = load i64, i64* %arg0.i, !dbg !157
  store i64 %6, i64* %size.i, !dbg !157
  %7 = load i64, i64* %arg1.i, !dbg !157
  store i64 %7, i64* %align.i, !dbg !157
  br label %bb1, !dbg !156

bb1:                                              ; preds = %start
  %8 = load i64, i64* %size, !dbg !158
  %9 = load i64, i64* %align, !dbg !158
  %10 = call i8* @__rust_allocate(i64 %8, i64 %9), !dbg !158
  br label %bb2, !dbg !158

bb2:                                              ; preds = %bb1
  ret i8* %10, !dbg !159
}

; Function Attrs: uwtable
define internal i32 @_ZN7example3sum17hf4e2be639b15369cE(i32, i32) unnamed_addr #0 !dbg !160 {
entry-block:
  %arg0 = alloca i32
  %arg1 = alloca i32
  %a = alloca i32
  %b = alloca i32
  store i32 %0, i32* %arg0
  call void @llvm.dbg.declare(metadata i32* %arg0, metadata !164, metadata !40), !dbg !165
  store i32 %1, i32* %arg1
  call void @llvm.dbg.declare(metadata i32* %arg1, metadata !166, metadata !40), !dbg !165
  call void @llvm.dbg.declare(metadata i32* %a, metadata !167, metadata !40), !dbg !169
  call void @llvm.dbg.declare(metadata i32* %b, metadata !170, metadata !40), !dbg !169
  br label %start

start:                                            ; preds = %entry-block
  %2 = load i32, i32* %arg0, !dbg !171
  store i32 %2, i32* %a, !dbg !171
  %3 = load i32, i32* %arg1, !dbg !171
  store i32 %3, i32* %b, !dbg !171
  %4 = load i32, i32* %a, !dbg !172
  %5 = load i32, i32* %b, !dbg !172
  %6 = call { i32, i1 } @llvm.sadd.with.overflow.i32(i32 %4, i32 %5), !dbg !172
  %7 = extractvalue { i32, i1 } %6, 0, !dbg !172
  %8 = extractvalue { i32, i1 } %6, 1, !dbg !172
  %9 = call i1 @llvm.expect.i1(i1 %8, i1 false), !dbg !172
  br i1 %9, label %panic, label %bb1, !dbg !172

bb1:                                              ; preds = %start
  ret i32 %7, !dbg !173

panic:                                            ; preds = %start
  call void @_ZN4core9panicking5panic17hd383cb12a44b01ffE({ %str_slice, %str_slice, i32 }* @panic_loc.3), !dbg !172
  unreachable, !dbg !172
}

; Function Attrs: uwtable
define internal void @_ZN7example12foo_test_sum17h5bd19e140b55e128E() unnamed_addr #0 !dbg !174 {
entry-block:
  %_0 = alloca {}
  %_1 = alloca {}
  br label %start

start:                                            ; preds = %entry-block
  %0 = call i32 @_ZN7example3sum17hf4e2be639b15369cE(i32 3, i32 4), !dbg !177
  br label %bb1, !dbg !177

bb1:                                              ; preds = %start
  %1 = icmp eq i32 %0, 7, !dbg !177
  %2 = xor i1 %1, true, !dbg !177
  br i1 %2, label %bb2, label %bb3, !dbg !177

bb2:                                              ; preds = %bb1
  call void @_ZN3std9panicking11begin_panic17h634e2b37a96f78d4E(i8* noalias nonnull readonly getelementptr inbounds ([32 x i8], [32 x i8]* @str.4, i32 0, i32 0), i64 32, { %str_slice, i32 }* noalias readonly dereferenceable(24) bitcast ({ %str_slice, i32, [4 x i8] }* @_ZN7example12foo_test_sum10_FILE_LINE17h710238568b16f65dE to { %str_slice, i32 }*)), !dbg !177
  unreachable, !dbg !177

bb3:                                              ; preds = %bb1
  ret void, !dbg !178
}

; Function Attrs: uwtable
define internal void @_ZN7example6__test4main17h2a7ca5b1ce24a7fdE() unnamed_addr #0 !dbg !179 {
entry-block:
  br label %start

start:                                            ; preds = %entry-block
  call void @_ZN4test16test_main_static17h9317ea9d7ac82cffE(%"12.__test::test::TestDescAndFn"* noalias nonnull readonly bitcast ({ { { { i64, %str_slice, [8 x i8] }, i1, [7 x i8], { i64, [16 x i8] } }, { i64, void ()*, [8 x i8] } } }* @ref.6 to %"12.__test::test::TestDescAndFn"*), i64 1), !dbg !181
  br label %bb1, !dbg !181

bb1:                                              ; preds = %start
  ret void, !dbg !181
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind
declare i32 @rust_eh_personality(i32, i32, i64, %"8.unwind::libunwind::_Unwind_Exception"*, %"8.unwind::libunwind::_Unwind_Context"*) unnamed_addr #6

; Function Attrs: cold noinline noreturn
declare void @_ZN3std9panicking20rust_panic_with_hook17h109e116a3a861224E(i8* noalias nonnull, void (i8*)** nonnull, { %str_slice, i32 }* noalias readonly dereferenceable(24)) unnamed_addr #7

; Function Attrs: cold noinline noreturn
declare void @_ZN5alloc3oom3oom17hcac7549e1d9cf2ccE() unnamed_addr #7

; Function Attrs: nounwind
declare noalias i8* @__rust_allocate(i64, i64) unnamed_addr #6

; Function Attrs: nounwind readnone
declare { i32, i1 } @llvm.sadd.with.overflow.i32(i32, i32) #4

; Function Attrs: nounwind readnone
declare i1 @llvm.expect.i1(i1, i1) #4

; Function Attrs: cold noinline noreturn
declare void @_ZN4core9panicking5panic17hd383cb12a44b01ffE({ %str_slice, %str_slice, i32 }* noalias readonly dereferenceable(40)) unnamed_addr #7

declare void @_ZN4test16test_main_static17h9317ea9d7ac82cffE(%"12.__test::test::TestDescAndFn"* noalias nonnull readonly, i64) unnamed_addr #3

define i64 @main(i64, i8**) unnamed_addr #3 {
top:
  %2 = call i64 @_ZN3std2rt10lang_start17hd661476ce2fc2931E(i8* bitcast (void ()* @_ZN7example6__test4main17h2a7ca5b1ce24a7fdE to i8*), i64 %0, i8** %1)
  ret i64 %2
}

declare i64 @_ZN3std2rt10lang_start17hd661476ce2fc2931E(i8*, i64, i8**) unnamed_addr #3

attributes #0 = { uwtable "no-frame-pointer-elim"="true" }
attributes #1 = { cold noinline noreturn uwtable "no-frame-pointer-elim"="true" }
attributes #2 = { inlinehint uwtable "no-frame-pointer-elim"="true" }
attributes #3 = { "no-frame-pointer-elim"="true" }
attributes #4 = { nounwind readnone }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind "no-frame-pointer-elim"="true" }
attributes #7 = { cold noinline noreturn "no-frame-pointer-elim"="true" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.dbg.cu = !{!3}

!0 = !{i32 1, !"PIE Level", i32 2}
!1 = !{i32 2, !"Dwarf Version", i32 2}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = distinct !DICompileUnit(language: DW_LANG_Rust, file: !4, producer: "rustc version 1.14.0 (e8a012324 2016-12-16)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !5, globals: !6)
!4 = !DIFile(filename: "./example.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!5 = !{}
!6 = !{!7}
!7 = distinct !DIGlobalVariable(name: "_FILE_LINE", linkageName: "_ZN7example12foo_test_sum10_FILE_LINEE", scope: !8, file: !12, line: 5, type: !13, isLocal: true, isDefinition: true, variable: { %str_slice, i32, [4 x i8] }* @_ZN7example12foo_test_sum10_FILE_LINE17h710238568b16f65dE)
!8 = !DINamespace(name: "foo_test_sum", scope: !10, file: !9, line: 7)
!9 = !DIFile(filename: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust/example.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!10 = !DINamespace(name: "example", scope: null, file: !11)
!11 = !DIFile(filename: "<unknown>", directory: "")
!12 = !DIFile(filename: "<std macros>", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!13 = !DICompositeType(tag: DW_TAG_structure_type, name: "(&str, u32)", file: !11, size: 192, align: 64, elements: !14, identifier: "c5cde3a439cadccb7a27333adc9bf57da4510cb")
!14 = !{!15, !23}
!15 = !DIDerivedType(tag: DW_TAG_member, name: "__0", scope: !13, file: !11, baseType: !16, size: 128, align: 64)
!16 = !DICompositeType(tag: DW_TAG_structure_type, name: "&str", file: !11, size: 128, align: 64, elements: !17, identifier: "ba943fec7ffec6f5b5383b3687bffbb545ec77f")
!17 = !{!18, !21}
!18 = !DIDerivedType(tag: DW_TAG_member, name: "data_ptr", scope: !16, file: !11, baseType: !19, size: 64, align: 64)
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "*const u8", baseType: !20, size: 64, align: 64)
!20 = !DIBasicType(name: "u8", size: 8, align: 8, encoding: DW_ATE_unsigned)
!21 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !16, file: !11, baseType: !22, size: 64, align: 64, offset: 64)
!22 = !DIBasicType(name: "usize", size: 64, align: 64, encoding: DW_ATE_unsigned)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "__1", scope: !13, file: !11, baseType: !24, size: 32, align: 32, offset: 128)
!24 = !DIBasicType(name: "u32", size: 32, align: 32, encoding: DW_ATE_unsigned)
!25 = distinct !DISubprogram(name: "get_type_id<&str>", linkageName: "_ZN4core3any8{{impl}}17get_type_id<&str>E", scope: !27, file: !26, line: 115, type: !30, isLocal: false, isDefinition: true, scopeLine: 115, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !37, variables: !5)
!26 = !DIFile(filename: "/Users/rustbuild/src/rust-buildbot/slave/stable-dist-rustc-mac/build/obj/../src/libcore/any.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!27 = !DINamespace(name: "{{impl}}", scope: !28, file: !11)
!28 = !DINamespace(name: "any", scope: !29, file: !11)
!29 = !DINamespace(name: "core", scope: null, file: !11)
!30 = !DISubroutineType(types: !31)
!31 = !{!32, !36}
!32 = !DICompositeType(tag: DW_TAG_structure_type, name: "TypeId", scope: !28, file: !11, size: 64, align: 64, elements: !33, identifier: "bf7d48731e03b6e1cedb66ee729d6c6f41787c")
!33 = !{!34}
!34 = !DIDerivedType(tag: DW_TAG_member, name: "t", scope: !32, file: !11, baseType: !35, size: 64, align: 64)
!35 = !DIBasicType(name: "u64", size: 64, align: 64, encoding: DW_ATE_unsigned)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "&&str", baseType: !16, size: 64, align: 64)
!37 = !{!38}
!38 = !DITemplateTypeParameter(name: "T", type: !16)
!39 = !DILocalVariable(name: "self", arg: 1, scope: !25, file: !9, line: 1, type: !36)
!40 = !DIExpression()
!41 = !DILocation(line: 1, scope: !25)
!42 = !DILocalVariable(name: "self", scope: !43, file: !26, line: 115, type: !36)
!43 = distinct !DILexicalBlock(scope: !25, file: !26, line: 115, column: 36)
!44 = !DILocation(line: 115, scope: !43)
!45 = !DILocation(line: 115, scope: !25)
!46 = distinct !DISubprogram(name: "begin_panic<&str>", linkageName: "_ZN3std9panicking17begin_panic<&str>E", scope: !48, file: !47, line: 405, type: !50, isLocal: false, isDefinition: true, scopeLine: 405, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !54, variables: !5)
!47 = !DIFile(filename: "/Users/rustbuild/src/rust-buildbot/slave/stable-dist-rustc-mac/build/obj/../src/libstd/panicking.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!48 = !DINamespace(name: "panicking", scope: !49, file: !11)
!49 = !DINamespace(name: "std", scope: null, file: !11)
!50 = !DISubroutineType(types: !51)
!51 = !{!52, !16, !53}
!52 = !DIBasicType(name: "!", align: 8, encoding: DW_ATE_unsigned)
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "&(&str, u32)", baseType: !13, size: 64, align: 64)
!54 = !{!55}
!55 = !DITemplateTypeParameter(name: "M", type: !16)
!56 = !DILocalVariable(name: "x", arg: 1, scope: !57, file: !9, line: 1, type: !16)
!57 = distinct !DISubprogram(name: "new<&str>", linkageName: "_ZN5alloc5boxed8{{impl}}9new<&str>E", scope: !59, file: !58, line: 234, type: !62, isLocal: false, isDefinition: true, scopeLine: 234, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !37, variables: !5)
!58 = !DIFile(filename: "/Users/rustbuild/src/rust-buildbot/slave/stable-dist-rustc-mac/build/obj/../src/liballoc/boxed.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!59 = !DINamespace(name: "{{impl}}", scope: !60, file: !11)
!60 = !DINamespace(name: "boxed", scope: !61, file: !11)
!61 = !DINamespace(name: "alloc", scope: null, file: !11)
!62 = !DISubroutineType(types: !63)
!63 = !{!64, !16}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "Box<&str>", baseType: !16, size: 64, align: 64)
!65 = !DILocation(line: 1, scope: !57, inlinedAt: !66)
!66 = distinct !DILocation(line: 413, scope: !67)
!67 = distinct !DILexicalBlock(scope: !46, file: !47, line: 405, column: 80)
!68 = !DILocalVariable(name: "x", scope: !69, file: !58, line: 234, type: !16)
!69 = distinct !DILexicalBlock(scope: !57, file: !58, line: 234, column: 31)
!70 = !DILocation(line: 234, scope: !69, inlinedAt: !66)
!71 = !DILocalVariable(name: "msg", arg: 1, scope: !46, file: !9, line: 1, type: !16)
!72 = !DILocation(line: 1, scope: !46)
!73 = !DILocalVariable(name: "file_line", arg: 2, scope: !46, file: !9, line: 1, type: !53)
!74 = !DILocalVariable(name: "msg", scope: !67, file: !47, line: 405, type: !16)
!75 = !DILocation(line: 405, scope: !67)
!76 = !DILocalVariable(name: "file_line", scope: !67, file: !47, line: 405, type: !53)
!77 = !DILocation(line: 405, scope: !46)
!78 = !DILocation(line: 413, scope: !67)
!79 = !{!80}
!80 = distinct !{!80, !81, !"_ZN5alloc5boxed30_$LT$impl$u20$Box$LT$T$GT$$GT$3new17h206de9ebd9c06f29E: argument 0"}
!81 = distinct !{!81, !"_ZN5alloc5boxed30_$LT$impl$u20$Box$LT$T$GT$$GT$3new17h206de9ebd9c06f29E"}
!82 = !DILocation(line: 234, scope: !57, inlinedAt: !66)
!83 = !DILocation(line: 235, scope: !69, inlinedAt: !66)
!84 = !DILocation(line: 236, scope: !69, inlinedAt: !66)
!85 = distinct !DISubprogram(name: "of<&str>", linkageName: "_ZN4core3any8{{impl}}8of<&str>E", scope: !32, file: !26, line: 366, type: !86, isLocal: false, isDefinition: true, scopeLine: 366, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !37, variables: !5)
!86 = !DISubroutineType(types: !87)
!87 = !{!32}
!88 = !DILocation(line: 368, scope: !85)
!89 = !DILocation(line: 367, scope: !85)
!90 = !DILocation(line: 370, scope: !85)
!91 = distinct !DISubprogram(name: "is_null<u8>", linkageName: "_ZN4core3ptr8{{impl}}11is_null<u8>E", scope: !93, file: !92, line: 404, type: !95, isLocal: false, isDefinition: true, scopeLine: 404, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !99, variables: !5)
!92 = !DIFile(filename: "/Users/rustbuild/src/rust-buildbot/slave/stable-dist-rustc-mac/build/obj/../src/libcore/ptr.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!93 = !DINamespace(name: "{{impl}}", scope: !94, file: !11)
!94 = !DINamespace(name: "ptr", scope: !29, file: !11)
!95 = !DISubroutineType(types: !96)
!96 = !{!97, !98}
!97 = !DIBasicType(name: "bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "*mut u8", baseType: !20, size: 64, align: 64)
!99 = !{!100}
!100 = !DITemplateTypeParameter(name: "T", type: !20)
!101 = !DILocalVariable(name: "self", arg: 1, scope: !91, file: !9, line: 1, type: !98)
!102 = !DILocation(line: 1, scope: !91)
!103 = !DILocalVariable(name: "self", scope: !104, file: !92, line: 404, type: !98)
!104 = distinct !DILexicalBlock(scope: !91, file: !92, line: 404, column: 48)
!105 = !DILocation(line: 404, scope: !104)
!106 = !DILocation(line: 404, scope: !91)
!107 = !DILocation(line: 405, scope: !104)
!108 = !DILocation(line: 406, scope: !104)
!109 = distinct !DISubprogram(name: "null_mut<u8>", linkageName: "_ZN4core3ptr12null_mut<u8>E", scope: !94, file: !92, line: 69, type: !110, isLocal: false, isDefinition: true, scopeLine: 69, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !99, variables: !5)
!110 = !DISubroutineType(types: !111)
!111 = !{!98}
!112 = !DILocation(line: 69, scope: !109)
!113 = distinct !DISubprogram(name: "exchange_malloc", linkageName: "_ZN5alloc4heap15exchange_mallocE", scope: !115, file: !114, line: 133, type: !116, isLocal: false, isDefinition: true, scopeLine: 133, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !5, variables: !5)
!114 = !DIFile(filename: "/Users/rustbuild/src/rust-buildbot/slave/stable-dist-rustc-mac/build/obj/../src/liballoc/heap.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!115 = !DINamespace(name: "heap", scope: !61, file: !11)
!116 = !DISubroutineType(types: !117)
!117 = !{!98, !22, !22}
!118 = !DILocalVariable(name: "size", arg: 1, scope: !113, file: !9, line: 1, type: !22)
!119 = !DILocation(line: 1, scope: !113)
!120 = !DILocalVariable(name: "align", arg: 2, scope: !113, file: !9, line: 1, type: !22)
!121 = !DILocalVariable(name: "size", scope: !122, file: !114, line: 133, type: !22)
!122 = distinct !DILexicalBlock(scope: !113, file: !114, line: 133, column: 64)
!123 = !DILocation(line: 133, scope: !122)
!124 = !DILocalVariable(name: "align", scope: !122, file: !114, line: 133, type: !22)
!125 = !DILocalVariable(name: "ptr", scope: !126, file: !114, line: 137, type: !98)
!126 = distinct !DILexicalBlock(scope: !122, file: !114, line: 137, column: 40)
!127 = !DILocation(line: 137, scope: !126)
!128 = !DILocation(line: 133, scope: !113)
!129 = !DILocation(line: 134, scope: !122)
!130 = !DILocation(line: 135, scope: !122)
!131 = !DILocation(line: 137, scope: !122)
!132 = !DILocation(line: 138, scope: !126)
!133 = !DILocation(line: 139, scope: !126)
!134 = !DILocation(line: 141, scope: !126)
!135 = !DILocation(line: 143, scope: !122)
!136 = distinct !DISubprogram(name: "allocate", linkageName: "_ZN5alloc4heap8allocateE", scope: !115, file: !114, line: 57, type: !116, isLocal: false, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !5, variables: !5)
!137 = !DILocalVariable(name: "size", arg: 1, scope: !138, file: !9, line: 1, type: !22)
!138 = distinct !DISubprogram(name: "check_size_and_alignment", linkageName: "_ZN5alloc4heap24check_size_and_alignmentE", scope: !115, file: !114, line: 37, type: !139, isLocal: false, isDefinition: true, scopeLine: 37, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !5, variables: !5)
!139 = !DISubroutineType(types: !140)
!140 = !{null, !22, !22}
!141 = !DILocation(line: 1, scope: !138, inlinedAt: !142)
!142 = distinct !DILocation(line: 58, scope: !143)
!143 = distinct !DILexicalBlock(scope: !136, file: !114, line: 57, column: 61)
!144 = !DILocalVariable(name: "align", arg: 2, scope: !138, file: !9, line: 1, type: !22)
!145 = !DILocalVariable(name: "size", scope: !146, file: !114, line: 37, type: !22)
!146 = distinct !DILexicalBlock(scope: !138, file: !114, line: 37, column: 55)
!147 = !DILocation(line: 37, scope: !146, inlinedAt: !142)
!148 = !DILocalVariable(name: "align", scope: !146, file: !114, line: 37, type: !22)
!149 = !DILocalVariable(name: "size", arg: 1, scope: !136, file: !9, line: 1, type: !22)
!150 = !DILocation(line: 1, scope: !136)
!151 = !DILocalVariable(name: "align", arg: 2, scope: !136, file: !9, line: 1, type: !22)
!152 = !DILocalVariable(name: "size", scope: !143, file: !114, line: 57, type: !22)
!153 = !DILocation(line: 57, scope: !143)
!154 = !DILocalVariable(name: "align", scope: !143, file: !114, line: 57, type: !22)
!155 = !DILocation(line: 57, scope: !136)
!156 = !DILocation(line: 58, scope: !143)
!157 = !DILocation(line: 37, scope: !138, inlinedAt: !142)
!158 = !DILocation(line: 59, scope: !143)
!159 = !DILocation(line: 60, scope: !143)
!160 = distinct !DISubprogram(name: "sum", linkageName: "_ZN7example3sumE", scope: !10, file: !9, line: 2, type: !161, isLocal: true, isDefinition: true, scopeLine: 2, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !5, variables: !5)
!161 = !DISubroutineType(types: !162)
!162 = !{!163, !163, !163}
!163 = !DIBasicType(name: "i32", size: 32, align: 32, encoding: DW_ATE_signed)
!164 = !DILocalVariable(name: "a", arg: 1, scope: !160, file: !9, line: 1, type: !163)
!165 = !DILocation(line: 1, scope: !160)
!166 = !DILocalVariable(name: "b", arg: 2, scope: !160, file: !9, line: 1, type: !163)
!167 = !DILocalVariable(name: "a", scope: !168, file: !9, line: 2, type: !163)
!168 = distinct !DILexicalBlock(scope: !160, file: !9, line: 2, column: 34)
!169 = !DILocation(line: 2, scope: !168)
!170 = !DILocalVariable(name: "b", scope: !168, file: !9, line: 2, type: !163)
!171 = !DILocation(line: 2, scope: !160)
!172 = !DILocation(line: 3, scope: !168)
!173 = !DILocation(line: 4, scope: !168)
!174 = distinct !DISubprogram(name: "foo_test_sum", linkageName: "_ZN7example12foo_test_sumE", scope: !10, file: !9, line: 7, type: !175, isLocal: true, isDefinition: true, scopeLine: 7, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !5, variables: !5)
!175 = !DISubroutineType(types: !176)
!176 = !{null}
!177 = !DILocation(line: 8, scope: !174)
!178 = !DILocation(line: 9, scope: !174)
!179 = distinct !DISubprogram(name: "main", linkageName: "_ZN7example6__test4mainE", scope: !180, file: !9, line: 1, type: !175, isLocal: true, isDefinition: true, scopeLine: 1, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !5, variables: !5)
!180 = !DINamespace(name: "__test", scope: !10, file: !11)
!181 = !DILocation(line: 1, scope: !179)
