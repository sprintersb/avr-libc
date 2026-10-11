# Copyright (c) 2026  Georg-Johann Lay
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in
#   the documentation and/or other materials provided with the
#   distribution.
# * Neither the name of the copyright holders nor the names of
#   contributors may be used to endorse or promote products derived
#   from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

AC_DEFUN([CHECK_DOUBLE_COMPARISON],[dnl
    AC_MSG_CHECKING([how ${CC} compares 64-bit double])
    AC_COMPILE_IFELSE(
	[ AC_LANG_SOURCE([[
		#if !defined (__WITH_DOUBLE_COMPARISON__)
		#elif __WITH_DOUBLE_COMPARISON__ == 3
		#else
		int a[-1];
		#endif
		]],[])],
	[DOUBLE_COMPARE_tribool=tristate
	 AC_DEFINE(DOUBLE_COMPARE_TRISTATE, 1,
	           [Define if 64-bit double comparisons return tristate.])],
	[DOUBLE_COMPARE_tribool=bool
	 AC_DEFINE(DOUBLE_COMPARE_BOOL, 1,
	           [Define if 64-bit double comparisons return bool.])])
    AC_MSG_RESULT([$DOUBLE_COMPARE_tribool])
    ])
    AC_SUBST([DOUBLE_COMPARE_tribool])
])
dnl Local Variables:
dnl mode: autoconf
dnl End:
