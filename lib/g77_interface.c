/*
 * Copyright (C) 2002, 2003  Free Software Foundation, Inc.
 * 
 * This file is part of GNU libmatheval
 *
 * GNU libmatheval is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * GNU libmatheval is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with program; see the file COPYING. If not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
 * USA.
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "common.h"
#include "matheval.h"

/*
 * Wrapper for evaluator_create() function.  Evaluator objects will be passed
 * between Fortran and C as integers instead of void pointers, thus equal
 * length of int and void* types is assumed throughout this interface.
 */
int
evaluator_create__(char *string, int length)
{
	char           *stringz;/* Zero-terminated string representing
				 * function.  */
	int             evaluator;	/* Evaluator created for function.  */

	/* Copy string passed from Fortran code and terminate it with zero.  */
	stringz = XMALLOC(char, length + 1);
	memcpy(stringz, string, length * sizeof(char));
	stringz[length] = '\0';

	/* Call evaluator_create() function.  */
	evaluator = (int)evaluator_create(stringz);

	/* Free string used to create evaluator.  */
	XFREE(stringz);

	return evaluator;
}

/* Wrapper for evaluator_destroy() function.  */
void
evaluator_destroy__(int *evaluator)
{
	evaluator_destroy((void *)*evaluator);
}

/* Wrapper for evaluator_evaluate() function.  */
double
evaluator_evaluate__(int *evaluator, int *count, char *names,
		     double *values, int length)
{
	char          **names_copy;	/* Copy of variable names.  Names are
					 * passed in single string from
					 * Fortran code, delimited by blanks,
					 * while evaluator_evaluate()
					 * function expects array of strings.  */
	double          result;	/* Calculated value of function.  */
	int             i, j, n;/* Loop counters.  */

	/*
	 * Parse string containing variable names and create array of strings
	 * with each string containing single name.
	 */
	names_copy = XMALLOC(char *, *count);
	for (i = j = 0; i < *count && j < length; i++, j += n) {
		for (; names[j] == ' '; j++);
		for (n = 1; j + n < length && !(names[j + n] == ' '); n++);
		names_copy[i] = XMALLOC(char, n + 1);
		memcpy(names_copy[i], names + j, n * sizeof(char));
		names_copy[i][n] = '\0';
	}

	/* Call evaluator_evaluate() function.  */
	result =
		evaluator_evaluate((void *)*evaluator, *count, names_copy, values);

	/* Free memory used.  */
	for (i = 0; i < *count; i++)
		XFREE(names_copy[i]);
	XFREE(names_copy);

	return result;
}

/* Wrapper for evaluator_calculate_length() function.  */
int
evaluator_calculate_length__(int *evaluator)
{
	return evaluator_calculate_length((void *)*evaluator);
}

/* Wrapper for evaluator_write() function.  */
void
evaluator_write__(int *evaluator, char *string, int length)
{
	char           *stringz;/* Zero-terminated string for evaluator
				 * textual representation. */

	/* Allocate string of appropriate length to write evaluator to. */
	stringz = XMALLOC(char, length + 1);

	/* Call evaluator_write() function.  */
	evaluator_write((void *)*evaluator, stringz);

	/*
	 * Copy evaluator textual representation to string passed from
	 * Fortran code.
	 */
	memcpy(string, stringz, length * sizeof(char));

	/* Free string used for evaluator textual representation.  */
	XFREE(stringz);
}

/* Wrapper for evaluator_derivative() function.  */
int
evaluator_derivative__(int *evaluator, char *name, int length)
{
	char           *stringz;/* Zero terminated string containing
				 * derivation variable name.  */
	int             derivative;	/* Evaluator for function derivative.  */

	/*
	 * Copy variable name passed from Fortran code and terminate it with
	 * zero.
	 */
	stringz = XMALLOC(char, length + 1);
	memcpy(stringz, name, length * sizeof(char));
	stringz[length] = '\0';

	/* Call evaluator_derivative() function.  */
	derivative = (int)evaluator_derivative((void *)*evaluator, stringz);

	/* Free string containing derivation variable name.  */
	XFREE(stringz);

	return derivative;
}

/* Wrapper for evaluator_evaluate_x() function.  */
double
evaluator_evaluate_x__(int *evaluator, double *x)
{
	return evaluator_evaluate_x((void *)*evaluator, *x);
}

/* Wrapper for evaluator_evaluate_x_y() function.  */
double
evaluator_evaluate_x_y__(int *evaluator, double *x, double *y)
{
	return evaluator_evaluate_x_y((void *)*evaluator, *x, *y);
}

/* Wrapper for evaluator_evaluate_x_y_z() function.  */
double
evaluator_evaluate_x_y_z__(int *evaluator, double *x, double *y, double *z)
{
	return evaluator_evaluate_x_y_z((void *)*evaluator, *x, *y, *z);
}

/* Wrapper for evaluator_derivative_x() function.  */
int
evaluator_derivative_x__(int *evaluator)
{
	return (int)evaluator_derivative_x((void *)*evaluator);
}

/* Wrapper for evaluator_derivative_y() function.  */
int
evaluator_derivative_y__(int *evaluator)
{
	return (int)evaluator_derivative_y((void *)*evaluator);
}

/* Wrapper for evaluator_derivative_z() function.  */
int
evaluator_derivative_z__(int *evaluator)
{
	return (int)evaluator_derivative_z((void *)*evaluator);
}
