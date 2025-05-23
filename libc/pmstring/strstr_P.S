/* Copyright (c) 2002, Philip Soeberg
   Copyright (c) 2005, 2006, 2007 Werner Boellmann
   Copyright (c) 2007  Dmirty Xmelkov
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

/*
   strstr_P.S
   Search string contained in a string

   Originally contributed by:
     Philip Soeberg <philip@soeberg.net>

   Modified for string s2 in program space by:
     Werner Boellmann <wb@muekno.de>
*/

#if !defined(__AVR_TINY__)

#if !defined(__DOXYGEN__)

#include "asmdef.h"

#define s1_hi r25
#define s1_lo r24
#define s2_hi r23
#define s2_lo r22

#define chr1   r20
#define	beg2   r21	/* begin of s2: s2[0]	*/
#define chr2   r0

ENTRY _U(strstr_P)

	X_movw	ZL, s2_lo
	X_lpm	beg2, Z+
	tst	beg2		; is str2 empty?
	breq	.L_ret		; return original string (req'd by standard)
	X_movw	s2_lo, ZL	; save: address of second s2 byte

0:	X_movw	XL, s1_lo

1:	ld	chr1, X+	; Find first char
	cp	chr1, beg2
	cpse	chr1, __zero_reg__
	brne	1b

	brne	.L_no_match	; end of s1
	X_movw	s1_lo, XL	; store return value

2:	X_lpm	chr2, Z+	; compare strings
	tst	chr2
	breq	.L_match	; end of s2
	ld	chr1, X+
	cp	chr1, chr2
	cpse	chr1, __zero_reg__	; break, if end of s1
	breq	2b

	X_movw	ZL, s2_lo	; restore s2+1
	cpse	chr1, __zero_reg__
	rjmp	0b

.L_no_match:
	ldi	s1_lo, lo8(1)
	ldi	s1_hi, hi8(1)
.L_match:
	sbiw	s1_lo, 1	; restore after post-increment
.L_ret:
	ret

ENDFUNC

#endif /* not __DOXYGEN__ */

#endif /* !defined(__AVR_TINY__) */
