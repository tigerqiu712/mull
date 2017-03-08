	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 9
	.globl	_main
	.align	4, 0x90
_main:
	.cfi_startproc
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$192, %rsp
	movq	_globalinit_33_FD9A49A256BEB6AF7C48013347ADC3BA_token4@GOTPCREL(%rip), %rax
	movq	__TZvOs11CommandLine5_argcVs5Int32@GOTPCREL(%rip), %rcx
	movl	%edi, (%rcx)
	cmpq	$-1, (%rax)
	movq	%rsi, -8(%rbp)
	je	LBB0_2
	movq	_globalinit_33_FD9A49A256BEB6AF7C48013347ADC3BA_token4@GOTPCREL(%rip), %rdi
	movq	_globalinit_33_FD9A49A256BEB6AF7C48013347ADC3BA_func4@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	callq	_swift_once
LBB0_2:
	movq	__TZvOs11CommandLine11_unsafeArgvGSpGSqGSpVs4Int8___@GOTPCREL(%rip), %rax
	movq	-8(%rbp), %rcx
	movq	%rcx, (%rax)
	callq	__TMaC8jitswift5Hello
	movq	%rax, %rdi
	callq	__TFC8jitswift5HelloCfT_S0_
	movq	_swift_isaMask@GOTPCREL(%rip), %rcx
	movq	(%rax), %rdi
	andq	(%rcx), %rdi
	movq	%rdi, -16(%rbp)
	movq	%rax, %rdi
	movq	-16(%rbp), %rcx
	movq	%rax, -24(%rbp)
	callq	*88(%rcx)
	movq	-24(%rbp), %rdi
	callq	_objc_release
	callq	__TMaP_
	movl	$1, %edx
	movl	%edx, %edi
	movq	%rax, %rsi
	movq	%rax, -32(%rbp)
	callq	__TFs27_allocateUninitializedArrayurFBwTGSax_Bp_
	leaq	L___unnamed_1(%rip), %rdi
	movl	$21, %r8d
	movl	%r8d, %esi
	movl	$1, %r8d
	movq	__TMSS@GOTPCREL(%rip), %rcx
	movq	%rcx, 24(%rdx)
	movq	%rdx, -40(%rbp)
	movl	%r8d, %edx
	movq	%rax, -48(%rbp)
	callq	__TFSSCfT21_builtinStringLiteralBp17utf8CodeUnitCountBw7isASCIIBi1__SS
	movq	-40(%rbp), %rsi
	movq	%rax, (%rsi)
	movq	%rdx, 8(%rsi)
	movq	%rcx, 16(%rsi)
	callq	__TIFs5printFTGSaP__9separatorSS10terminatorSS_T_A0_
	movq	%rax, -56(%rbp)
	movq	%rdx, -64(%rbp)
	movq	%rcx, -72(%rbp)
	callq	__TIFs5printFTGSaP__9separatorSS10terminatorSS_T_A1_
	movq	-48(%rbp), %rdi
	movq	-56(%rbp), %rsi
	movq	-64(%rbp), %r9
	movq	%rdx, -80(%rbp)
	movq	%r9, %rdx
	movq	-72(%rbp), %r10
	movq	%rcx, -88(%rbp)
	movq	%r10, %rcx
	movq	%rax, %r8
	movq	-80(%rbp), %r9
	movq	-88(%rbp), %rax
	movq	%rax, (%rsp)
	callq	__TFs5printFTGSaP__9separatorSS10terminatorSS_T_
	callq	__TMaCSo11XCTestSuite
	cmpq	$14, (%rax)
	movq	%rax, %rcx
	movq	%rax, -96(%rbp)
	movq	%rcx, -104(%rbp)
	jne	LBB0_4
	movq	-96(%rbp), %rax
	movq	8(%rax), %rcx
	movq	%rcx, -104(%rbp)
LBB0_4:
	movq	-104(%rbp), %rax
	movq	"L_selector(defaultTestSuite)"(%rip), %rsi
	movq	%rax, %rdi
	callq	_objc_msgSend
	movq	%rax, %rdi
	callq	_objc_retainAutoreleasedReturnValue
	movq	%rax, __Tv8jitswift12defaultSuiteCSo11XCTestSuite(%rip)
	movq	__Tv8jitswift12defaultSuiteCSo11XCTestSuite(%rip), %rax
	movq	%rax, %rdi
	movq	%rax, -112(%rbp)
	callq	_objc_retain
	movq	-112(%rbp), %rsi
	movq	"L_selector(runTest)"(%rip), %rdi
	movq	%rdi, -120(%rbp)
	movq	%rsi, %rdi
	movq	-120(%rbp), %rsi
	movq	%rax, -128(%rbp)
	callq	_objc_msgSend
	movq	-112(%rbp), %rdi
	callq	_objc_release
	movl	$1, %ecx
	movl	%ecx, %edi
	movq	-32(%rbp), %rsi
	callq	__TFs27_allocateUninitializedArrayurFBwTGSax_Bp_
	leaq	L___unnamed_2(%rip), %rdi
	movl	$20, %ecx
	movl	%ecx, %esi
	movl	$1, %ecx
	movq	__TMSS@GOTPCREL(%rip), %r8
	movq	%r8, 24(%rdx)
	movq	%rdx, -136(%rbp)
	movl	%ecx, %edx
	movq	%rax, -144(%rbp)
	callq	__TFSSCfT21_builtinStringLiteralBp17utf8CodeUnitCountBw7isASCIIBi1__SS
	movq	-136(%rbp), %rsi
	movq	%rax, (%rsi)
	movq	%rdx, 8(%rsi)
	movq	%rcx, 16(%rsi)
	callq	__TIFs5printFTGSaP__9separatorSS10terminatorSS_T_A0_
	movq	%rax, -152(%rbp)
	movq	%rdx, -160(%rbp)
	movq	%rcx, -168(%rbp)
	callq	__TIFs5printFTGSaP__9separatorSS10terminatorSS_T_A1_
	movq	-144(%rbp), %rdi
	movq	-152(%rbp), %rsi
	movq	-160(%rbp), %r8
	movq	%rdx, -176(%rbp)
	movq	%r8, %rdx
	movq	-168(%rbp), %r9
	movq	%rcx, -184(%rbp)
	movq	%r9, %rcx
	movq	%rax, %r8
	movq	-176(%rbp), %r9
	movq	-184(%rbp), %rax
	movq	%rax, (%rsp)
	callq	__TFs5printFTGSaP__9separatorSS10terminatorSS_T_
	xorl	%eax, %eax
	addq	$192, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.private_extern	__TFC8jitswift5Hello9testHellofT_T_
	.globl	__TFC8jitswift5Hello9testHellofT_T_
	.align	4, 0x90
