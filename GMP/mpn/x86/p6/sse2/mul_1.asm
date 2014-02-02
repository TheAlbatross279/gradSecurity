dnl  Intel P6/SSE2 mpn_mul_1.

dnl  Copyright 2008 Free Software Foundation, Inc.

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

C TODO
C  * Write P6 specific SSE2 code.  It should reach 3 c/l.
C    The Pentium4 code runs at 4.2 c/l.

MULFUNC_PROLOGUE(mpn_mul_1)
include_mpn(`x86/pentium4/sse2/mul_1.asm')