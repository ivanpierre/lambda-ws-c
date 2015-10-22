/****
	General writer to output objects

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "strings.h"
#include "function.h"
#include "writer.h"
#include "number.h"
#include "free.h"
#include "free_internal.h"

Node *curr = NULL;

/*
	Constructor
*/
Node *writer(FILE *file)
{
	Node *node = new_node(IWRITER);
	ASSERT(node, ERR_CREATE_NEW, str_type(IWRITER));
	Writer *wr = STRUCT(node);
	wr->file = file;
	return node;

	//*************
	error_assert:
	unlink_node(node);
	return NULL;
}

/*
	Constructor avec fichier
*/
Node *writer_open_file(Node *name)
{
	ASSERT_NODE(name, ISTRING);
	char *filename = GET_STRING(name);
	unlink_node(name);
	FILE *handle = fopen(filename, "w");
	ASSERT(handle, "cannot open file %s for write", filename);
	free(filename);
	return writer(handle);

	//************
	error_assert:
	unlink_node(name);
	free(filename);
	return NULL;
}

/*
	Constructor stdout
*/
Node *writer_stdout()
{
	FILE *handle = stdout;
	ASSERT(handle, "cannot open stdout");
	return writer(handle);

	//************
	error_assert:
	return NULL;
}

/*
	Constructor stderr
*/
Node *writer_stderr()
{
	FILE *handle = stderr;
	ASSERT(handle, "cannot open stderr");
	return writer(handle);

	//************
	error_assert:
	return NULL;
}

/*
	Return file handle of the writer
*/
void *WRITER_FILE(Node *node)
{
	ASSERT_TYPE(node, IWRITER);
	Writer *wr = STRUCT(node);
	FILE *handle = wr->file;
	return handle;

	//************
	error_assert:
	return NULL;
}

/*
	Change current output
*/
Node *writer_curr(Node *node)
{
	ASSIGN(curr, node);
	return curr;
}

/*
	Change current output
*/
Node *writer_curr_close()
{
	unlink_node(curr);
	return NIL;
}

/*
	Write string to current output
*/
static void writer_print(char *str)
{
	FILE *handle = WRITER_FILE(curr);
	fprintf(handle, "%s", str);
	fflush(handle);
}

/*
	Write newline to current output
*/
static void writer_nl()
{
	FILE *handle = WRITER_FILE(curr);
	fprintf(handle, "\n");
	fflush(handle);
}

/*
	Flush current output
*/
static void writer_flush()
{
	FILE *handle = WRITER_FILE(curr);
	fflush(handle);
}

/*
	Free writer and close file
*/
Node *writer_free(Node *node)
{
	Writer *wr = STRUCT(node);
	FILE *file = wr->file;
	fflush(file);
	if (file != stderr && file != stdout)
		fclose(file);

	free(node);
	return NULL;
}

/*
	String representation of reader
	returns linked allocated String
*/
static char *string_writer(Node *node)
{
	char *res = NULL;
	asprintf(&res, "<%s FILE*=?>", str_type(IWRITER));
	return res;
}


/*
	String representation for functions
	returns linked allocated String
*/
static char *string_function(Node *node)
{
	// TODO suppress GET_ELEM_STRING
	char *res     = NULL;
	char *closure = GET_ELEM_STRING(node, &function_closure);
	char *args    = GET_ELEM_STRING(node, &function_args);

	if (node->type->int_type == ILAMBDA)
	{
		char *body = GET_ELEM_STRING(node, &function_body);
		asprintf(&res, "<%s macro=%s special=%s args=%s closure=%s body=%s>", str_type(node->type->int_type),
		         TRUE_Q_(function_is_macro(node)) ? "yes" : "no", TRUE_Q_(function_is_special(node)) ? "yes" : "no",
		         args, closure, body);
		free(body);
	}
	else
	{
		asprintf(&res, "<%s macro=%s special=%s args=%s closure=%s>", str_type(node->type->int_type),
		         TRUE_Q_(function_is_macro(node)) ? "yes" : "no", TRUE_Q_(function_is_special(node)) ? "yes" : "no",
		         args, closure);
	}

	free(args);
	free(closure);
	return res;
}

