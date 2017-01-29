; ModuleID = 'example.cgu-0.rs'
source_filename = "example.cgu-0.rs"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-darwin"

%str_slice = type { i8*, i64 }
%"core::any::TypeId" = type { i64 }
%"test::TestDescAndFn" = type { %"test::TestDesc", %"test::TestFn" }
%"test::TestDesc" = type { %"test::TestName", i8, %"test::ShouldPanic" }
%"test::TestName" = type { i64, [0 x i64], [3 x i64] }
%"test::ShouldPanic" = type { i64, [0 x i64], [2 x i64] }
%"test::TestFn" = type { i64, [0 x i64], [2 x i64] }
%"unwind::libunwind::_Unwind_Exception" = type { i64, void (i32, %"unwind::libunwind::_Unwind_Exception"*)*, [6 x i64] }
%"unwind::libunwind::_Unwind_Context" = type {}

@vtable.0 = internal unnamed_addr constant { void (i8*)*, i64, i64, i64 (%str_slice*)* } { void (i8*)* @_ZN4drop17h3f10143eb02d4bbbE, i64 16, i64 8, i64 (%str_slice*)* @"_ZN36_$LT$T$u20$as$u20$core..any..Any$GT$11get_type_id17h231b0be68756ea7dE" }, align 8
@str.1 = internal constant [10 x i8] c"example.rs"
@str.2 = internal constant [28 x i8] c"attempt to add with overflow"
@panic_loc.3 = internal unnamed_addr constant { %str_slice, %str_slice, i32 } { %str_slice { i8* getelementptr inbounds ([28 x i8], [28 x i8]* @str.2, i32 0, i32 0), i64 28 }, %str_slice { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @str.1, i32 0, i32 0), i64 10 }, i32 3 }, align 8
@str.4 = internal constant [32 x i8] c"assertion failed: sum(3, 4) == 7"
@str.5 = internal constant [32 x i8] c"assertion failed: sum(4, 5) == 9"
@_ZN7example17rusttest_foo_sum110_FILE_LINE17h5d1b4176bce6be50E = internal constant { %str_slice, i32, [4 x i8] } { %str_slice { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @str.1, i32 0, i32 0), i64 10 }, i32 8, [4 x i8] undef }, align 8
@_ZN7example17rusttest_foo_sum210_FILE_LINE17h1dfc9fa2411661a7E = internal constant { %str_slice, i32, [4 x i8] } { %str_slice { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @str.1, i32 0, i32 0), i64 10 }, i32 13, [4 x i8] undef }, align 8
@str.6 = internal constant [17 x i8] c"rusttest_foo_sum1"
@str.7 = internal constant [17 x i8] c"rusttest_foo_sum2"
@ref.8 = internal unnamed_addr constant { { { { i64, %str_slice, [8 x i8] }, i1, [7 x i8], { i64, [16 x i8] } }, { i64, void ()*, [8 x i8] } }, { { { i64, %str_slice, [8 x i8] }, i1, [7 x i8], { i64, [16 x i8] } }, { i64, void ()*, [8 x i8] } } } { { { { i64, %str_slice, [8 x i8] }, i1, [7 x i8], { i64, [16 x i8] } }, { i64, void ()*, [8 x i8] } } { { { i64, %str_slice, [8 x i8] }, i1, [7 x i8], { i64, [16 x i8] } } { { i64, %str_slice, [8 x i8] } { i64 0, %str_slice { i8* getelementptr inbounds ([17 x i8], [17 x i8]* @str.6, i32 0, i32 0), i64 17 }, [8 x i8] undef }, i1 false, [7 x i8] undef, { i64, [16 x i8] } { i64 0, [16 x i8] undef } }, { i64, void ()*, [8 x i8] } { i64 0, void ()* @_ZN7example17rusttest_foo_sum117h319bd21b204fd3edE, [8 x i8] undef } }, { { { i64, %str_slice, [8 x i8] }, i1, [7 x i8], { i64, [16 x i8] } }, { i64, void ()*, [8 x i8] } } { { { i64, %str_slice, [8 x i8] }, i1, [7 x i8], { i64, [16 x i8] } } { { i64, %str_slice, [8 x i8] } { i64 0, %str_slice { i8* getelementptr inbounds ([17 x i8], [17 x i8]* @str.7, i32 0, i32 0), i64 17 }, [8 x i8] undef }, i1 false, [7 x i8] undef, { i64, [16 x i8] } { i64 0, [16 x i8] undef } }, { i64, void ()*, [8 x i8] } { i64 0, void ()* @_ZN7example17rusttest_foo_sum217h8c8aeea1b7695792E, [8 x i8] undef } } }, align 8

; Function Attrs: uwtable
define internal i64 @"_ZN36_$LT$T$u20$as$u20$core..any..Any$GT$11get_type_id17h231b0be68756ea7dE"(%str_slice* noalias readonly dereferenceable(16)) unnamed_addr #0 !dbg !27 {
entry-block:
  %abi_cast = alloca i64
  %self = alloca %str_slice*
  %_0 = alloca %"core::any::TypeId"
  %arg0 = alloca %str_slice*
  store %str_slice* %0, %str_slice** %arg0
  call void @llvm.dbg.declare(metadata %str_slice** %arg0, metadata !42, metadata !43), !dbg !44
  call void @llvm.dbg.declare(metadata %str_slice** %self, metadata !45, metadata !43), !dbg !47
  br label %start, !dbg !47

start:                                            ; preds = %entry-block
  %1 = load %str_slice*, %str_slice** %arg0, !dbg !48, !nonnull !5
  store %str_slice* %1, %str_slice** %self, !dbg !48
  %2 = call i64 @_ZN4core3any6TypeId2of17h2a88c185967cf0f1E(), !dbg !47
  store i64 %2, i64* %abi_cast, !dbg !47
  %3 = bitcast %"core::any::TypeId"* %_0 to i8*, !dbg !47
  %4 = bitcast i64* %abi_cast to i8*, !dbg !47
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* %4, i64 8, i32 8, i1 false), !dbg !47
  br label %bb1, !dbg !47

bb1:                                              ; preds = %start
  %5 = bitcast %"core::any::TypeId"* %_0 to i64*, !dbg !47
  %6 = load i64, i64* %5, align 8, !dbg !47
  ret i64 %6, !dbg !47
}

; Function Attrs: cold noinline noreturn uwtable
define internal void @_ZN3std9panicking11begin_panic17h6c6bf73f39cdbdacE(i8* noalias nonnull readonly, i64, { %str_slice, i32 }* noalias readonly dereferenceable(24)) unnamed_addr #1 personality i32 (i32, i32, i64, %"unwind::libunwind::_Unwind_Exception"*, %"unwind::libunwind::_Unwind_Context"*)* @rust_eh_personality !dbg !49 {
entry-block:
  %x.i = alloca %str_slice
  call void @llvm.dbg.declare(metadata %str_slice* %x.i, metadata !60, metadata !43), !dbg !71
  %arg0.i = alloca %str_slice
  call void @llvm.dbg.declare(metadata %str_slice* %arg0.i, metadata !74, metadata !43), !dbg !75
  %personalityslot = alloca { i8*, i32 }
  %file_line = alloca { %str_slice, i32 }*
  %msg = alloca %str_slice
  %arg1 = alloca { %str_slice, i32 }*
  %arg0 = alloca %str_slice
  %3 = getelementptr inbounds %str_slice, %str_slice* %arg0, i32 0, i32 0
  store i8* %0, i8** %3
  %4 = getelementptr inbounds %str_slice, %str_slice* %arg0, i32 0, i32 1
  store i64 %1, i64* %4
  call void @llvm.dbg.declare(metadata %str_slice* %arg0, metadata !76, metadata !43), !dbg !77
  store { %str_slice, i32 }* %2, { %str_slice, i32 }** %arg1
  call void @llvm.dbg.declare(metadata { %str_slice, i32 }** %arg1, metadata !78, metadata !43), !dbg !77
  call void @llvm.dbg.declare(metadata %str_slice* %msg, metadata !79, metadata !43), !dbg !80
  call void @llvm.dbg.declare(metadata { %str_slice, i32 }** %file_line, metadata !81, metadata !43), !dbg !80
  br label %start, !dbg !80

start:                                            ; preds = %entry-block
  %5 = getelementptr inbounds %str_slice, %str_slice* %arg0, i32 0, i32 0, !dbg !82
  %6 = load i8*, i8** %5, !dbg !82, !nonnull !5
  %7 = getelementptr inbounds %str_slice, %str_slice* %arg0, i32 0, i32 1, !dbg !82
  %8 = load i64, i64* %7, !dbg !82
  %9 = getelementptr inbounds %str_slice, %str_slice* %msg, i32 0, i32 0, !dbg !82
  store i8* %6, i8** %9, !dbg !82
  %10 = getelementptr inbounds %str_slice, %str_slice* %msg, i32 0, i32 1, !dbg !82
  store i64 %8, i64* %10, !dbg !82
  %11 = load { %str_slice, i32 }*, { %str_slice, i32 }** %arg1, !dbg !82, !nonnull !5
  store { %str_slice, i32 }* %11, { %str_slice, i32 }** %file_line, !dbg !82
  %12 = getelementptr inbounds %str_slice, %str_slice* %msg, i32 0, i32 0, !dbg !83
  %13 = load i8*, i8** %12, !dbg !83, !nonnull !5
  %14 = getelementptr inbounds %str_slice, %str_slice* %msg, i32 0, i32 1, !dbg !83
  %15 = load i64, i64* %14, !dbg !83
  %16 = getelementptr inbounds %str_slice, %str_slice* %arg0.i, i32 0, i32 0, !dbg !83
  store i8* %13, i8** %16, !dbg !83, !noalias !84
  %17 = getelementptr inbounds %str_slice, %str_slice* %arg0.i, i32 0, i32 1, !dbg !83
  store i64 %15, i64* %17, !dbg !83, !noalias !84
  %18 = getelementptr inbounds %str_slice, %str_slice* %arg0.i, i32 0, i32 0, !dbg !87
  %19 = load i8*, i8** %18, !dbg !87, !noalias !84, !nonnull !5
  %20 = getelementptr inbounds %str_slice, %str_slice* %arg0.i, i32 0, i32 1, !dbg !87
  %21 = load i64, i64* %20, !dbg !87, !noalias !84
  %22 = getelementptr inbounds %str_slice, %str_slice* %x.i, i32 0, i32 0, !dbg !87
  store i8* %19, i8** %22, !dbg !87, !noalias !84
  %23 = getelementptr inbounds %str_slice, %str_slice* %x.i, i32 0, i32 1, !dbg !87
  store i64 %21, i64* %23, !dbg !87, !noalias !84
  %24 = invoke i8* @_ZN5alloc4heap15exchange_malloc17h502cb7e03a3ef92eE(i64 16, i64 8)
          to label %"_ZN5alloc5boxed30_$LT$impl$u20$Box$LT$T$GT$$GT$3new17hcdad80961e4b06cfE.exit" unwind label %cleanup, !dbg !88

"_ZN5alloc5boxed30_$LT$impl$u20$Box$LT$T$GT$$GT$3new17hcdad80961e4b06cfE.exit": ; preds = %start
  %25 = bitcast i8* %24 to %str_slice*, !dbg !88
  %26 = getelementptr inbounds %str_slice, %str_slice* %x.i, i32 0, i32 0, !dbg !88
  %27 = load i8*, i8** %26, !dbg !88, !noalias !84, !nonnull !5
  %28 = getelementptr inbounds %str_slice, %str_slice* %x.i, i32 0, i32 1, !dbg !88
  %29 = load i64, i64* %28, !dbg !88, !noalias !84
  %30 = getelementptr inbounds %str_slice, %str_slice* %25, i32 0, i32 0, !dbg !88
  store i8* %27, i8** %30, !dbg !88
  %31 = getelementptr inbounds %str_slice, %str_slice* %25, i32 0, i32 1, !dbg !88
  store i64 %29, i64* %31, !dbg !88
  br label %bb2, !dbg !89

