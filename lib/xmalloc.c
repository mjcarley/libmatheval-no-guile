/*
 * Copyright (C) 1999, 2002, 2003  Free Software Foundation, Inc.
 * 
 * This file is part of GNU libmatheval
 * 
 * GNU libmatheval is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2, or (at your option) any later
 * version.
 * 
 * GNU libmatheval is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * program; see the file COPYING. If not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "common.h"
#include "error.h"

#if !HAVE_BZERO && HAVE_MEMSET
#define bzero(buf, bytes) ((void) memset (buf, 0, bytes))
#endif

void           *
xmalloc(size_t num)
{
	/*
	 * Call malloc() and check return value.
	 */
	void           *new = malloc(num);

	if (!new)
		error_fatal("unable to allocate memory");
	return new;
}

void           *
xrealloc(void *p, size_t num)
{
	void           *new;

	/*
	 * If memory not already allocated, fall back to xmalloc().
	 */
	if (!p)
		return xmalloc(num);

	/*
	 * Otherwise, call realloc() and check return value.
	 */
	new = realloc(p, num);
	if (!new)
		error_fatal("unable to allocate memory");

	return new;
}

void           *
xcalloc(size_t num, size_t size)
{
	/*
	 * Allocate memory and fill with zeroes.
	 */
	void           *new = xmalloc(num * size);

	bzero(new, num * size);
	return new;
}
