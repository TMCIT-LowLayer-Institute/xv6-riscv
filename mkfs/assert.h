/*
 * Copyright 2024 TMCIT-LowLayer-Institute. All rights reserved.
 */
/*	$OpenBSD: assert.h,v 1.15 2020/09/06 12:57:25 millert Exp $	*/
/*	$NetBSD: assert.h,v 1.6 1994/10/26 00:55:44 cgd Exp $	*/

/*-
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)assert.h	8.2 (Berkeley) 1/21/94
 *	@(#)cdefs.h	8.7 (Berkeley) 1/21/94
 */

/*
 * Unlike other ANSI header files, <assert.h> may usefully be included
 * multiple times, with and without NDEBUG defined.
 */

#undef assert
#undef _assert

#ifdef NDEBUG
# define	assert(e)	((void)0)
# define	_assert(e)	((void)0)
#else
# define	_assert(e)	assert(e)
# if __ISO_C_VISIBLE >= 1999
#  define	assert(e)	((e) ? (void)0 : __assert2(__FILE__, __LINE__, __func__, #e))
# else
#  define	assert(e)	((e) ? (void)0 : __assert(__FILE__, __LINE__, #e))
# endif
#endif

#ifndef _ASSERT_H_
#define _ASSERT_H_

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112
#define static_assert _Static_assert
#endif

#if defined(__cplusplus)
#define	__BEGIN_EXTERN_C	extern "C" {
#define	__END_EXTERN_C		}
#else
#define	__BEGIN_EXTERN_C
#define	__END_EXTERN_C
#endif

/*
 * Macro to test if we're using a specific version of gcc or later.
 */
#ifdef __GNUC__
#define __GNUC_PREREQ__(ma, mi) \
	((__GNUC__ > (ma)) || (__GNUC__ == (ma) && __GNUC_MINOR__ >= (mi)))
#else
#define __GNUC_PREREQ__(ma, mi) 0
#endif

#if !__GNUC_PREREQ__(2, 5) && !defined(__PCC__)
#define	__attribute__(x)	/* delete __attribute__ if non-gcc or gcc1 */
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#define	__dead		__volatile
#define	__pure		__const
#endif
#else
#define __dead		__attribute__((__noreturn__))
#define __pure		__attribute__((__const__))
#endif

#if __GNUC_PREREQ__(4, 0)
#define	__dso_public	__attribute__((__visibility__("default")))
#define	__dso_hidden	__attribute__((__visibility__("hidden")))
#define	__BEGIN_PUBLIC_DECLS \
	_Pragma("GCC visibility push(default)") __BEGIN_EXTERN_C
#define	__END_PUBLIC_DECLS	__END_EXTERN_C _Pragma("GCC visibility pop")
#define	__BEGIN_HIDDEN_DECLS \
	_Pragma("GCC visibility push(hidden)") __BEGIN_EXTERN_C
#define	__END_HIDDEN_DECLS	__END_EXTERN_C _Pragma("GCC visibility pop")
#else
#define	__dso_public
#define	__dso_hidden
#define	__BEGIN_PUBLIC_DECLS	__BEGIN_EXTERN_C
#define	__END_PUBLIC_DECLS	__END_EXTERN_C
#define	__BEGIN_HIDDEN_DECLS	__BEGIN_EXTERN_C
#define	__END_HIDDEN_DECLS	__END_EXTERN_C
#endif

#define	__BEGIN_DECLS	__BEGIN_EXTERN_C
#define	__END_DECLS	__END_EXTERN_C

__BEGIN_DECLS
__dead void __assert(const char *, int, const char *);
__dead void __assert2(const char *, int, const char *, const char *);
__END_DECLS
#endif