bb1:                                              ; preds = %cleanup
  %32 = load { i8*, i32 }, { i8*, i32 }* %personalityslot, !dbg !82
  resume { i8*, i32 } %32, !dbg !82

bb2:                                              ; preds = %"_ZN5alloc5boxed30_$LT$impl$u20$Box$LT$T$GT$$GT$3new17hcdad80961e4b06cfE.exit"
  %33 = bitcast %str_slice* %25 to i8*, !dbg !83
  %34 = load { %str_slice, i32 }*, { %str_slice, i32 }** %file_line, !dbg !83, !nonnull !5
  invoke void @_ZN3std9panicking20rust_panic_with_hook17h33761bada49f3713E(i8* noalias nonnull %33, void (i8*)** nonnull getelementptr inbounds ({ void (i8*)*, i64, i64, i64 (%str_slice*)* }, { void (i8*)*, i64, i64, i64 (%str_slice*)* }* @vtable.0, i32 0, i32 0), { %str_slice, i32 }* noalias readonly dereferenceable(24) %34)
          to label %unreachable unwind label %cleanup, !dbg !83

cleanup:                                          ; preds = %start, %bb2
  %35 = landingpad { i8*, i32 }
          cleanup
  store { i8*, i32 } %35, { i8*, i32 }* %personalityslot
  br label %bb1

unreachable:                                      ; preds = %bb2
  unreachable
}

; Function Attrs: uwtable
define internal i64 @_ZN4core3any6TypeId2of17h2a88c185967cf0f1E() unnamed_addr #0 !dbg !90 {
entry-block:
  %tmp_ret = alloca i64
  %_0 = alloca %"core::any::TypeId"
  br label %start

start:                                            ; preds = %entry-block
  store i64 2615731484939768676, i64* %tmp_ret, !dbg !93
  %0 = load i64, i64* %tmp_ret, !dbg !93
  br label %bb1, !dbg !93

bb1:                                              ; preds = %start
  %1 = getelementptr inbounds %"core::any::TypeId", %"core::any::TypeId"* %_0, i32 0, i32 0, !dbg !94
  store i64 %0, i64* %1, !dbg !94
  %2 = bitcast %"core::any::TypeId"* %_0 to i64*, !dbg !95
  %3 = load i64, i64* %2, align 8, !dbg !95
  ret i64 %3, !dbg !95
}

; Function Attrs: inlinehint uwtable
define internal zeroext i1 @"_ZN4core3ptr31_$LT$impl$u20$$BP$mut$u20$T$GT$7is_null17h38e81f44618c9461E"(i8*) unnamed_addr #2 !dbg !96 {
entry-block:
  %self = alloca i8*
  %arg0 = alloca i8*
  store i8* %0, i8** %arg0
  call void @llvm.dbg.declare(metadata i8** %arg0, metadata !106, metadata !43), !dbg !107
  call void @llvm.dbg.declare(metadata i8** %self, metadata !108, metadata !43), !dbg !110
  br label %start, !dbg !110

start:                                            ; preds = %entry-block
  %1 = load i8*, i8** %arg0, !dbg !111
  store i8* %1, i8** %self, !dbg !111
  %2 = load i8*, i8** %self, !dbg !112
  %3 = call i8* @_ZN4core3ptr8null_mut17h0479cb4736c6e923E(), !dbg !112
  br label %bb1, !dbg !112

bb1:                                              ; preds = %start
  %4 = icmp eq i8* %2, %3, !dbg !112
  ret i1 %4, !dbg !113
}

; Function Attrs: inlinehint uwtable
define internal i8* @_ZN4core3ptr8null_mut17h0479cb4736c6e923E() unnamed_addr #2 !dbg !114 {
entry-block:
  br label %start

start:                                            ; preds = %entry-block
  ret i8* null, !dbg !117
}

define internal void @_ZN4drop17h3f10143eb02d4bbbE(i8*) unnamed_addr #3 {
entry-block:
  ret void
}

; Function Attrs: inlinehint uwtable
define internal i8* @_ZN5alloc4heap15exchange_malloc17h502cb7e03a3ef92eE(i64, i64) unnamed_addr #2 !dbg !118 {
entry-block:
  %_10 = alloca {}
  %ptr = alloca i8*
  %align = alloca i64
  %size = alloca i64
  %_0 = alloca i8*
  %arg1 = alloca i64
  %arg0 = alloca i64
  store i64 %0, i64* %arg0
  call void @llvm.dbg.declare(metadata i64* %arg0, metadata !123, metadata !43), !dbg !124
  store i64 %1, i64* %arg1
  call void @llvm.dbg.declare(metadata i64* %arg1, metadata !125, metadata !43), !dbg !124
  call void @llvm.dbg.declare(metadata i64* %size, metadata !126, metadata !43), !dbg !128
  call void @llvm.dbg.declare(metadata i64* %align, metadata !129, metadata !43), !dbg !128
  call void @llvm.dbg.declare(metadata i8** %ptr, metadata !130, metadata !43), !dbg !132
  br label %start, !dbg !132

start:                                            ; preds = %entry-block
  %2 = load i64, i64* %arg0, !dbg !133
  store i64 %2, i64* %size, !dbg !133
  %3 = load i64, i64* %arg1, !dbg !133
  store i64 %3, i64* %align, !dbg !133
  %4 = load i64, i64* %size, !dbg !134
  %5 = icmp eq i64 %4, 0, !dbg !134
  br i1 %5, label %bb1, label %bb2, !dbg !134

bb1:                                              ; preds = %start
  store i8* inttoptr (i64 1 to i8*), i8** %_0, !dbg !135
  br label %bb7, !dbg !134