__TFC8jitswift5Hello9testHellofT_T_:
	.cfi_startproc
	pushq	%rbp
Ltmp3:
	.cfi_def_cfa_offset 16
Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp5:
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
	movq	%rdi, -8(%rbp)
	callq	__TMaP_
	movl	$1, %ecx
	movl	%ecx, %edi
	movq	%rax, %rsi
	callq	__TFs27_allocateUninitializedArrayurFBwTGSax_Bp_
	leaq	L___unnamed_3(%rip), %rdi
	movl	$11, %ecx
	movl	%ecx, %esi
	movl	$1, %ecx
	movq	__TMSS@GOTPCREL(%rip), %r8
	movq	%r8, 24(%rdx)
	movq	%rdx, -16(%rbp)
	movl	%ecx, %edx
	movq	%rax, -24(%rbp)
	callq	__TFSSCfT21_builtinStringLiteralBp17utf8CodeUnitCountBw7isASCIIBi1__SS
	movq	-16(%rbp), %rsi
	movq	%rax, (%rsi)
	movq	%rdx, 8(%rsi)
	movq	%rcx, 16(%rsi)
	callq	__TIFs5printFTGSaP__9separatorSS10terminatorSS_T_A0_
	movq	%rax, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	callq	__TIFs5printFTGSaP__9separatorSS10terminatorSS_T_A1_
	movq	-24(%rbp), %rdi
	movq	-32(%rbp), %rsi
	movq	-40(%rbp), %r8
	movq	%rdx, -56(%rbp)
	movq	%r8, %rdx
	movq	-48(%rbp), %r9
	movq	%rcx, -64(%rbp)
	movq	%r9, %rcx
	movq	%rax, %r8
	movq	-56(%rbp), %r9
	movq	-64(%rbp), %rax
	movq	%rax, (%rsp)
	callq	__TFs5printFTGSaP__9separatorSS10terminatorSS_T_
	addq	$80, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.align	4, 0x90
__TToFC8jitswift5Hello9testHellofT_T_:
	.cfi_startproc
	pushq	%rbp
Ltmp6:
	.cfi_def_cfa_offset 16
Ltmp7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp8:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	callq	_objc_retain
	movq	-8(%rbp), %rdi
	movq	%rax, -24(%rbp)
	callq	__TFC8jitswift5Hello9testHellofT_T_
	movq	-8(%rbp), %rdi
	callq	_objc_release
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.private_extern	__TFC8jitswift5Hello3sayfT_T_
	.globl	__TFC8jitswift5Hello3sayfT_T_
	.align	4, 0x90
__TFC8jitswift5Hello3sayfT_T_:
	.cfi_startproc
	pushq	%rbp
Ltmp9:
	.cfi_def_cfa_offset 16
Ltmp10:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp11:
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
	movq	%rdi, -8(%rbp)
	callq	__TMaP_
	movl	$1, %ecx
	movl	%ecx, %edi
	movq	%rax, %rsi
	callq	__TFs27_allocateUninitializedArrayurFBwTGSax_Bp_
	leaq	L___unnamed_4(%rip), %rdi
	movl	$16, %ecx
	movl	%ecx, %esi
	movl	$1, %ecx
	movq	__TMSS@GOTPCREL(%rip), %r8
	movq	%r8, 24(%rdx)
	movq	%rdx, -16(%rbp)
	movl	%ecx, %edx
	movq	%rax, -24(%rbp)
	callq	__TFSSCfT21_builtinStringLiteralBp17utf8CodeUnitCountBw7isASCIIBi1__SS
	movq	-16(%rbp), %rsi
	movq	%rax, (%rsi)
	movq	%rdx, 8(%rsi)
	movq	%rcx, 16(%rsi)
	callq	__TIFs5printFTGSaP__9separatorSS10terminatorSS_T_A0_
	movq	%rax, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	callq	__TIFs5printFTGSaP__9separatorSS10terminatorSS_T_A1_
	movq	-24(%rbp), %rdi
	movq	-32(%rbp), %rsi
	movq	-40(%rbp), %r8
	movq	%rdx, -56(%rbp)
	movq	%r8, %rdx
	movq	-48(%rbp), %r9
	movq	%rcx, -64(%rbp)
	movq	%r9, %rcx
	movq	%rax, %r8
	movq	-56(%rbp), %r9
	movq	-64(%rbp), %rax
	movq	%rax, (%rsp)
	callq	__TFs5printFTGSaP__9separatorSS10terminatorSS_T_
	addq	$80, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.align	4, 0x90
__TToFC8jitswift5Hello3sayfT_T_:
	.cfi_startproc
	pushq	%rbp
