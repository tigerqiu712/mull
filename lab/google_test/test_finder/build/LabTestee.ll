; ModuleID = './LabTestee.cpp'
source_filename = "./LabTestee.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.10.0"

%class.LabTestee = type { i8 }

; Function Attrs: nounwind ssp uwtable
define i32 @_ZN9LabTestee6testeeEv(%class.LabTestee*) #0 align 2 !dbg !7 {
  %2 = alloca %class.LabTestee*, align 8
  store %class.LabTestee* %0, %class.LabTestee** %2, align 8
  call void @llvm.dbg.declare(metadata %class.LabTestee** %2, metadata !21, metadata !23), !dbg !24
  %3 = load %class.LabTestee*, %class.LabTestee** %2, align 8
  %4 = call i32 @_ZN9LabTestee7testee1Ev(%class.LabTestee* %3), !dbg !25
  ret i32 %4, !dbg !26
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind ssp uwtable
define i32 @_ZN9LabTestee7testee1Ev(%class.LabTestee*) #0 align 2 !dbg !27 {
  %2 = alloca %class.LabTestee*, align 8
  store %class.LabTestee* %0, %class.LabTestee** %2, align 8
  call void @llvm.dbg.declare(metadata %class.LabTestee** %2, metadata !28, metadata !23), !dbg !29
  %3 = load %class.LabTestee*, %class.LabTestee** %2, align 8
  %4 = call i32 @_ZN9LabTestee7testee2Ev(%class.LabTestee* %3), !dbg !30
  ret i32 %4, !dbg !31
}

; Function Attrs: nounwind ssp uwtable
define i32 @_ZN9LabTestee7testee2Ev(%class.LabTestee*) #0 align 2 !dbg !32 {
  %2 = alloca %class.LabTestee*, align 8
  store %class.LabTestee* %0, %class.LabTestee** %2, align 8
  call void @llvm.dbg.declare(metadata %class.LabTestee** %2, metadata !33, metadata !23), !dbg !34
  %3 = load %class.LabTestee*, %class.LabTestee** %2, align 8
  %4 = call i32 @_ZN9LabTestee7testee3Ev(%class.LabTestee* %3), !dbg !35
  ret i32 %4, !dbg !36
}

; Function Attrs: nounwind ssp uwtable
define i32 @_ZN9LabTestee7testee3Ev(%class.LabTestee*) #0 align 2 !dbg !37 {
  %2 = alloca %class.LabTestee*, align 8
  store %class.LabTestee* %0, %class.LabTestee** %2, align 8
  call void @llvm.dbg.declare(metadata %class.LabTestee** %2, metadata !38, metadata !23), !dbg !39
  %3 = load %class.LabTestee*, %class.LabTestee** %2, align 8
  %4 = call i32 @_ZN9LabTestee7testee4Ev(%class.LabTestee* %3), !dbg !40
  ret i32 %4, !dbg !41
}

; Function Attrs: nounwind ssp uwtable
define i32 @_ZN9LabTestee7testee4Ev(%class.LabTestee*) #0 align 2 !dbg !42 {
  %2 = alloca %class.LabTestee*, align 8
  store %class.LabTestee* %0, %class.LabTestee** %2, align 8
  call void @llvm.dbg.declare(metadata %class.LabTestee** %2, metadata !43, metadata !23), !dbg !44
  %3 = load %class.LabTestee*, %class.LabTestee** %2, align 8
  ret i32 1, !dbg !45
}