bb2:                                              ; preds = %start
  %6 = load i64, i64* %size, !dbg !136
  %7 = load i64, i64* %align, !dbg !136
  %8 = call i8* @_ZN5alloc4heap8allocate17he4b35139a88152f3E(i64 %6, i64 %7), !dbg !136
  store i8* %8, i8** %ptr, !dbg !136
  br label %bb3, !dbg !136

bb3:                                              ; preds = %bb2
  %9 = load i8*, i8** %ptr, !dbg !137
  %10 = call zeroext i1 @"_ZN4core3ptr31_$LT$impl$u20$$BP$mut$u20$T$GT$7is_null17h38e81f44618c9461E"(i8* %9), !dbg !137
  br label %bb4, !dbg !137

bb4:                                              ; preds = %bb3
  br i1 %10, label %bb5, label %bb6, !dbg !137

bb5:                                              ; preds = %bb4
  call void @_ZN5alloc3oom3oom17h42e87d3c9d8b24c2E(), !dbg !138
  unreachable, !dbg !138

bb6:                                              ; preds = %bb4
  %11 = load i8*, i8** %ptr, !dbg !139
  store i8* %11, i8** %_0, !dbg !139
  br label %bb7, !dbg !134

bb7:                                              ; preds = %bb1, %bb6
  %12 = load i8*, i8** %_0, !dbg !140
  ret i8* %12, !dbg !140
}

; Function Attrs: inlinehint uwtable
define internal i8* @_ZN5alloc4heap8allocate17he4b35139a88152f3E(i64, i64) unnamed_addr #2 !dbg !141 {
entry-block:
  %align.i = alloca i64
  call void @llvm.dbg.declare(metadata i64* %align.i, metadata !142, metadata !43), !dbg !147
  %size.i = alloca i64
  call void @llvm.dbg.declare(metadata i64* %size.i, metadata !150, metadata !43), !dbg !147
  %_0.i = alloca {}
  %arg1.i = alloca i64
  call void @llvm.dbg.declare(metadata i64* %arg1.i, metadata !151, metadata !43), !dbg !152
  %arg0.i = alloca i64
  call void @llvm.dbg.declare(metadata i64* %arg0.i, metadata !153, metadata !43), !dbg !152
  %align = alloca i64
  %size = alloca i64
  %arg1 = alloca i64
  %arg0 = alloca i64
  store i64 %0, i64* %arg0
  call void @llvm.dbg.declare(metadata i64* %arg0, metadata !154, metadata !43), !dbg !155
  store i64 %1, i64* %arg1
  call void @llvm.dbg.declare(metadata i64* %arg1, metadata !156, metadata !43), !dbg !155
  call void @llvm.dbg.declare(metadata i64* %size, metadata !157, metadata !43), !dbg !158
  call void @llvm.dbg.declare(metadata i64* %align, metadata !159, metadata !43), !dbg !158
  br label %start, !dbg !158

start:                                            ; preds = %entry-block
  %2 = load i64, i64* %arg0, !dbg !160
  store i64 %2, i64* %size, !dbg !160
  %3 = load i64, i64* %arg1, !dbg !160
  store i64 %3, i64* %align, !dbg !160
  %4 = load i64, i64* %size, !dbg !161
  %5 = load i64, i64* %align, !dbg !161
  store i64 %4, i64* %arg0.i, !dbg !161
  store i64 %5, i64* %arg1.i, !dbg !161
  %6 = load i64, i64* %arg0.i, !dbg !162
  store i64 %6, i64* %size.i, !dbg !162
  %7 = load i64, i64* %arg1.i, !dbg !162
  store i64 %7, i64* %align.i, !dbg !162
  br label %bb1, !dbg !161

bb1:                                              ; preds = %start
  %8 = load i64, i64* %size, !dbg !163
  %9 = load i64, i64* %align, !dbg !163
  %10 = call i8* @__rust_allocate(i64 %8, i64 %9), !dbg !163
  br label %bb2, !dbg !163

bb2:                                              ; preds = %bb1
  ret i8* %10, !dbg !164
}

; Function Attrs: uwtable
define internal i32 @_ZN7example3sum17hefb5a864520fb38cE(i32, i32) unnamed_addr #0 !dbg !165 {
entry-block:
  %b = alloca i32
  %a = alloca i32
  %arg1 = alloca i32
  %arg0 = alloca i32
  store i32 %0, i32* %arg0
  call void @llvm.dbg.declare(metadata i32* %arg0, metadata !169, metadata !43), !dbg !170
  store i32 %1, i32* %arg1
  call void @llvm.dbg.declare(metadata i32* %arg1, metadata !171, metadata !43), !dbg !170
  call void @llvm.dbg.declare(metadata i32* %a, metadata !172, metadata !43), !dbg !174
  call void @llvm.dbg.declare(metadata i32* %b, metadata !175, metadata !43), !dbg !174
  br label %start, !dbg !174

start:                                            ; preds = %entry-block
  %2 = load i32, i32* %arg0, !dbg !176
  store i32 %2, i32* %a, !dbg !176
  %3 = load i32, i32* %arg1, !dbg !176
  store i32 %3, i32* %b, !dbg !176
  %4 = load i32, i32* %a, !dbg !177
  %5 = load i32, i32* %b, !dbg !177
  %6 = call { i32, i1 } @llvm.sadd.with.overflow.i32(i32 %4, i32 %5), !dbg !177
  %7 = extractvalue { i32, i1 } %6, 0, !dbg !177
  %8 = extractvalue { i32, i1 } %6, 1, !dbg !177
  %9 = call i1 @llvm.expect.i1(i1 %8, i1 false), !dbg !177
  br i1 %9, label %panic, label %bb1, !dbg !177

bb1:                                              ; preds = %start
  ret i32 %7, !dbg !178

panic:                                            ; preds = %start
  call void @_ZN4core9panicking5panic17h723a4d81a96970caE({ %str_slice, %str_slice, i32 }* @panic_loc.3), !dbg !177
  unreachable, !dbg !177
}