Ltmp12:
	.cfi_def_cfa_offset 16
Ltmp13:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp14:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	callq	_objc_retain
	movq	-8(%rbp), %rdi
	movq	%rax, -24(%rbp)
	callq	__TFC8jitswift5Hello3sayfT_T_
	movq	-8(%rbp), %rdi
	callq	_objc_release
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.private_extern	__TFC8jitswift5HelloD
	.globl	__TFC8jitswift5HelloD
	.align	4, 0x90
__TFC8jitswift5HelloD:
	.cfi_startproc
	pushq	%rbp
Ltmp15:
	.cfi_def_cfa_offset 16
Ltmp16:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp17:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	callq	__TMaC8jitswift5Hello
	leaq	-16(%rbp), %rdi
	movq	-24(%rbp), %rcx
	movq	%rcx, -16(%rbp)
	movq	%rax, -8(%rbp)
	movq	"L_selector(dealloc)"(%rip), %rsi
	callq	_objc_msgSendSuper2
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.private_extern	__TFC8jitswift5HellocfT10invocationGSqCSo12NSInvocation__S0_
	.globl	__TFC8jitswift5HellocfT10invocationGSqCSo12NSInvocation__S0_
	.align	4, 0x90
__TFC8jitswift5HellocfT10invocationGSqCSo12NSInvocation__S0_:
	.cfi_startproc
	pushq	%rbp
Ltmp18:
	.cfi_def_cfa_offset 16
Ltmp19:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp20:
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movq	%rsi, -8(%rbp)
	movq	%rdi, -32(%rbp)
	movq	%rsi, -40(%rbp)
	callq	__TMaC8jitswift5Hello
	leaq	-24(%rbp), %rdi
	movq	-40(%rbp), %rsi
	movq	%rsi, -24(%rbp)
	movq	%rax, -16(%rbp)
	movq	"L_selector(initWithInvocation:)"(%rip), %rsi
	movq	-32(%rbp), %rdx
	callq	_objc_msgSendSuper2
	movq	%rax, -8(%rbp)
	movq	%rax, %rdi
	movq	%rax, -48(%rbp)
	callq	_objc_retain
	movq	-32(%rbp), %rdi
	movq	%rax, -56(%rbp)
	callq	_objc_release
	movq	-48(%rbp), %rdi
	callq	_objc_release
	movq	-48(%rbp), %rax
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.private_extern	__TFC8jitswift5HelloCfT10invocationGSqCSo12NSInvocation__S0_
	.globl	__TFC8jitswift5HelloCfT10invocationGSqCSo12NSInvocation__S0_
	.align	4, 0x90
__TFC8jitswift5HelloCfT10invocationGSqCSo12NSInvocation__S0_:
	.cfi_startproc
	pushq	%rbp
Ltmp21:
	.cfi_def_cfa_offset 16
Ltmp22:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp23:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	callq	__TMaC8jitswift5Hello
	xorl	%ecx, %ecx
	movl	%ecx, %edx
	movq	"L_selector(allocWithZone:)"(%rip), %rsi
	movq	%rax, %rdi
	callq	_objc_msgSend
	movq	-8(%rbp), %rdi
	movq	%rax, %rsi
	callq	__TFC8jitswift5HellocfT10invocationGSqCSo12NSInvocation__S0_
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.align	4, 0x90
__TToFC8jitswift5HellocfT10invocationGSqCSo12NSInvocation__S0_:
	.cfi_startproc
	pushq	%rbp
Ltmp24:
	.cfi_def_cfa_offset 16
Ltmp25:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp26:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rdx, %rdi
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	callq	_objc_retain
	movq	-24(%rbp), %rdi
	movq	-8(%rbp), %rsi
	movq	%rax, -32(%rbp)
	callq	__TFC8jitswift5HellocfT10invocationGSqCSo12NSInvocation__S0_
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.private_extern	__TFC8jitswift5HellocfT8selectorV10ObjectiveC8Selector_S0_
	.globl	__TFC8jitswift5HellocfT8selectorV10ObjectiveC8Selector_S0_
	.align	4, 0x90
__TFC8jitswift5HellocfT8selectorV10ObjectiveC8Selector_S0_:
	.cfi_startproc
	pushq	%rbp
Ltmp27:
	.cfi_def_cfa_offset 16
Ltmp28:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp29:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rsi, -8(%rbp)
	movq	%rdi, -32(%rbp)
	movq	%rsi, -40(%rbp)
	callq	__TMaC8jitswift5Hello
	leaq	-24(%rbp), %rdi
	movq	-40(%rbp), %rsi
	movq	%rsi, -24(%rbp)
	movq	%rax, -16(%rbp)
	movq	"L_selector(initWithSelector:)"(%rip), %rsi
	movq	-32(%rbp), %rdx
	callq	_objc_msgSendSuper2
	movq	%rax, -8(%rbp)
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.private_extern	__TFC8jitswift5HelloCfT8selectorV10ObjectiveC8Selector_S0_
	.globl	__TFC8jitswift5HelloCfT8selectorV10ObjectiveC8Selector_S0_
	.align	4, 0x90
__TFC8jitswift5HelloCfT8selectorV10ObjectiveC8Selector_S0_:
	.cfi_startproc
	pushq	%rbp
Ltmp30:
	.cfi_def_cfa_offset 16
Ltmp31:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp32:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	callq	__TMaC8jitswift5Hello
	xorl	%ecx, %ecx
	movl	%ecx, %edx
	movq	"L_selector(allocWithZone:)"(%rip), %rsi
	movq	%rax, %rdi
	callq	_objc_msgSend
	movq	-8(%rbp), %rdi
	movq	%rax, %rsi
	callq	__TFC8jitswift5HellocfT8selectorV10ObjectiveC8Selector_S0_
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.align	4, 0x90
__TToFC8jitswift5HellocfT8selectorV10ObjectiveC8Selector_S0_:
	.cfi_startproc
	pushq	%rbp
