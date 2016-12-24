; ModuleID = './LabTestee.cpp'
source_filename = "./LabTestee.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.10.0"

%class.LabTestee = type { i8 }

; Function Attrs: nounwind ssp uwtable
define i32 @_ZN9LabTestee6testeeEv(%class.LabTestee*) #0 align 2 !dbg !7 {
  %2 = alloca %class.LabTestee*, align 8
  store %class.LabTestee* %0, %class.LabTestee** %2, align 8
  call void @llvm.dbg.declare(metadata %class.LabTestee** %2, metadata !17, metadata !19), !dbg !20
  %3 = load %class.LabTestee*, %class.LabTestee** %2, align 8
  ret i32 1, !dbg !21
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

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
!7 = distinct !DISubprogram(name: "testee", linkageName: "_ZN9LabTestee6testeeEv", scope: !9, file: !8, line: 3, type: !13, isLocal: false, isDefinition: true, scopeLine: 3, flags: DIFlagPrototyped, isOptimized: false, unit: !0, declaration: !12, variables: !2)
!8 = !DIFile(filename: "./LabTestee.cpp", directory: "/Users/Stanislaw/Projects/LLVM/llvm/projects/mutang-project/lab/google_test/test_finder")
!9 = distinct !DICompositeType(tag: DW_TAG_class_type, name: "LabTestee", file: !10, line: 2, size: 8, align: 8, elements: !11, identifier: "_ZTS9LabTestee")
!10 = !DIFile(filename: "./LabTestee.h", directory: "/Users/Stanislaw/Projects/LLVM/llvm/projects/mutang-project/lab/google_test/test_finder")
!11 = !{!12}
!12 = !DISubprogram(name: "testee", linkageName: "_ZN9LabTestee6testeeEv", scope: !9, file: !10, line: 4, type: !13, isLocal: false, isDefinition: false, scopeLine: 4, flags: DIFlagPublic | DIFlagPrototyped, isOptimized: false)
!13 = !DISubroutineType(types: !14)
!14 = !{!15, !16}
!15 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64, flags: DIFlagArtificial | DIFlagObjectPointer)
!17 = !DILocalVariable(name: "this", arg: 1, scope: !7, type: !18, flags: DIFlagArtificial | DIFlagObjectPointer)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!19 = !DIExpression()
!20 = !DILocation(line: 0, scope: !7)
!21 = !DILocation(line: 4, column: 3, scope: !7)