/*
	print integer
*/
static char *string_integer(Node *node)
{
	char *formated = NULL;

	Integer *integer = STRUCT(node);
	asprintf(&formated, "%ld", integer->integer);

	return formated;
}

/*
	print decimal
*/
static char *string_decimal(Node *node)
{
	char *formated = NULL;

	Decimal *dec = STRUCT(node);
	asprintf(&formated, "%lf", dec->decimal);

	return formated;
}

/*
	Return allocated string node of string formatted according to type
*/
static char *string_formated(Node *node)
{
	String *str      = STRUCT(node);
	char   *formated = NULL;
	asprintf(&formated, "\"%s\"", str->string);
	return formated;
}

/*
	return string version of nodes according to type
*/
char *print_node(Node *node, bool readable)
{
	char *res = NULL;
	// TRACE("pruint_node(%s)", node->type->str_type);
	ASSERT_TYPE(node, INODES);
	// TRACE("print_node(%s) after assert", node->type->str_type);

	switch (node->type->int_type)
	{
		case INIL :
			res = strdup("nil");
	        break;

		case ITRUE :
			res = strdup("true");
	        break;

		case IFALSE :
			res = strdup("false");
	        break;

		case ISTRING :
			if (readable)
				res = string_formated(node);
			else
				// res will be node and this node will be unlinked...
				res = GET_STRING(node);
	        break;

		case IFUNCTION :
			res = string_function(node);
	        break;

		case IWRITER :
			res = string_writer(node);
	        break;

		case IINTEGER :
			res = string_integer(node);
	        break;

		case IDECIMAL :
			res = string_decimal(node);
	        break;

		default :
			TRACE("Unable to write %s", node->type->str_type);
	        break;
	}
	return res;

	// *****************
	error_assert:
	free(&res);
	return NULL;
}

/*
	def pointer for print
*/
char *(*print_ptr)(Node *node, bool readable) = &print_node;

/*
	PRINT node using pointer readable
*/
char *print(Node *node)
{
	return (*print_ptr)(node, BOOL_FALSE);
}

/*
	PR node using pointer, non readable
*/
char *pr(Node *node)
{
	return (*print_ptr)(node, BOOL_TRUE);
}

/*
	PRINT node using pointer readable
*/
Node *PRINT(Node *node)
{
	ASSERT_NODE(node, INODES);

	char *str = NULL;
	// If no current output is selectioned : stdout
	if (!curr)
		writer_curr(writer_stdout());
	str = print(node);
	unlink_node(node);
	writer_print(str);
	free(str);
	return NIL;

	// *****************
	error_assert:
	unlink_node(node);
	return NULL;
}

/*
	PR node using pointer, non readable
*/
Node *PR(Node *node)
{
	ASSERT_NODE(node, INODES);

	char *str = NULL;
	// If no current output is selectioned : stdout
	if (!curr)
		writer_curr(writer_stdout());

	str = pr(node);
	unlink_node(node);
	writer_print(str);
	free(str);
	return NIL;

	// *****************
	error_assert:
	unlink_node(node);
	return NULL;
}

/*
	PRINT node using pointer readable
*/
Node *PRINTLN(Node *node)
{
	ASSERT_NODE(node, INODES);

	char *str = NULL;
	// If no current output is selectioned : stdout
	if (!curr)
		writer_curr(writer_stdout());

	str = print(node);
	unlink_node(node);
	writer_print(str);
	free(str);

	writer_nl();
	return NIL;

	// *****************
	error_assert:
	unlink_node(node);
	return NULL;
}

/*
	PR node using pointer, non readable
*/
Node *PRN(Node *node)
{
	ASSERT_NODE(node, INODES);

	char *str = NULL;
	// If no current output is selectioned : stdout
	if (!curr)
		writer_curr(writer_stdout());

	str = pr(node);
	unlink_node(node);
	writer_print(str);
	free(str);

	writer_nl();
	return NIL;

	// *****************
	error_assert:
	unlink_node(node);
	return NULL;
}

