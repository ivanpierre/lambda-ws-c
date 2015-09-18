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
#include "keyval.h"
#include "strings.h"
#include "environment.h"
#include "collection.h"
#include "function.h"
#include "named.h"
#include "writer.h"
#include "number.h"
#include "var.h"
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
	Return String representation a KEYVAL
*/
static char *string_keyval(Node *node, bool map)
{
    ASSERT_NODE(node, IKEYVAL);
	char *res = NULL;
	char *k   = GET_ELEM_STRING(node, &keyval_key);
	char *v   = GET_ELEM_STRING(node, &keyval_value);
	if (map)
		asprintf(&res, "%s %s", k, v);
	else
		asprintf(&res, "[%s %s]", k, v);
	free(v);
	free(k);
	k = v = NULL;
	ASSERT(res, "Error printing keyval");
	unlink_node(node);
	return res;

	//*****************
	error_assert:
	free(k);
	free(v);
	free(res);
	unlink_node(node);
	return NULL;
}

/*
	Return array of string representation of element of coll
*/
static char **get_array(Node *node)
{
	Collection *coll = STRUCT(node);
	Node *curr = NULL;
	if(coll->size <= 0)
		goto error_assert; // no argument

	char **str_res = malloc(coll->size * sizeof(char *));
	ASSERT(str_res, "Error allocationg string array");

	for (long i = 0; i < coll->size; i++)
	{
		Node *curr = collection_nth(node, integer(i));
		// here we will print the node
		char *value;
		if (!curr)
			value = strdup("(null)");
		else if (curr->type->int_type == IKEYVAL)
			if(node->type->int_type == IMAP)
				value = string_keyval(curr, BOOL_TRUE);
			else
				value = string_keyval(curr, BOOL_FALSE);
		else
			value = print(curr);
		str_res[i] = value;
	}
	return str_res;

	//*****************
	error_assert:
	free(str_res);
	unlink_node(curr);
	return NULL;
}

/*
	calculate the size of the string to display inner elements
	There is at last one element
*/
static long list_size(long size, char *arr[])
{
	long     res = 0;
	for (int i   = 0; i < size; i++)
		res += strlen(arr[i]) + 1; // space
	return res; // '\0' on the last space
}

/*
	Return string of all elements of coll in right order
*/
static char *collection_get_inner_content(Node *node)
{
	bool       rev   = node->type->int_type == ILIST; // LIST is growing from head
	Collection *coll = STRUCT(node);
	long       size  = coll->size;
	if (size <= 0)
		return strdup("");

	char **str_res = get_array(node);
	ASSERT(str_res, "reasding the elements of inner list");
	long str_size = list_size(size, str_res);

	char *string_res = malloc(sizeof(char) * str_size);
	string_res[0] = '\0';

	for (long i = 0; i < size; i++)
	{
		// TRACE("cating '%s'", str_res[i]);
		if (i > 0)
			strcat(string_res, " ");
		strcat(string_res, str_res[i]);
		free(str_res[i]); // free each allocated string node
	}

	free(str_res); // free string array
	return string_res;

	//*****************
	error_assert:
	return NULL;
}

/*
	Return String representation of coll
*/
static char *string_collection(Node *coll)
{
	// get back inner content
	char *inner_content = collection_get_inner_content(coll);
	char *res           = NULL;
	if (!inner_content)
	ABORT("Error getting inner content of collection");

	switch (coll->type->int_type)
	{
		case ILIST:
			asprintf(&res, "(%s)", inner_content);
	        break;

		case IARRAY:
			asprintf(&res, "[%s]", inner_content);
	        break;

		case ISET:
			asprintf(&res, "#{%s}", inner_content);
	        break;

		case IMAP:
			asprintf(&res, "{%s}", inner_content);
	        break;

		default :
			free(inner_content);
			inner_content = NULL;
	        ABORT("string_coll : bad type for collection %s", coll->type->str_type);
	}
	free(inner_content);
	return res;

	//*****************
	error_assert:
	free(inner_content);
	free(res);
	return NULL;
}

/*
	String representation of reader
	returns linked allocated String
*/
static char *string_reader(Node *node)
{
	char *res = NULL;
	asprintf(&res, "<%s FILE*=?>", str_type(IREADER));
	return res;
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
	String representation of var
*/
static char *string_var(Node *node)
{
	char *res = NULL;

	char *sym = GET_ELEM_STRING(node, &var_symbol);
	char *typ = node->type->str_type;
	if (FALSE_Q_(var_bound_Q_(node)))
		asprintf(&res, "<%s symbol*=%s unbound>", typ, sym);
	else
	{
		char *val = GET_ELEM_STRING(node, &var_value);
		asprintf(&res, "<%s symbol*=%s value=%s>", typ, sym, val);
		free(val);
	}
	free(sym);

	return res;
}

/*
	String representation of environment
	returns linked allocated String
*/
static char *string_env(Node *node)
{
	Environment *env = STRUCT(node);
	char        *res = NULL;
	if (env->map)
	{
		char *map_str = string_collection(env->map);
		asprintf(&res, "<%s map=%s>", str_type(IENVIRONMENT), map_str);
		free(map_str);
	}
	else
		asprintf(&res, "<%s map=nil>", str_type(IENVIRONMENT));

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
	get interned name
*/
static char *string_named_interned(Node *node)
{
	char *complete = NULL;
	Node *name     = named_name(node);
	Node *ns       = named_ns(node);

	if (FALSE_Q_(ns))
		complete = GET_STRING(name);
	else
	{
		char *ns_str   = GET_STRING(ns);
		char *name_str = GET_STRING(name);

		asprintf(&complete, "%s/%s", ns_str, name_str);
		free(ns_str);
		free(name_str);
	}

	return complete;
}

/*
	Return allocated string of symbol name according to type
*/
static char *string_named_formated(Node *node)
{
	char *formated  = NULL;
	char *compl_str = string_named_interned(node);
	switch (node->type->int_type)
	{
		case IKEYWORD :
			asprintf(&formated, ":%s", compl_str);
	        break;

		case ISYMBOL :
			asprintf(&formated, "%s", compl_str);
	        break;

		default:
			break;;
	}
	free(compl_str);

	ASSERT(formated, "cannot format node");
	return formated;

	//*****************
	error_assert:
	free(formated);
	free(compl_str);
	return NULL;
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

		case IKEYWORD :
		case ISYMBOL :
			res = string_named_formated(node);
	        break;

		case ISTRING :
			if (readable)
				res = string_formated(node);
			else
				// res will be node and this node will be unlinked...
				res = GET_STRING(node);
	        break;

		case ILIST :
		case IARRAY :
		case IMAP :
		case ISET :
			// TRACE("Entring string_collection");
			res = string_collection(node);
	        break;

		case IENVIRONMENT :
			res = string_env(node);
	        break;

		case IKEYVAL :
			res = string_keyval(node, BOOL_FALSE);
	        break;

		case IFUNCTION :
		case ILAMBDA :
			res = string_function(node);
	        break;

		case IVAR :
			res = string_var(node);
	        break;

	        //    	case REF :
	        //    	case FUTURE :

		case IREADER :
			res = string_reader(node);
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

