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
#include "matheval.h"
#include "node.h"
#include "symbol_table.h"

/* Minimal length of evaluator symbol table.  */
#define MIN_TABLE_LENGTH 211

/*
 * Function used to parse string representing function (this function is
 * generated by parser generator).
 */
extern int      yyparse();

/*
 * Following variables are needed for parsing (parser is able to communicate
 * with program from which it is used through global variables only).
 */
char           *input_string;	/* String representing function.  */
Node           *root;		/* Root of tree representation of function.  */
SymbolTable    *symbol_table;	/* Evaluator symbol table.  */
int             ok;		/* Flag determining if parsing went OK.  */

/* Data structure representing evaluator.  */
typedef struct {
	Node           *root;	/* Root of tree representation of function.  */
	SymbolTable    *symbol_table;	/* Evalutor symbol table.  */
}               Evaluator;

void           *
evaluator_create(char *string)
{
	Evaluator      *evaluator;	/* Evaluator representing function
					 * given by string.  */
	char           *stringn;/* Copy of string terminated by newline
				 * character.  */

	/*
	 * Copy string representing function and terminate it with newline
	 * (this is necessary because parser expect newline character to
	 * terminate its input).
	 */
	stringn = XMALLOC(char, strlen(string) + 2);

	strcpy(stringn, string);
	strcat(stringn, "\n");

	/*
	 * Initialize global variables used by parser.
	 */
	input_string = stringn;
	root = NULL;
	symbol_table = symbol_table_create(MIN_TABLE_LENGTH);
	ok = 1;

	/*
	 * Do parsing.
	 */
	yyparse();

	/*
	 * Free copy of string representing function.
	 */
	XFREE(stringn);

	/*
	 * Return null pointer as error indicator if parsing error occured.
	 */
	if (!ok)
		return NULL;

	/*
	 * Simplify tree represention of function.
	 */
	root = node_simplify(root);

	/*
	 * Allocate memory for and initialize evaluator data structure.
	 */
	evaluator = XMALLOC(Evaluator, 1);
	evaluator->root = root;
	evaluator->symbol_table = symbol_table;

	return evaluator;
}

void
evaluator_destroy(void *evaluator)
{
	/*
	 * Destroy tree represention of function, symbol table, as well as
	 * data structure representing evaluator.
	 */
	node_destroy(((Evaluator *) evaluator)->root);
	symbol_table_destroy(((Evaluator *) evaluator)->symbol_table);
	XFREE(evaluator);
}

double
evaluator_evaluate(void *evaluator, int count, char **names, double *values)
{
	Record         *record;	/* Symbol table record corresponding to give
				 * variable name.  */
	int             i;	/* Loop counter.  */

	/*
	 * Assign values to symbol table records corresponding to variable
	 * names.
	 */
	for (i = 0; i < count; i++) {
		record = symbol_table_lookup(((Evaluator *) evaluator)->symbol_table, names[i]);
		if (record && record->type == 'v')
			record->data.value = values[i];
	}

	/*
	 * Evaluate function value using tree represention of function.
	 */
	return node_evaluate(((Evaluator *) evaluator)->root);
}

int
evaluator_calculate_length(void *evaluator)
{
	/*
	 * Calculate length of evaluator textual representation.
	 */
	return node_calculate_length(((Evaluator *) evaluator)->root);
}

void
evaluator_write(void *evaluator, char *string)
{
	/*
	 * Write evaluator textual representation to given string.
	 */
	node_write(((Evaluator *) evaluator)->root, string);
}

void           *
evaluator_derivative(void *evaluator, char *name)
{
	Evaluator      *derivative;	/* Derivative function evaluator.  */

	/*
	 * Allocate memory for and initalize data structure for evaluator
	 * representing derivative of function given by evaluator.
	 */
	derivative = XMALLOC(Evaluator, 1);
	derivative->root = node_simplify(node_derivative(((Evaluator *) evaluator)->root, name, ((Evaluator *) evaluator)->symbol_table));
	derivative->symbol_table = symbol_table_assign(((Evaluator *) evaluator)->symbol_table);

	return derivative;
}

double
evaluator_evaluate_x(void *evaluator, double x)
{
	char           *names[] = {"x"};	/* Array of variable names.  */
	double          values[1];	        /* Array of variable values.  */

	/*
	 * Evaluate function for given values of variable "x".
	 */
        values[0] = x;
	return evaluator_evaluate(evaluator, sizeof(names) / sizeof(names[0]), names, values);
}

double
evaluator_evaluate_x_y(void *evaluator, double x, double y)
{
	char           *names[] = {"x", "y"};	/* Array of variable names.  */
	double          values[2];	        /* Array of variable values.  */

	/*
	 * Evaluate function for given values of variable "x" and "y".
	 */
        values[0] = x, values[1] = y;
	return evaluator_evaluate(evaluator, sizeof(names) / sizeof(names[0]), names, values);
}

double
evaluator_evaluate_x_y_z(void *evaluator, double x, double y, double z)
{
	char           *names[] = {"x", "y", "z"};	/* Array of variable
							 * names.  */
	double          values[3];	 	/* Array of variable values.  */

	/*
	 * Evaluate function for given values of variable "x", "y" and "z".
	 */
        values[0] = x, values[1] = y, values[2] = z;
	return evaluator_evaluate(evaluator, sizeof(names) / sizeof(names[0]), names, values);
}

void           *
evaluator_derivative_x(void *evaluator)
{
	/*
	 * Differentiate function using derivation variable "x".
	 */
	return evaluator_derivative(evaluator, "x");
}

void           *
evaluator_derivative_y(void *evaluator)
{
	/*
	 * Differentiate function using derivation variable "y".
	 */
	return evaluator_derivative(evaluator, "y");
}

void           *
evaluator_derivative_z(void *evaluator)
{
	/*
	 * Differentiate function using derivation variable "z".
	 */
	return evaluator_derivative(evaluator, "z");
}
