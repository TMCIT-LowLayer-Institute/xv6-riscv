/*
 * Copyright 2024 TMCIT-LowLayer-Institute. All rights reserved.
 */
/*	$OpenBSD: string.h,v 1.32 2017/09/05 03:16:13 schwarze Exp $	*/
/*	$NetBSD: string.h,v 1.6 1994/10/26 00:56:30 cgd Exp $	*/

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
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
 *	@(#)string.h	5.10 (Berkeley) 3/9/91
 */

/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright 2024 TMCIT-LowLayer-Institute. All rights reserved.
 */

#ifndef _STRING_H_
#define	_STRING_H_

#include <sys/types.h>

#include "assert.h"

#if __GNUC_PREREQ__(2, 96)
#define	__malloc_like	__attribute__((__malloc__))
#define	__pure		__attribute__((__const__))
#else
#define	__malloc_like
#define	__pure
#endif

#ifndef _SIZE_T_DECLARED
typedef	__size_t	size_t;
#define	_SIZE_T_DECLARED
#endif

__BEGIN_DECLS
void	*memccpy(void * __restrict, const void * __restrict, int, size_t);
void	*memchr(const void *, int, size_t) __pure;
void	*memrchr(const void *, int, size_t) __pure;
int	 memcmp(const void *, const void *, size_t) __pure;
void	*memcpy(void * __restrict, const void * __restrict, size_t);
void	*memmem(const void *, size_t, const void *, size_t) __pure;
void	*memmove(void *, const void *, size_t);
void	*mempcpy(void * __restrict, const void * __restrict, size_t);
void	*memset(void *, int, size_t);
char	*stpcpy(char * __restrict, const char * __restrict);
char	*stpncpy(char * __restrict, const char * __restrict, size_t);
char	*strcasestr(const char *, const char *) __pure;
char	*strcat(char * __restrict, const char * __restrict);
char	*strchrnul(const char*, int) __pure;
int	 strverscmp(const char *, const char *) __pure;
int	 strcmp(const char *, const char *) __pure;
int	 strcoll(const char *, const char *);
char	*strcpy(char * __restrict, const char * __restrict);
size_t	 strcspn(const char *, const char *) __pure;
char	*strdup(const char *) __malloc_like;
char	*strerror(int);
int	 strerror_r(int, char *, size_t);
size_t	 strlcat(char * __restrict, const char * __restrict, size_t);
size_t	 strlcpy(char * __restrict, const char * __restrict, size_t);
size_t	 strlen(const char *) __pure;

//void	 strmode(mode_t, char *);

char	*strncat(char * __restrict, const char * __restrict, size_t);
int	 strncmp(const char *, const char *, size_t) __pure;
char	*strncpy(char * __restrict, const char * __restrict, size_t);
char	*strndup(const char *, size_t) __malloc_like;
size_t	 strnlen(const char *, size_t) __pure;
char	*strnstr(const char *, const char *, size_t) __pure;
char	*strpbrk(const char *, const char *) __pure;
char	*strrchr(const char *, int) __pure;
char	*strsep(char **, const char *);
char	*strsignal(int);
size_t	 strspn(const char *, const char *) __pure;
char	*strstr(const char *, const char *) __pure;
char	*strtok(char * __restrict, const char * __restrict);
char	*strtok_r(char *, const char *, char **);
size_t	 strxfrm(char * __restrict, const char * __restrict, size_t);

#ifndef _SWAB_DECLARED
#define _SWAB_DECLARED

#ifndef _SSIZE_T_DECLARED
typedef	__ssize_t	ssize_t;
#define	_SSIZE_T_DECLARED
#endif /* _SIZE_T_DECLARED */

void	 swab(const void * __restrict, void * __restrict, ssize_t);

int	 timingsafe_bcmp(const void *, const void *, size_t);
int	 timingsafe_memcmp(const void *, const void *, size_t);



#ifndef _RSIZE_T_DEFINED
#define _RSIZE_T_DEFINED
typedef size_t rsize_t;
#endif

#ifndef _ERRNO_T_DEFINED
#define _ERRNO_T_DEFINED
typedef int errno_t;
#endif

/* ISO/IEC 9899:2011 K.3.7.4.1.1 */
errno_t memset_s(void *, rsize_t, int, rsize_t);

extern char *index(char const* sp, int c);
extern char *strchr(char const* sp, int c);
__END_DECLS

#endif 
#endif /* _STRING_H_ */