Ltmp33:
	.cfi_def_cfa_offset 16
Ltmp34:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp35:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rdx, %rdi
	movq	-8(%rbp), %rdx
	movq	%rsi, -16(%rbp)
	movq	%rdx, %rsi
	callq	__TFC8jitswift5HellocfT8selectorV10ObjectiveC8Selector_S0_
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.private_extern	__TFC8jitswift5HellocfT_S0_
	.globl	__TFC8jitswift5HellocfT_S0_
	.align	4, 0x90
__TFC8jitswift5HellocfT_S0_:
	.cfi_startproc
	pushq	%rbp
Ltmp36:
	.cfi_def_cfa_offset 16
Ltmp37:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp38:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rdi, -32(%rbp)
	callq	__TMaC8jitswift5Hello
	leaq	-24(%rbp), %rdi
	movq	-32(%rbp), %rcx
	movq	%rcx, -24(%rbp)
	movq	%rax, -16(%rbp)
	movq	"L_selector(init)"(%rip), %rsi
	callq	_objc_msgSendSuper2
	movq	%rax, -8(%rbp)
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.private_extern	__TFC8jitswift5HelloCfT_S0_
	.globl	__TFC8jitswift5HelloCfT_S0_
	.align	4, 0x90
__TFC8jitswift5HelloCfT_S0_:
	.cfi_startproc
	pushq	%rbp
Ltmp39:
	.cfi_def_cfa_offset 16
Ltmp40:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp41:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	callq	__TMaC8jitswift5Hello
	xorl	%ecx, %ecx
	movl	%ecx, %edx
	movq	"L_selector(allocWithZone:)"(%rip), %rsi
	movq	%rax, %rdi
	callq	_objc_msgSend
	movq	%rax, %rdi
	callq	__TFC8jitswift5HellocfT_S0_
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.private_extern	__TMaC8jitswift5Hello
	.globl	__TMaC8jitswift5Hello
	.align	4, 0x90
__TMaC8jitswift5Hello:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	__TMLC8jitswift5Hello(%rip), %rax
	cmpq	$0, %rax
	movq	%rax, -8(%rbp)
	jne	LBB14_2
	leaq	__TMfC8jitswift5Hello+16(%rip), %rdi
	callq	_rt_swift_getInitializedObjCClass
	movq	%rax, %rdi
	movq	%rax, __TMLC8jitswift5Hello(%rip)
	movq	%rdi, -8(%rbp)
