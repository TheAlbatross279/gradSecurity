dnl  AMD K6-2 mpn_com -- mpn bitwise one's complement.

dnl  Copyright 1999-2002 Free Software Foundation, Inc.

dnl  This file is part of the GNU MP Library.

dnl  The GNU MP Library is free software; you can redistribute it and/or modify
dnl  it under the terms of the GNU Lesser General Public License as published
dnl  by the Free Software Foundation; either version 3 of the License, or (at
dnl  your option) any later version.

dnl  The GNU MP Library is distributed in the hope that it will be useful, but
dnl  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
dnl  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
dnl  License for more details.

dnl  You should have received a copy of the GNU Lesser General Public License
dnl  along with the GNU MP Library.  If not, see https://www.gnu.org/licenses/.

include(`../config.m4')

NAILS_SUPPORT(0-31)


C    alignment dst/src, A=0mod8 N=4mod8
C       A/A   A/N   N/A   N/N
C K6-2  1.0   1.18  1.18  1.18  cycles/limb
C K6    1.5   1.85  1.75  1.85


C void mpn_com (mp_ptr dst, mp_srcptr src, mp_size_t size);
C
C Take the bitwise ones-complement of src,size and write it to dst,size.

defframe(PARAM_SIZE,12)
defframe(PARAM_SRC, 8)
defframe(PARAM_DST, 4)

	TEXT
	ALIGN(16)
PROLOGUE(mpn_com)
deflit(`FRAME',0)

	movl	PARAM_SIZE, %ecx
	movl	PARAM_SRC, %eax
	movl	PARAM_DST, %edx
	shrl	%ecx
	jnz	L(two_or_more)

	movl	(%eax), %eax
	notl_or_xorl_GMP_NUMB_MASK(	%eax)
	movl	%eax, (%edx)
	ret


L(two_or_more):
	pushl	%ebx	FRAME_pushl()
	pcmpeqd	%mm7, %mm7		C all ones

	movl	%ecx, %ebx
ifelse(GMP_NAIL_BITS,0,,
`	psrld	$GMP_NAIL_BITS, %mm7')	C clear nails



	ALIGN(8)
L(top):
	C eax	src
	C ebx	floor(size/2)
	C ecx	counter
	C edx	dst
	C
	C mm0	scratch
	C mm7	mask

	movq	-8(%eax,%ecx,8), %mm0
	pxor	%mm7, %mm0
	movq	%mm0, -8(%edx,%ecx,8)
	loop	L(top)


	jnc	L(no_extra)
	movl	(%eax,%ebx,8), %eax
	notl_or_xorl_GMP_NUMB_MASK(	%eax)
	movl	%eax, (%edx,%ebx,8)
L(no_extra):

	popl	%ebx
	emms_or_femms
	ret

EPILOGUE()