	.file	"test_addr.c"
 # GNU C17 (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project) version 8.1.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 8.1.0, GMP version 6.1.2, MPFR version 4.0.1, MPC version 1.1.0, isl version isl-0.18-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: 
 # -iprefix D:/softwares/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/
 # -D_REENTRANT .\test_addr.c -mtune=core2 -march=nocona -fverbose-asm
 # options enabled:  -faggressive-loop-optimizations
 # -fasynchronous-unwind-tables -fauto-inc-dec -fchkp-check-incomplete-type
 # -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
 # -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
 # -fchkp-use-static-bounds -fchkp-use-static-const-bounds
 # -fchkp-use-wrappers -fcommon -fdelete-null-pointer-checks
 # -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
 # -ffp-int-builtin-inexact -ffunction-cse -fgcse-lm -fgnu-runtime
 # -fgnu-unique -fident -finline-atomics -fira-hoist-pressure
 # -fira-share-save-slots -fira-share-spill-slots -fivopts
 # -fkeep-inline-dllexport -fkeep-static-consts -fleading-underscore
 # -flifetime-dse -flto-odr-type-merging -fmath-errno -fmerge-debug-strings
 # -fpeephole -fpic -fplt -fprefetch-loop-arrays -freg-struct-return
 # -fsched-critical-path-heuristic -fsched-dep-count-heuristic
 # -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
 # -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
 # -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
 # -fset-stack-executable -fshow-column -fshrink-wrap-separate
 # -fsigned-zeros -fsplit-ivs-in-unroller -fssa-backprop -fstdarg-opt
 # -fstrict-volatile-bitfields -fsync-libcalls -ftrapping-math
 # -ftree-cselim -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im
 # -ftree-loop-ivcanon -ftree-loop-optimize -ftree-parallelize-loops=
 # -ftree-phiprop -ftree-reassoc -ftree-scev-cprop -funit-at-a-time
 # -funwind-tables -fverbose-asm -fzero-initialized-in-bss
 # -m128bit-long-double -m64 -m80387 -maccumulate-outgoing-args
 # -malign-double -malign-stringops -mcx16 -mfancy-math-387 -mfentry
 # -mfp-ret-in-387 -mfxsr -mieee-fp -mlong-double-80 -mmmx -mms-bitfields
 # -mno-sse4 -mpush-args -mred-zone -msse -msse2 -msse3 -mstack-arg-probe
 # -mstackrealign -mvzeroupper

	.text
	.globl	a
	.bss
	.align 4
a:
	.space 4
	.comm	p1, 8, 3
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "123456\0"
.LC1:
	.ascii "stack 1: %x \12\0"
.LC2:
	.ascii "stack 2: %x \12\0"
.LC3:
	.ascii "stack 3: %x \12\0"
.LC4:
	.ascii "const 1: %x \12\0"
.LC5:
	.ascii "global 1: %x \12\0"
.LC6:
	.ascii "heap 1: %x \12\0"
.LC7:
	.ascii "heap 2: %x \12\0"
.LC8:
	.ascii "bss 2: %x \12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp	 #
	.seh_pushreg	%rbp
	movq	%rsp, %rbp	 #,
	.seh_setframe	%rbp, 0
	subq	$64, %rsp	 #,
	.seh_stackalloc	64
	.seh_endprologue
 # .\test_addr.c:8: {
	call	__main	 #
 # .\test_addr.c:10:     char s[] = "abc"; //栈
	movl	$6513249, -16(%rbp)	 #, s
 # .\test_addr.c:12:     char *p3 = "123456"; //123456\0在常量区，p3在栈上 .LC0:
	leaq	.LC0(%rip), %rax	 #, tmp93
	movq	%rax, -8(%rbp)	 # tmp93, p3
 # .\test_addr.c:14:     p1 = (char *)malloc(10); //堆
	movl	$10, %ecx	 #,
	call	malloc	 #
	movq	%rax, %rdx	 # tmp94, _1
 # .\test_addr.c:14:     p1 = (char *)malloc(10); //堆
	leaq	p1(%rip), %rax	 #, tmp95
	movq	%rdx, (%rax)	 # _1, p1
 # .\test_addr.c:15:     p2 = (char *)malloc(20);  //堆
	movl	$20, %ecx	 #,
	call	malloc	 #
 # .\test_addr.c:15:     p2 = (char *)malloc(20);  //堆
	movq	%rax, -24(%rbp)	 # _2, p2
 # .\test_addr.c:20:     printf ("stack 1: %x \n", &b);
	leaq	-12(%rbp), %rax	 #, tmp97
	movq	%rax, %rdx	 # tmp97,
	leaq	.LC1(%rip), %rcx	 #,
	call	printf	 #
 # .\test_addr.c:21:     printf ("stack 2: %x \n", s);
	leaq	-16(%rbp), %rax	 #, tmp98
	movq	%rax, %rdx	 # tmp98,
	leaq	.LC2(%rip), %rcx	 #,
	call	printf	 #
 # .\test_addr.c:22:     printf ("stack 3: %x \n", &p2);
	leaq	-24(%rbp), %rax	 #, tmp99
	movq	%rax, %rdx	 # tmp99,
	leaq	.LC3(%rip), %rcx	 #,
	call	printf	 #
 # .\test_addr.c:23:     printf ("const 1: %x \n", p3);
	movq	-8(%rbp), %rax	 # p3, tmp100
	movq	%rax, %rdx	 # tmp100,
	leaq	.LC4(%rip), %rcx	 #,
	call	printf	 #
 # .\test_addr.c:24:     printf ("global 1: %x \n", &c);
	leaq	c.4100(%rip), %rdx	 #,
	leaq	.LC5(%rip), %rcx	 #,
	call	printf	 #
 # .\test_addr.c:25:     printf ("heap 1: %x \n", p1);
	leaq	p1(%rip), %rax	 #, tmp101
	movq	(%rax), %rax	 # p1, p1.0_3
	movq	%rax, %rdx	 # p1.0_3,
	leaq	.LC6(%rip), %rcx	 #,
	call	printf	 #
 # .\test_addr.c:26:     printf ("heap 2: %x \n", p2);
	movq	-24(%rbp), %rax	 # p2, p2.1_4
	movq	%rax, %rdx	 # p2.1_4,
	leaq	.LC7(%rip), %rcx	 #,
	call	printf	 #
 # .\test_addr.c:27:     printf ("global 1: %x \n", &a);
	leaq	a(%rip), %rdx	 #,
	leaq	.LC5(%rip), %rcx	 #,
	call	printf	 #
 # .\test_addr.c:28:     printf ("bss 2: %x \n", &p1);
	leaq	p1(%rip), %rax	 #, tmp102
	movq	%rax, %rdx	 # tmp102,
	leaq	.LC8(%rip), %rcx	 #,
	call	printf	 #
 # .\test_addr.c:30:     return 0;
	movl	$0, %eax	 #, _21
 # .\test_addr.c:31: }
	addq	$64, %rsp	 #,
	popq	%rbp	 #
	ret	
	.seh_endproc
.lcomm c.4100,4,4
	.data
	.align 32
arr.4101:
	.long	233
	.space 3996
	.ident	"GCC: (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