LBB14_2:
	movq	-8(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	retq

	.private_extern	__TMaP_
	.globl	__TMaP_
	.weak_def_can_be_hidden	__TMaP_
	.align	4, 0x90
__TMaP_:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	__TMLP_(%rip), %rax
	cmpq	$0, %rax
	movq	%rax, -16(%rbp)
	jne	LBB15_2
	xorl	%eax, %eax
	movl	%eax, %edi
	leaq	-8(%rbp), %rsi
	callq	_rt_swift_getExistentialTypeMetadata
	movq	%rax, %rsi
	movq	%rax, __TMLP_(%rip)
	movq	%rsi, -16(%rbp)
LBB15_2:
	movq	-16(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	retq

	.private_extern	_rt_swift_getExistentialTypeMetadata
	.globl	_rt_swift_getExistentialTypeMetadata
	.weak_def_can_be_hidden	_rt_swift_getExistentialTypeMetadata
	.align	4, 0x90
_rt_swift_getExistentialTypeMetadata:
	movq	__swift_getExistentialTypeMetadata@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	jmpq	*%rax

	.private_extern	__TMaCSo11XCTestSuite
	.globl	__TMaCSo11XCTestSuite
	.weak_def_can_be_hidden	__TMaCSo11XCTestSuite
	.align	4, 0x90
__TMaCSo11XCTestSuite:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	__TMLCSo11XCTestSuite(%rip), %rax
	cmpq	$0, %rax
	movq	%rax, -8(%rbp)
	jne	LBB17_2
	movq	L_OBJC_CLASS_REF_$_XCTestSuite(%rip), %rdi
	callq	_rt_swift_getInitializedObjCClass
	movq	%rax, %rdi
	callq	_swift_getObjCClassMetadata
	movq	%rax, %rdi
	movq	%rax, __TMLCSo11XCTestSuite(%rip)
	movq	%rdi, -8(%rbp)
LBB17_2:
	movq	-8(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	retq

	.private_extern	_rt_swift_getInitializedObjCClass
	.globl	_rt_swift_getInitializedObjCClass
	.weak_def_can_be_hidden	_rt_swift_getInitializedObjCClass
	.align	4, 0x90
_rt_swift_getInitializedObjCClass:
	movq	__swift_getInitializedObjCClass@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	jmpq	*%rax

	.align	4, 0x90
__TToFC8jitswift5HellocfT_S0_:
	.cfi_startproc
	pushq	%rbp
Ltmp42:
	.cfi_def_cfa_offset 16
Ltmp43:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp44:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rsi, -8(%rbp)
	callq	__TFC8jitswift5HellocfT_S0_
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.align	4, 0x90
l_get_field_types_Hello:
	.cfi_startproc
	pushq	%rbp
Ltmp45:
	.cfi_def_cfa_offset 16
Ltmp46:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp47:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	l_field_type_vector_Hello(%rip), %rax
	cmpq	$0, %rax
	movq	%rdi, -8(%rbp)
	movq	%rax, -16(%rbp)
	jne	LBB20_3
	xorl	%eax, %eax
	movl	%eax, %ecx
	movl	$7, %eax
	movl	%eax, %esi
	movq	%rcx, %rdi
	movq	%rcx, -24(%rbp)
	callq	_rt_swift_slowAlloc
	movq	%rax, %rcx
	movq	%rax, %rsi
	movq	-24(%rbp), %rdi
	movq	%rax, -32(%rbp)
	movq	%rdi, %rax
	movq	-32(%rbp), %rdx
	lock		cmpxchgq	%rdx, l_field_type_vector_Hello(%rip)
	sete	%r8b
	testb	$1, %r8b
	movq	%rcx, -40(%rbp)
	movq	%rax, -48(%rbp)
	movq	%rsi, -16(%rbp)
	jne	LBB20_3
	xorl	%eax, %eax
	movl	%eax, %esi
	movl	$7, %eax
	movl	%eax, %edx
	movq	-40(%rbp), %rdi
	callq	_rt_swift_slowDealloc
	movq	-48(%rbp), %rdx
	movq	%rdx, -16(%rbp)
LBB20_3:
	movq	-16(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.private_extern	_rt_swift_slowAlloc
	.globl	_rt_swift_slowAlloc
	.weak_def_can_be_hidden	_rt_swift_slowAlloc
	.align	4, 0x90
_rt_swift_slowAlloc:
	movq	__swift_slowAlloc@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	jmpq	*%rax

	.private_extern	_rt_swift_slowDealloc
	.globl	_rt_swift_slowDealloc
	.weak_def_can_be_hidden	_rt_swift_slowDealloc
	.align	4, 0x90
_rt_swift_slowDealloc:
	movq	__swift_slowDealloc@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	jmpq	*%rax

	.private_extern	__Tv8jitswift12defaultSuiteCSo11XCTestSuite
	.globl	__Tv8jitswift12defaultSuiteCSo11XCTestSuite
.zerofill __DATA,__common,__Tv8jitswift12defaultSuiteCSo11XCTestSuite,8,3
	.private_extern	__TMLP_
	.section	__DATA,__data
	.globl	__TMLP_
	.weak_definition	__TMLP_
	.align	3
__TMLP_:
	.quad	0

	.section	__TEXT,__cstring,cstring_literals
	.align	4
L___unnamed_1:
	.asciz	"before running XCTest"

	.private_extern	__TMLCSo11XCTestSuite
	.section	__DATA,__data
	.globl	__TMLCSo11XCTestSuite
	.weak_definition	__TMLCSo11XCTestSuite
	.align	3
__TMLCSo11XCTestSuite:
	.quad	0

	.section	__DATA,__objc_classrefs,regular,no_dead_strip
	.align	3
L_OBJC_CLASS_REF_$_XCTestSuite:
	.quad	_OBJC_CLASS_$_XCTestSuite

	.section	__TEXT,__objc_methname,cstring_literals
"L_selector_data(defaultTestSuite)":
	.asciz	"defaultTestSuite"

	.section	__DATA,__objc_selrefs,literal_pointers,no_dead_strip
	.align	3
"L_selector(defaultTestSuite)":
	.quad	"L_selector_data(defaultTestSuite)"

	.section	__TEXT,__objc_methname,cstring_literals
"L_selector_data(runTest)":
	.asciz	"runTest"

	.section	__DATA,__objc_selrefs,literal_pointers,no_dead_strip
	.align	3
"L_selector(runTest)":
	.quad	"L_selector_data(runTest)"

	.section	__TEXT,__cstring,cstring_literals
	.align	4
L___unnamed_2:
	.asciz	"after running XCTest"

L___unnamed_3:
	.asciz	"Hello world"

	.align	4
L___unnamed_4:
	.asciz	"Say: Hello world"

	.section	__TEXT,__objc_methname,cstring_literals
"L_selector_data(dealloc)":
	.asciz	"dealloc"

	.section	__DATA,__objc_selrefs,literal_pointers,no_dead_strip
	.align	3
"L_selector(dealloc)":
	.quad	"L_selector_data(dealloc)"

	.section	__TEXT,__objc_methname,cstring_literals
"L_selector_data(initWithInvocation:)":
	.asciz	"initWithInvocation:"

	.section	__DATA,__objc_selrefs,literal_pointers,no_dead_strip
	.align	3
"L_selector(initWithInvocation:)":
	.quad	"L_selector_data(initWithInvocation:)"

	.section	__TEXT,__objc_methname,cstring_literals
"L_selector_data(allocWithZone:)":
	.asciz	"allocWithZone:"

	.section	__DATA,__objc_selrefs,literal_pointers,no_dead_strip
	.align	3
"L_selector(allocWithZone:)":
	.quad	"L_selector_data(allocWithZone:)"

	.section	__TEXT,__objc_methname,cstring_literals
"L_selector_data(initWithSelector:)":
	.asciz	"initWithSelector:"

	.section	__DATA,__objc_selrefs,literal_pointers,no_dead_strip
	.align	3
"L_selector(initWithSelector:)":
	.quad	"L_selector_data(initWithSelector:)"

	.section	__TEXT,__objc_methname,cstring_literals
"L_selector_data(init)":
	.asciz	"init"

	.section	__DATA,__objc_selrefs,literal_pointers,no_dead_strip
	.align	3
"L_selector(init)":
	.quad	"L_selector_data(init)"

	.private_extern	_OBJC_METACLASS_$__TtC8jitswift5Hello
	.section	__DATA,__data
	.globl	_OBJC_METACLASS_$__TtC8jitswift5Hello
	.align	3
_OBJC_METACLASS_$__TtC8jitswift5Hello:
	.quad	_OBJC_METACLASS_$_NSObject
	.quad	_OBJC_METACLASS_$_XCTestCase
	.quad	__objc_empty_cache
	.quad	0
	.quad	l__METACLASS_DATA__TtC8jitswift5Hello

	.section	__TEXT,__objc_methname,cstring_literals
"L_selector_data(testHello)":
	.asciz	"testHello"

	.section	__TEXT,__cstring,cstring_literals
L___unnamed_5:
	.asciz	"v16@0:8"

	.section	__TEXT,__objc_methname,cstring_literals
"L_selector_data(say)":
	.asciz	"say"

	.section	__TEXT,__cstring,cstring_literals
L___unnamed_6:
	.asciz	"@24@0:8@16"

L___unnamed_7:
	.asciz	"@24@0:8:16"

L___unnamed_8:
	.asciz	"@16@0:8"

	.align	4
L___unnamed_9:
	.asciz	"_TtC8jitswift5Hello"

	.section	__DATA,__objc_const
	.align	3
l__METACLASS_DATA__TtC8jitswift5Hello:
	.long	129
	.long	40
	.long	40
	.long	0
	.quad	0
	.quad	L___unnamed_9
	.quad	0
	.quad	0
	.quad	0
	.quad	0
	.quad	0

	.align	3
l__INSTANCE_METHODS__TtC8jitswift5Hello:
	.long	24
	.long	5
	.quad	"L_selector_data(testHello)"
	.quad	L___unnamed_5
	.quad	__TToFC8jitswift5Hello9testHellofT_T_
	.quad	"L_selector_data(say)"
	.quad	L___unnamed_5
	.quad	__TToFC8jitswift5Hello3sayfT_T_
	.quad	"L_selector_data(initWithInvocation:)"
	.quad	L___unnamed_6
	.quad	__TToFC8jitswift5HellocfT10invocationGSqCSo12NSInvocation__S0_
	.quad	"L_selector_data(initWithSelector:)"
	.quad	L___unnamed_7
	.quad	__TToFC8jitswift5HellocfT8selectorV10ObjectiveC8Selector_S0_
	.quad	"L_selector_data(init)"
	.quad	L___unnamed_8
	.quad	__TToFC8jitswift5HellocfT_S0_

	.align	3
l__DATA__TtC8jitswift5Hello:
	.long	128
	.long	16
	.long	16
	.long	0
	.quad	0
	.quad	L___unnamed_9
	.quad	l__INSTANCE_METHODS__TtC8jitswift5Hello
	.quad	0
	.quad	0
	.quad	0
	.quad	0

	.section	__TEXT,__const
	.align	4
l___unnamed_10:
	.asciz	"C8jitswift5Hello"

l___unnamed_11:
	.space	1

	.private_extern	__TMnC8jitswift5Hello
	.globl	__TMnC8jitswift5Hello
	.align	3
__TMnC8jitswift5Hello:
	.long	l___unnamed_10-__TMnC8jitswift5Hello
	.long	0
	.long	15
	.long	l___unnamed_11-(__TMnC8jitswift5Hello+12)
	.long	l_get_field_types_Hello-(__TMnC8jitswift5Hello+16)
	.long	0
	.long	__TMaC8jitswift5Hello-(__TMnC8jitswift5Hello+24)
	.long	10
	.long	0
	.long	0
	.long	0

	.private_extern	__TWoFC8jitswift5Hello9testHellofT_T_
	.globl	__TWoFC8jitswift5Hello9testHellofT_T_
	.align	3
__TWoFC8jitswift5Hello9testHellofT_T_:
	.quad	96

	.private_extern	__TWoFC8jitswift5Hello3sayfT_T_
	.globl	__TWoFC8jitswift5Hello3sayfT_T_
	.align	3
__TWoFC8jitswift5Hello3sayfT_T_:
	.quad	104

	.private_extern	__TWoFC8jitswift5HelloCfT10invocationGSqCSo12NSInvocation__S0_
	.globl	__TWoFC8jitswift5HelloCfT10invocationGSqCSo12NSInvocation__S0_
	.align	3
__TWoFC8jitswift5HelloCfT10invocationGSqCSo12NSInvocation__S0_:
	.quad	112

	.private_extern	__TWoFC8jitswift5HelloCfT8selectorV10ObjectiveC8Selector_S0_
	.globl	__TWoFC8jitswift5HelloCfT8selectorV10ObjectiveC8Selector_S0_
	.align	3
__TWoFC8jitswift5HelloCfT8selectorV10ObjectiveC8Selector_S0_:
	.quad	120

	.private_extern	__TWoFC8jitswift5HelloCfT_S0_
	.globl	__TWoFC8jitswift5HelloCfT_S0_
	.align	3
__TWoFC8jitswift5HelloCfT_S0_:
	.quad	128

	.private_extern	__TMLC8jitswift5Hello
	.globl	__TMLC8jitswift5Hello
.zerofill __DATA,__common,__TMLC8jitswift5Hello,8,3
	.section	__DATA,__objc_data
	.align	3
__TMfC8jitswift5Hello:
	.quad	__TFC8jitswift5HelloD
	.quad	__TWVBO
	.quad	_OBJC_METACLASS_$__TtC8jitswift5Hello
	.quad	_OBJC_CLASS_$_XCTestCase
	.quad	__objc_empty_cache
	.quad	0
	.quad	l__DATA__TtC8jitswift5Hello+1
	.long	1
	.long	0
	.long	16
	.short	7
	.short	0
	.long	136
	.long	16
	.quad	__TMnC8jitswift5Hello-(__TMfC8jitswift5Hello+80)
	.quad	0
	.quad	__TFC8jitswift5Hello9testHellofT_T_
	.quad	__TFC8jitswift5Hello3sayfT_T_
	.quad	__TFC8jitswift5HellocfT10invocationGSqCSo12NSInvocation__S0_
	.quad	__TFC8jitswift5HellocfT8selectorV10ObjectiveC8Selector_S0_
	.quad	__TFC8jitswift5HellocfT_S0_

	.section	__TEXT,__swift3_typeref,regular,no_dead_strip
	.align	4
L___unnamed_12:
	.asciz	"C8jitswift5Hello"

	.section	__TEXT,__swift3_fieldmd,regular,no_dead_strip
	.align	2
__TMRfC8jitswift5Hello:
	.long	L___unnamed_12-__TMRfC8jitswift5Hello
	.short	7
	.short	12
	.long	0

	.section	__TEXT,__swift3_typeref,regular,no_dead_strip
L___unnamed_13:
	.asciz	"Ps9AnyObject_"

L___unnamed_14:
	.asciz	"super"

L___unnamed_15:
	.asciz	"CSo10XCTestCase"

	.section	__TEXT,__swift3_assocty,regular,no_dead_strip
	.align	2
__TMRsC8jitswift5Hello:
	.long	L___unnamed_12-__TMRsC8jitswift5Hello
	.long	L___unnamed_13-(__TMRsC8jitswift5Hello+4)
	.long	1
	.long	8
	.long	L___unnamed_14-(__TMRsC8jitswift5Hello+16)
	.long	L___unnamed_15-(__TMRsC8jitswift5Hello+20)

	.private_extern	__swift_FORCE_LOAD_$_swiftXCTest_$_jitswift
	.section	__DATA,__data
	.globl	__swift_FORCE_LOAD_$_swiftXCTest_$_jitswift
	.weak_definition	__swift_FORCE_LOAD_$_swiftXCTest_$_jitswift
	.align	3
__swift_FORCE_LOAD_$_swiftXCTest_$_jitswift:
	.quad	__swift_FORCE_LOAD_$_swiftXCTest

	.private_extern	__swift_FORCE_LOAD_$_swiftFoundation_$_jitswift
	.globl	__swift_FORCE_LOAD_$_swiftFoundation_$_jitswift
	.weak_definition	__swift_FORCE_LOAD_$_swiftFoundation_$_jitswift
	.align	3
__swift_FORCE_LOAD_$_swiftFoundation_$_jitswift:
	.quad	__swift_FORCE_LOAD_$_swiftFoundation

	.private_extern	__swift_FORCE_LOAD_$_swiftObjectiveC_$_jitswift
	.globl	__swift_FORCE_LOAD_$_swiftObjectiveC_$_jitswift
	.weak_definition	__swift_FORCE_LOAD_$_swiftObjectiveC_$_jitswift
	.align	3
__swift_FORCE_LOAD_$_swiftObjectiveC_$_jitswift:
	.quad	__swift_FORCE_LOAD_$_swiftObjectiveC

	.private_extern	__swift_FORCE_LOAD_$_swiftDarwin_$_jitswift
	.globl	__swift_FORCE_LOAD_$_swiftDarwin_$_jitswift
	.weak_definition	__swift_FORCE_LOAD_$_swiftDarwin_$_jitswift
	.align	3
__swift_FORCE_LOAD_$_swiftDarwin_$_jitswift:
	.quad	__swift_FORCE_LOAD_$_swiftDarwin

	.private_extern	__swift_FORCE_LOAD_$_swiftIOKit_$_jitswift
	.globl	__swift_FORCE_LOAD_$_swiftIOKit_$_jitswift
	.weak_definition	__swift_FORCE_LOAD_$_swiftIOKit_$_jitswift
	.align	3
__swift_FORCE_LOAD_$_swiftIOKit_$_jitswift:
	.quad	__swift_FORCE_LOAD_$_swiftIOKit

	.private_extern	__swift_FORCE_LOAD_$_swiftDispatch_$_jitswift
	.globl	__swift_FORCE_LOAD_$_swiftDispatch_$_jitswift
	.weak_definition	__swift_FORCE_LOAD_$_swiftDispatch_$_jitswift
	.align	3
__swift_FORCE_LOAD_$_swiftDispatch_$_jitswift:
	.quad	__swift_FORCE_LOAD_$_swiftDispatch

	.private_extern	__swift_FORCE_LOAD_$_swiftCoreGraphics_$_jitswift
	.globl	__swift_FORCE_LOAD_$_swiftCoreGraphics_$_jitswift
	.weak_definition	__swift_FORCE_LOAD_$_swiftCoreGraphics_$_jitswift
	.align	3
__swift_FORCE_LOAD_$_swiftCoreGraphics_$_jitswift:
	.quad	__swift_FORCE_LOAD_$_swiftCoreGraphics

	.private_extern	__swift_FORCE_LOAD_$_swiftAppKit_$_jitswift
	.globl	__swift_FORCE_LOAD_$_swiftAppKit_$_jitswift
	.weak_definition	__swift_FORCE_LOAD_$_swiftAppKit_$_jitswift
	.align	3
__swift_FORCE_LOAD_$_swiftAppKit_$_jitswift:
	.quad	__swift_FORCE_LOAD_$_swiftAppKit

	.private_extern	__swift_FORCE_LOAD_$_swiftCoreImage_$_jitswift
	.globl	__swift_FORCE_LOAD_$_swiftCoreImage_$_jitswift
	.weak_definition	__swift_FORCE_LOAD_$_swiftCoreImage_$_jitswift
	.align	3
__swift_FORCE_LOAD_$_swiftCoreImage_$_jitswift:
	.quad	__swift_FORCE_LOAD_$_swiftCoreImage

	.private_extern	__swift_FORCE_LOAD_$_swiftXPC_$_jitswift
	.globl	__swift_FORCE_LOAD_$_swiftXPC_$_jitswift
	.weak_definition	__swift_FORCE_LOAD_$_swiftXPC_$_jitswift
	.align	3
__swift_FORCE_LOAD_$_swiftXPC_$_jitswift:
	.quad	__swift_FORCE_LOAD_$_swiftXPC

	.private_extern	__swift_FORCE_LOAD_$_swiftQuartzCore_$_jitswift
	.globl	__swift_FORCE_LOAD_$_swiftQuartzCore_$_jitswift
	.weak_definition	__swift_FORCE_LOAD_$_swiftQuartzCore_$_jitswift
	.align	3
__swift_FORCE_LOAD_$_swiftQuartzCore_$_jitswift:
	.quad	__swift_FORCE_LOAD_$_swiftQuartzCore

	.private_extern	__swift_FORCE_LOAD_$_swiftCoreData_$_jitswift
	.globl	__swift_FORCE_LOAD_$_swiftCoreData_$_jitswift
	.weak_definition	__swift_FORCE_LOAD_$_swiftCoreData_$_jitswift
	.align	3
__swift_FORCE_LOAD_$_swiftCoreData_$_jitswift:
	.quad	__swift_FORCE_LOAD_$_swiftCoreData

	.section	__TEXT,__swift2_types,regular,no_dead_strip
	.align	3
l_type_metadata_table:
	.long	(__TMfC8jitswift5Hello+16)-l_type_metadata_table
	.long	15

	.private_extern	___swift_reflection_version
	.section	__TEXT,__const
	.globl	___swift_reflection_version
	.weak_definition	___swift_reflection_version
	.align	1
___swift_reflection_version:
	.short	1

.zerofill __DATA,__bss,l_field_type_vector_Hello,8,3
	.section	__DATA,__objc_classlist,regular,no_dead_strip
	.align	3
_objc_classes:
	.quad	__TMC8jitswift5Hello

	.no_dead_strip	__TMRfC8jitswift5Hello
	.no_dead_strip	__TMRsC8jitswift5Hello
	.no_dead_strip	__swift_FORCE_LOAD_$_swiftXCTest_$_jitswift
	.no_dead_strip	__swift_FORCE_LOAD_$_swiftFoundation_$_jitswift
	.no_dead_strip	__swift_FORCE_LOAD_$_swiftObjectiveC_$_jitswift
	.no_dead_strip	__swift_FORCE_LOAD_$_swiftDarwin_$_jitswift
	.no_dead_strip	__swift_FORCE_LOAD_$_swiftIOKit_$_jitswift
	.no_dead_strip	__swift_FORCE_LOAD_$_swiftDispatch_$_jitswift
	.no_dead_strip	__swift_FORCE_LOAD_$_swiftCoreGraphics_$_jitswift
	.no_dead_strip	__swift_FORCE_LOAD_$_swiftAppKit_$_jitswift
	.no_dead_strip	__swift_FORCE_LOAD_$_swiftCoreImage_$_jitswift
	.no_dead_strip	__swift_FORCE_LOAD_$_swiftXPC_$_jitswift
	.no_dead_strip	__swift_FORCE_LOAD_$_swiftQuartzCore_$_jitswift
	.no_dead_strip	__swift_FORCE_LOAD_$_swiftCoreData_$_jitswift
	.no_dead_strip	l_type_metadata_table
	.no_dead_strip	___swift_reflection_version
	.no_dead_strip	_objc_classes
	.linker_option "-lswiftCore"
	.linker_option "-lswiftXCTest"
	.linker_option "-framework", "XCTest"
	.linker_option "-lswiftFoundation"
	.linker_option "-framework", "Foundation"
	.linker_option "-lswiftObjectiveC"
	.linker_option "-lswiftDarwin"
	.linker_option "-framework", "CoreServices"
	.linker_option "-lswiftIOKit"
	.linker_option "-framework", "IOKit"
	.linker_option "-lswiftDispatch"
	.linker_option "-framework", "CoreFoundation"
	.linker_option "-framework", "DiskArbitration"
	.linker_option "-framework", "CFNetwork"
	.linker_option "-framework", "Security"
	.linker_option "-lswiftCoreGraphics"
	.linker_option "-framework", "CoreGraphics"
	.linker_option "-framework", "ApplicationServices"
	.linker_option "-framework", "CoreText"
	.linker_option "-framework", "ImageIO"
	.linker_option "-lswiftAppKit"
	.linker_option "-framework", "AppKit"
	.linker_option "-lswiftCoreImage"
	.linker_option "-framework", "CoreImage"
	.linker_option "-framework", "IOSurface"
	.linker_option "-lswiftXPC"
	.linker_option "-framework", "OpenGL"
	.linker_option "-framework", "CoreVideo"
	.linker_option "-lswiftQuartzCore"
	.linker_option "-framework", "QuartzCore"
	.linker_option "-framework", "Metal"
	.linker_option "-lswiftCoreData"
	.linker_option "-framework", "CoreData"
	.linker_option "-lobjc"
	.section	__DATA,__objc_imageinfo,regular,no_dead_strip
L_OBJC_IMAGE_INFO:
	.long	0
	.long	1088


	.globl	__TMC8jitswift5Hello
	.private_extern	__TMC8jitswift5Hello
	.alt_entry	__TMC8jitswift5Hello
__TMC8jitswift5Hello = __TMfC8jitswift5Hello+16
	.globl	_OBJC_CLASS_$__TtC8jitswift5Hello
_OBJC_CLASS_$__TtC8jitswift5Hello = __TMC8jitswift5Hello
.subsections_via_symbols