; Function Attrs: uwtable
define internal void @_ZN7example17rusttest_foo_sum117h319bd21b204fd3edE() unnamed_addr #0 !dbg !179 {
entry-block:
  %_1 = alloca {}
  %_0 = alloca {}
  br label %start

start:                                            ; preds = %entry-block
  %0 = call i32 @_ZN7example3sum17hefb5a864520fb38cE(i32 3, i32 4), !dbg !182
  br label %bb1, !dbg !182

bb1:                                              ; preds = %start
  %1 = icmp eq i32 %0, 7, !dbg !182
  %2 = xor i1 %1, true, !dbg !182
  br i1 %2, label %bb2, label %bb3, !dbg !182

bb2:                                              ; preds = %bb1
  call void @_ZN3std9panicking11begin_panic17h6c6bf73f39cdbdacE(i8* noalias nonnull readonly getelementptr inbounds ([32 x i8], [32 x i8]* @str.4, i32 0, i32 0), i64 32, { %str_slice, i32 }* noalias readonly dereferenceable(24) bitcast ({ %str_slice, i32, [4 x i8] }* @_ZN7example17rusttest_foo_sum110_FILE_LINE17h5d1b4176bce6be50E to { %str_slice, i32 }*)), !dbg !182
  unreachable, !dbg !182

bb3:                                              ; preds = %bb1
  ret void, !dbg !183
}

; Function Attrs: uwtable
define internal void @_ZN7example17rusttest_foo_sum217h8c8aeea1b7695792E() unnamed_addr #0 !dbg !184 {
entry-block:
  %_1 = alloca {}
  %_0 = alloca {}
  br label %start

start:                                            ; preds = %entry-block
  %0 = call i32 @_ZN7example3sum17hefb5a864520fb38cE(i32 4, i32 5), !dbg !185
  br label %bb1, !dbg !185

bb1:                                              ; preds = %start
  %1 = icmp eq i32 %0, 9, !dbg !185
  %2 = xor i1 %1, true, !dbg !185
  br i1 %2, label %bb2, label %bb3, !dbg !185

bb2:                                              ; preds = %bb1
  call void @_ZN3std9panicking11begin_panic17h6c6bf73f39cdbdacE(i8* noalias nonnull readonly getelementptr inbounds ([32 x i8], [32 x i8]* @str.5, i32 0, i32 0), i64 32, { %str_slice, i32 }* noalias readonly dereferenceable(24) bitcast ({ %str_slice, i32, [4 x i8] }* @_ZN7example17rusttest_foo_sum210_FILE_LINE17h1dfc9fa2411661a7E to { %str_slice, i32 }*)), !dbg !185
  unreachable, !dbg !185

bb3:                                              ; preds = %bb1
  ret void, !dbg !186
}

; Function Attrs: uwtable
define internal void @_ZN7example6__test4main17h57ca69db7ca63c3dE() unnamed_addr #0 !dbg !187 {
entry-block:
  br label %start

start:                                            ; preds = %entry-block
  call void @_ZN4test16test_main_static17h8310fdcbefe718c6E(%"test::TestDescAndFn"* noalias nonnull readonly bitcast ({ { { { i64, %str_slice, [8 x i8] }, i1, [7 x i8], { i64, [16 x i8] } }, { i64, void ()*, [8 x i8] } }, { { { i64, %str_slice, [8 x i8] }, i1, [7 x i8], { i64, [16 x i8] } }, { i64, void ()*, [8 x i8] } } }* @ref.8 to %"test::TestDescAndFn"*), i64 2), !dbg !189
  br label %bb1, !dbg !189

bb1:                                              ; preds = %start
  ret void, !dbg !189
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind
declare i32 @rust_eh_personality(i32, i32, i64, %"unwind::libunwind::_Unwind_Exception"*, %"unwind::libunwind::_Unwind_Context"*) unnamed_addr #6

; Function Attrs: cold noinline noreturn
declare void @_ZN3std9panicking20rust_panic_with_hook17h33761bada49f3713E(i8* noalias nonnull, void (i8*)** nonnull, { %str_slice, i32 }* noalias readonly dereferenceable(24)) unnamed_addr #7

; Function Attrs: cold noinline noreturn
declare void @_ZN5alloc3oom3oom17h42e87d3c9d8b24c2E() unnamed_addr #7

; Function Attrs: nounwind
declare noalias i8* @__rust_allocate(i64, i64) unnamed_addr #6

; Function Attrs: nounwind readnone
declare { i32, i1 } @llvm.sadd.with.overflow.i32(i32, i32) #4

; Function Attrs: nounwind readnone
declare i1 @llvm.expect.i1(i1, i1) #4

; Function Attrs: cold noinline noreturn
declare void @_ZN4core9panicking5panic17h723a4d81a96970caE({ %str_slice, %str_slice, i32 }* noalias readonly dereferenceable(40)) unnamed_addr #7

declare void @_ZN4test16test_main_static17h8310fdcbefe718c6E(%"test::TestDescAndFn"* noalias nonnull readonly, i64) unnamed_addr #3

define i64 @main(i64, i8**) unnamed_addr #3 {
top:
  %2 = call i64 @_ZN3std2rt10lang_start17h745bea112c3e5e1aE(i8* bitcast (void ()* @_ZN7example6__test4main17h57ca69db7ca63c3dE to i8*), i64 %0, i8** %1)
  ret i64 %2
}