attributes #0 = { nounwind ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus, file: !1, producer: "clang version 3.9.1 (tags/RELEASE_391/final)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2)
!1 = !DIFile(filename: "LabTestee.cpp", directory: "/Users/Stanislaw/Projects/LLVM/llvm/projects/mutang-project/lab/google_test/test_finder")
!2 = !{}
!3 = !{i32 2, !"Dwarf Version", i32 2}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"PIC Level", i32 2}
!6 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
!7 = distinct !DISubprogram(name: "testee", linkageName: "_ZN9LabTestee6testeeEv", scope: !9, file: !8, line: 3, type: !13, isLocal: false, isDefinition: true, scopeLine: 3, flags: DIFlagPrototyped, isOptimized: false, unit: !0, declaration: !20, variables: !2)
!8 = !DIFile(filename: "./LabTestee.cpp", directory: "/Users/Stanislaw/Projects/LLVM/llvm/projects/mutang-project/lab/google_test/test_finder")
!9 = distinct !DICompositeType(tag: DW_TAG_class_type, name: "LabTestee", file: !10, line: 2, size: 8, align: 8, elements: !11, identifier: "_ZTS9LabTestee")
!10 = !DIFile(filename: "./LabTestee.h", directory: "/Users/Stanislaw/Projects/LLVM/llvm/projects/mutang-project/lab/google_test/test_finder")
!11 = !{!12, !17, !18, !19, !20}
!12 = !DISubprogram(name: "testee1", linkageName: "_ZN9LabTestee7testee1Ev", scope: !9, file: !10, line: 3, type: !13, isLocal: false, isDefinition: false, scopeLine: 3, flags: DIFlagPrototyped, isOptimized: false)
!13 = !DISubroutineType(types: !14)
!14 = !{!15, !16}
!15 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64, flags: DIFlagArtificial | DIFlagObjectPointer)
!17 = !DISubprogram(name: "testee2", linkageName: "_ZN9LabTestee7testee2Ev", scope: !9, file: !10, line: 4, type: !13, isLocal: false, isDefinition: false, scopeLine: 4, flags: DIFlagPrototyped, isOptimized: false)
!18 = !DISubprogram(name: "testee3", linkageName: "_ZN9LabTestee7testee3Ev", scope: !9, file: !10, line: 5, type: !13, isLocal: false, isDefinition: false, scopeLine: 5, flags: DIFlagPrototyped, isOptimized: false)
!19 = !DISubprogram(name: "testee4", linkageName: "_ZN9LabTestee7testee4Ev", scope: !9, file: !10, line: 6, type: !13, isLocal: false, isDefinition: false, scopeLine: 6, flags: DIFlagPrototyped, isOptimized: false)
!20 = !DISubprogram(name: "testee", linkageName: "_ZN9LabTestee6testeeEv", scope: !9, file: !10, line: 8, type: !13, isLocal: false, isDefinition: false, scopeLine: 8, flags: DIFlagPublic | DIFlagPrototyped, isOptimized: false)
!21 = !DILocalVariable(name: "this", arg: 1, scope: !7, type: !22, flags: DIFlagArtificial | DIFlagObjectPointer)
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!23 = !DIExpression()
!24 = !DILocation(line: 0, scope: !7)
!25 = !DILocation(line: 4, column: 10, scope: !7)
!26 = !DILocation(line: 4, column: 3, scope: !7)
!27 = distinct !DISubprogram(name: "testee1", linkageName: "_ZN9LabTestee7testee1Ev", scope: !9, file: !8, line: 7, type: !13, isLocal: false, isDefinition: true, scopeLine: 7, flags: DIFlagPrototyped, isOptimized: false, unit: !0, declaration: !12, variables: !2)
!28 = !DILocalVariable(name: "this", arg: 1, scope: !27, type: !22, flags: DIFlagArtificial | DIFlagObjectPointer)
!29 = !DILocation(line: 0, scope: !27)
!30 = !DILocation(line: 8, column: 10, scope: !27)
!31 = !DILocation(line: 8, column: 3, scope: !27)
!32 = distinct !DISubprogram(name: "testee2", linkageName: "_ZN9LabTestee7testee2Ev", scope: !9, file: !8, line: 11, type: !13, isLocal: false, isDefinition: true, scopeLine: 11, flags: DIFlagPrototyped, isOptimized: false, unit: !0, declaration: !17, variables: !2)
!33 = !DILocalVariable(name: "this", arg: 1, scope: !32, type: !22, flags: DIFlagArtificial | DIFlagObjectPointer)
!34 = !DILocation(line: 0, scope: !32)
!35 = !DILocation(line: 12, column: 10, scope: !32)
!36 = !DILocation(line: 12, column: 3, scope: !32)
!37 = distinct !DISubprogram(name: "testee3", linkageName: "_ZN9LabTestee7testee3Ev", scope: !9, file: !8, line: 15, type: !13, isLocal: false, isDefinition: true, scopeLine: 15, flags: DIFlagPrototyped, isOptimized: false, unit: !0, declaration: !18, variables: !2)
!38 = !DILocalVariable(name: "this", arg: 1, scope: !37, type: !22, flags: DIFlagArtificial | DIFlagObjectPointer)
!39 = !DILocation(line: 0, scope: !37)
!40 = !DILocation(line: 16, column: 10, scope: !37)
!41 = !DILocation(line: 16, column: 3, scope: !37)
!42 = distinct !DISubprogram(name: "testee4", linkageName: "_ZN9LabTestee7testee4Ev", scope: !9, file: !8, line: 19, type: !13, isLocal: false, isDefinition: true, scopeLine: 19, flags: DIFlagPrototyped, isOptimized: false, unit: !0, declaration: !19, variables: !2)
!43 = !DILocalVariable(name: "this", arg: 1, scope: !42, type: !22, flags: DIFlagArtificial | DIFlagObjectPointer)
!44 = !DILocation(line: 0, scope: !42)
!45 = !DILocation(line: 20, column: 3, scope: !42)