declare i64 @_ZN3std2rt10lang_start17h745bea112c3e5e1aE(i8*, i64, i8**) unnamed_addr #3

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
!3 = distinct !DICompileUnit(language: DW_LANG_Rust, file: !4, producer: "rustc version 1.16.0-nightly (83c2d9523 2017-01-24)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !5, globals: !6)
!4 = !DIFile(filename: "./example.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!5 = !{}
!6 = !{!7, !25}
!7 = distinct !DIGlobalVariable(name: "_FILE_LINE", linkageName: "_ZN7example17rusttest_foo_sum110_FILE_LINEE", scope: !8, file: !11, line: 5, type: !12, isLocal: true, isDefinition: true, variable: { %str_slice, i32, [4 x i8] }* @_ZN7example17rusttest_foo_sum110_FILE_LINE17h5d1b4176bce6be50E)
!8 = !DINamespace(name: "rusttest_foo_sum1", scope: !10, file: !9, line: 7)
!9 = !DIFile(filename: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust/example.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!10 = !DINamespace(name: "example", scope: null, file: !9, line: 2)
!11 = !DIFile(filename: "<panic macros>", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!12 = !DICompositeType(tag: DW_TAG_structure_type, name: "(&str, u32)", file: !13, size: 192, align: 64, elements: !14, identifier: "7938d327a46fe9a622f4f79da12b5f3b304c40cf")
!13 = !DIFile(filename: "<unknown>", directory: "")
!14 = !{!15, !23}
!15 = !DIDerivedType(tag: DW_TAG_member, name: "__0", scope: !12, file: !13, baseType: !16, size: 128, align: 64)
!16 = !DICompositeType(tag: DW_TAG_structure_type, name: "&str", file: !13, size: 128, align: 64, elements: !17, identifier: "84d2e8c51a6d51cb9793108c0a4ccc387b029b7c")
!17 = !{!18, !21}
!18 = !DIDerivedType(tag: DW_TAG_member, name: "data_ptr", scope: !16, file: !13, baseType: !19, size: 64, align: 64)
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "*const u8", baseType: !20, size: 64, align: 64)
!20 = !DIBasicType(name: "u8", size: 8, align: 8, encoding: DW_ATE_unsigned)
!21 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !16, file: !13, baseType: !22, size: 64, align: 64, offset: 64)
!22 = !DIBasicType(name: "usize", size: 64, align: 64, encoding: DW_ATE_unsigned)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "__1", scope: !12, file: !13, baseType: !24, size: 32, align: 32, offset: 128)
!24 = !DIBasicType(name: "u32", size: 32, align: 32, encoding: DW_ATE_unsigned)
!25 = distinct !DIGlobalVariable(name: "_FILE_LINE", linkageName: "_ZN7example17rusttest_foo_sum210_FILE_LINEE", scope: !26, file: !11, line: 5, type: !12, isLocal: true, isDefinition: true, variable: { %str_slice, i32, [4 x i8] }* @_ZN7example17rusttest_foo_sum210_FILE_LINE17h1dfc9fa2411661a7E)
!26 = !DINamespace(name: "rusttest_foo_sum2", scope: !10, file: !9, line: 12)
!27 = distinct !DISubprogram(name: "get_type_id<&str>", linkageName: "_ZN4core3any8{{impl}}17get_type_id<&str>E", scope: !29, file: !28, line: 115, type: !33, isLocal: false, isDefinition: true, scopeLine: 115, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !40, variables: !5)
!28 = !DIFile(filename: "/Users/rustbuild/src/rust-buildbot/slave/nightly-dist-rustc-mac/build/src/libcore/any.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!29 = !DINamespace(name: "{{impl}}", scope: !30, file: !28, line: 114)
!30 = !DINamespace(name: "any", scope: !31, file: !28, line: 11)
!31 = !DINamespace(name: "core", scope: null, file: !32, line: 11)
!32 = !DIFile(filename: "/Users/rustbuild/src/rust-buildbot/slave/nightly-dist-rustc-mac/build/src/libcore/lib.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!33 = !DISubroutineType(types: !34)
!34 = !{!35, !39}
!35 = !DICompositeType(tag: DW_TAG_structure_type, name: "TypeId", scope: !30, file: !13, size: 64, align: 64, elements: !36, identifier: "f80b8036614d32088aa4b1d82ec3c5b70ca5b200")
!36 = !{!37}
!37 = !DIDerivedType(tag: DW_TAG_member, name: "t", scope: !35, file: !13, baseType: !38, size: 64, align: 64)
!38 = !DIBasicType(name: "u64", size: 64, align: 64, encoding: DW_ATE_unsigned)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "&&str", baseType: !16, size: 64, align: 64)
!40 = !{!41}
!41 = !DITemplateTypeParameter(name: "T", type: !16)
!42 = !DILocalVariable(name: "self", arg: 1, scope: !27, file: !9, line: 1, type: !39)
!43 = !DIExpression()
!44 = !DILocation(line: 1, scope: !27)
!45 = !DILocalVariable(name: "self", scope: !46, file: !28, line: 115, type: !39)
!46 = distinct !DILexicalBlock(scope: !27, file: !28, line: 115, column: 36)
!47 = !DILocation(line: 115, scope: !46)
!48 = !DILocation(line: 115, scope: !27)
!49 = distinct !DISubprogram(name: "begin_panic<&str>", linkageName: "_ZN3std9panicking17begin_panic<&str>E", scope: !51, file: !50, line: 509, type: !54, isLocal: false, isDefinition: true, scopeLine: 509, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !58, variables: !5)
!50 = !DIFile(filename: "/Users/rustbuild/src/rust-buildbot/slave/nightly-dist-rustc-mac/build/src/libstd/panicking.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!51 = !DINamespace(name: "panicking", scope: !52, file: !50, line: 11)
!52 = !DINamespace(name: "std", scope: null, file: !53, line: 11)
!53 = !DIFile(filename: "/Users/rustbuild/src/rust-buildbot/slave/nightly-dist-rustc-mac/build/src/libstd/lib.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!54 = !DISubroutineType(types: !55)
!55 = !{!56, !16, !57}
!56 = !DIBasicType(name: "!", align: 8, encoding: DW_ATE_unsigned)
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "&(&str, u32)", baseType: !12, size: 64, align: 64)
!58 = !{!59}
!59 = !DITemplateTypeParameter(name: "M", type: !16)
!60 = !DILocalVariable(name: "x", scope: !61, file: !62, line: 234, type: !16)
!61 = distinct !DILexicalBlock(scope: !63, file: !62, line: 234, column: 31)
!62 = !DIFile(filename: "/Users/rustbuild/src/rust-buildbot/slave/nightly-dist-rustc-mac/build/src/liballoc/boxed.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!63 = distinct !DISubprogram(name: "new<&str>", linkageName: "_ZN5alloc5boxed8{{impl}}9new<&str>E", scope: !64, file: !62, line: 234, type: !68, isLocal: false, isDefinition: true, scopeLine: 234, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !40, variables: !5)
!64 = !DINamespace(name: "{{impl}}", scope: !65, file: !62, line: 224)
!65 = !DINamespace(name: "boxed", scope: !66, file: !62, line: 11)
!66 = !DINamespace(name: "alloc", scope: null, file: !67, line: 11)
!67 = !DIFile(filename: "/Users/rustbuild/src/rust-buildbot/slave/nightly-dist-rustc-mac/build/src/liballoc/lib.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!68 = !DISubroutineType(types: !69)
!69 = !{!70, !16}
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "Box<&str>", baseType: !16, size: 64, align: 64)
!71 = !DILocation(line: 234, scope: !61, inlinedAt: !72)
!72 = distinct !DILocation(line: 517, scope: !73)
!73 = distinct !DILexicalBlock(scope: !49, file: !50, line: 509, column: 80)
!74 = !DILocalVariable(name: "x", arg: 1, scope: !63, file: !9, line: 1, type: !16)
!75 = !DILocation(line: 1, scope: !63, inlinedAt: !72)
!76 = !DILocalVariable(name: "msg", arg: 1, scope: !49, file: !9, line: 1, type: !16)
!77 = !DILocation(line: 1, scope: !49)
!78 = !DILocalVariable(name: "file_line", arg: 2, scope: !49, file: !9, line: 1, type: !57)
!79 = !DILocalVariable(name: "msg", scope: !73, file: !50, line: 509, type: !16)
!80 = !DILocation(line: 509, scope: !73)
!81 = !DILocalVariable(name: "file_line", scope: !73, file: !50, line: 509, type: !57)
!82 = !DILocation(line: 509, scope: !49)
!83 = !DILocation(line: 517, scope: !73)
!84 = !{!85}
!85 = distinct !{!85, !86, !"_ZN5alloc5boxed30_$LT$impl$u20$Box$LT$T$GT$$GT$3new17hcdad80961e4b06cfE: argument 0"}
!86 = distinct !{!86, !"_ZN5alloc5boxed30_$LT$impl$u20$Box$LT$T$GT$$GT$3new17hcdad80961e4b06cfE"}
!87 = !DILocation(line: 234, scope: !63, inlinedAt: !72)
!88 = !DILocation(line: 235, scope: !61, inlinedAt: !72)
!89 = !DILocation(line: 236, scope: !61, inlinedAt: !72)
!90 = distinct !DISubprogram(name: "of<&str>", linkageName: "_ZN4core3any8{{impl}}8of<&str>E", scope: !35, file: !28, line: 366, type: !91, isLocal: false, isDefinition: true, scopeLine: 366, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !40, variables: !5)
!91 = !DISubroutineType(types: !92)
!92 = !{!35}
!93 = !DILocation(line: 368, scope: !90)
!94 = !DILocation(line: 367, scope: !90)
!95 = !DILocation(line: 370, scope: !90)
!96 = distinct !DISubprogram(name: "is_null<u8>", linkageName: "_ZN4core3ptr8{{impl}}11is_null<u8>E", scope: !98, file: !97, line: 490, type: !100, isLocal: false, isDefinition: true, scopeLine: 490, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !104, variables: !5)
!97 = !DIFile(filename: "/Users/rustbuild/src/rust-buildbot/slave/nightly-dist-rustc-mac/build/src/libcore/ptr.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!98 = !DINamespace(name: "{{impl}}", scope: !99, file: !97, line: 476)
!99 = !DINamespace(name: "ptr", scope: !31, file: !97, line: 13)
!100 = !DISubroutineType(types: !101)
!101 = !{!102, !103}
!102 = !DIBasicType(name: "bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "*mut u8", baseType: !20, size: 64, align: 64)
!104 = !{!105}
!105 = !DITemplateTypeParameter(name: "T", type: !20)
!106 = !DILocalVariable(name: "self", arg: 1, scope: !96, file: !9, line: 1, type: !103)
!107 = !DILocation(line: 1, scope: !96)
!108 = !DILocalVariable(name: "self", scope: !109, file: !97, line: 490, type: !103)
!109 = distinct !DILexicalBlock(scope: !96, file: !97, line: 490, column: 48)
!110 = !DILocation(line: 490, scope: !109)
!111 = !DILocation(line: 490, scope: !96)
!112 = !DILocation(line: 491, scope: !109)
!113 = !DILocation(line: 492, scope: !109)
!114 = distinct !DISubprogram(name: "null_mut<u8>", linkageName: "_ZN4core3ptr12null_mut<u8>E", scope: !99, file: !97, line: 69, type: !115, isLocal: false, isDefinition: true, scopeLine: 69, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !104, variables: !5)
!115 = !DISubroutineType(types: !116)
!116 = !{!103}
!117 = !DILocation(line: 69, scope: !114)
!118 = distinct !DISubprogram(name: "exchange_malloc", linkageName: "_ZN5alloc4heap15exchange_mallocE", scope: !120, file: !119, line: 134, type: !121, isLocal: false, isDefinition: true, scopeLine: 134, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !5, variables: !5)
!119 = !DIFile(filename: "/Users/rustbuild/src/rust-buildbot/slave/nightly-dist-rustc-mac/build/src/liballoc/heap.rs", directory: "/Users/stanislaw/Projects/LLVM/llvm/projects/mull/lab/rust")
!120 = !DINamespace(name: "heap", scope: !66, file: !119, line: 11)
!121 = !DISubroutineType(types: !122)
!122 = !{!103, !22, !22}
!123 = !DILocalVariable(name: "size", arg: 1, scope: !118, file: !9, line: 1, type: !22)
!124 = !DILocation(line: 1, scope: !118)
!125 = !DILocalVariable(name: "align", arg: 2, scope: !118, file: !9, line: 1, type: !22)
!126 = !DILocalVariable(name: "size", scope: !127, file: !119, line: 134, type: !22)
!127 = distinct !DILexicalBlock(scope: !118, file: !119, line: 134, column: 64)
!128 = !DILocation(line: 134, scope: !127)
!129 = !DILocalVariable(name: "align", scope: !127, file: !119, line: 134, type: !22)
!130 = !DILocalVariable(name: "ptr", scope: !131, file: !119, line: 138, type: !103)
!131 = distinct !DILexicalBlock(scope: !127, file: !119, line: 138, column: 40)
!132 = !DILocation(line: 138, scope: !131)
!133 = !DILocation(line: 134, scope: !118)
!134 = !DILocation(line: 135, scope: !127)
!135 = !DILocation(line: 136, scope: !127)
!136 = !DILocation(line: 138, scope: !127)
!137 = !DILocation(line: 139, scope: !131)
!138 = !DILocation(line: 140, scope: !131)
!139 = !DILocation(line: 142, scope: !131)
!140 = !DILocation(line: 144, scope: !127)
!141 = distinct !DISubprogram(name: "allocate", linkageName: "_ZN5alloc4heap8allocateE", scope: !120, file: !119, line: 57, type: !121, isLocal: false, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !5, variables: !5)
!142 = !DILocalVariable(name: "align", scope: !143, file: !119, line: 37, type: !22)
!143 = distinct !DILexicalBlock(scope: !144, file: !119, line: 37, column: 55)
!144 = distinct !DISubprogram(name: "check_size_and_alignment", linkageName: "_ZN5alloc4heap24check_size_and_alignmentE", scope: !120, file: !119, line: 37, type: !145, isLocal: false, isDefinition: true, scopeLine: 37, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !5, variables: !5)
!145 = !DISubroutineType(types: !146)
!146 = !{null, !22, !22}
!147 = !DILocation(line: 37, scope: !143, inlinedAt: !148)
!148 = distinct !DILocation(line: 58, scope: !149)
!149 = distinct !DILexicalBlock(scope: !141, file: !119, line: 57, column: 61)
!150 = !DILocalVariable(name: "size", scope: !143, file: !119, line: 37, type: !22)
!151 = !DILocalVariable(name: "align", arg: 2, scope: !144, file: !9, line: 1, type: !22)
!152 = !DILocation(line: 1, scope: !144, inlinedAt: !148)
!153 = !DILocalVariable(name: "size", arg: 1, scope: !144, file: !9, line: 1, type: !22)
!154 = !DILocalVariable(name: "size", arg: 1, scope: !141, file: !9, line: 1, type: !22)
!155 = !DILocation(line: 1, scope: !141)
!156 = !DILocalVariable(name: "align", arg: 2, scope: !141, file: !9, line: 1, type: !22)
!157 = !DILocalVariable(name: "size", scope: !149, file: !119, line: 57, type: !22)
!158 = !DILocation(line: 57, scope: !149)
!159 = !DILocalVariable(name: "align", scope: !149, file: !119, line: 57, type: !22)
!160 = !DILocation(line: 57, scope: !141)
!161 = !DILocation(line: 58, scope: !149)
!162 = !DILocation(line: 37, scope: !144, inlinedAt: !148)
!163 = !DILocation(line: 59, scope: !149)
!164 = !DILocation(line: 60, scope: !149)
!165 = distinct !DISubprogram(name: "sum", linkageName: "_ZN7example3sumE", scope: !10, file: !9, line: 2, type: !166, isLocal: true, isDefinition: true, scopeLine: 2, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !5, variables: !5)
!166 = !DISubroutineType(types: !167)
!167 = !{!168, !168, !168}
!168 = !DIBasicType(name: "i32", size: 32, align: 32, encoding: DW_ATE_signed)
!169 = !DILocalVariable(name: "a", arg: 1, scope: !165, file: !9, line: 1, type: !168)
!170 = !DILocation(line: 1, scope: !165)
!171 = !DILocalVariable(name: "b", arg: 2, scope: !165, file: !9, line: 1, type: !168)
!172 = !DILocalVariable(name: "a", scope: !173, file: !9, line: 2, type: !168)
!173 = distinct !DILexicalBlock(scope: !165, file: !9, line: 2, column: 34)
!174 = !DILocation(line: 2, scope: !173)
!175 = !DILocalVariable(name: "b", scope: !173, file: !9, line: 2, type: !168)
!176 = !DILocation(line: 2, scope: !165)
!177 = !DILocation(line: 3, scope: !173)
!178 = !DILocation(line: 4, scope: !173)
!179 = distinct !DISubprogram(name: "rusttest_foo_sum1", linkageName: "_ZN7example17rusttest_foo_sum1E", scope: !10, file: !9, line: 7, type: !180, isLocal: true, isDefinition: true, scopeLine: 7, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !5, variables: !5)
!180 = !DISubroutineType(types: !181)
!181 = !{null}
!182 = !DILocation(line: 8, scope: !179)
!183 = !DILocation(line: 9, scope: !179)
!184 = distinct !DISubprogram(name: "rusttest_foo_sum2", linkageName: "_ZN7example17rusttest_foo_sum2E", scope: !10, file: !9, line: 12, type: !180, isLocal: true, isDefinition: true, scopeLine: 12, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !5, variables: !5)
!185 = !DILocation(line: 13, scope: !184)
!186 = !DILocation(line: 14, scope: !184)
!187 = distinct !DISubprogram(name: "main", linkageName: "_ZN7example6__test4mainE", scope: !188, file: !9, line: 1, type: !180, isLocal: true, isDefinition: true, scopeLine: 1, flags: DIFlagPrototyped, isOptimized: false, unit: !3, templateParams: !5, variables: !5)
!188 = !DINamespace(name: "__test", scope: !10, file: !13)
!189 = !DILocation(line: 1, scope: !187)
