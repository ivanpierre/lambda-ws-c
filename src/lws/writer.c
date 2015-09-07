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
	unlink_node(&node);
	return NULL;
}

/*
	Constructor avec fichier
*/
Node *writer_open_file(Node *name)
{
	Node *tmpname = NULL;
	ASSERT_NODE(name, tmpname, ISTRING);
	char *filename = GET_STRING(tmpname);
	unlink_node(&tmpname);
	FILE *handle = fopen(filename, "w");
	ASSERT(handle, "cannot open file %s for write", filename);
	free(filename);
	return writer(handle);

	//************
	error_assert:
	unlink_node(&tmpname);
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
	Writer *wr = STRUCT(node);
	return wr->file;
}

/*
	Change current output
*/
Node *writer_curr(Node *node)
{
	if(curr != node)
		return link_node(&curr, node);
	return curr;
}

/*
	Change current output
*/
Node *writer_curr_close()
{
	unlink_node(&curr);
	return NIL;
}

/*
	Write string to current output
*/
static Node *writer_print(Node *node)
{
	char *str = GET_STRING(node);
	FILE *handle = WRITER_FILE(curr);
	fprintf(handle, "%s", str);
	free(str);
	fflush(handle);

	return NIL;
}

/*
	Write newline to current output
*/
static Node *writer_nl()
{
	FILE *handle = WRITER_FILE(curr);
	fprintf(handle, "\n");
	fflush(handle);
	return NIL;
}

/*
	Flush current output
*/
Node *writer_flush()
{
	FILE *handle = WRITER_FILE(curr);
	fflush(handle);
	return NIL;
}

/*
	Free writer and close file
*/
Node *writer_free(Node **node)
{
	// TODO clean up that mess
	FILE *file = WRITER_FILE(*node);
	fflush(file);
	if(file != stderr && file != stdout)
		fclose(file);

	free(*node);
	*node = NULL;
	return NULL;
}

/*
	Return String representation a KEYVAL
*/
static char *string_keyval(Node *node, bool map)
{
	ASSERT(node, "null pointer");
	ASSERT_TYPE(node, IKEYVAL);
	char *res = NULL;
	char *k = GET_ELEM_STRING(node, &keyval_key);
	char *v = GET_ELEM_STRING(node, &keyval_value);
	if(map)
		asprintf(&res, "%s %s", k, v);
	else
		asprintf(&res, "[%s %s]", k, v);
	free(v);
	free(k);
	k = v = NULL;
	ASSERT(res, "Error printing keyval");
	return res;

	//*****************
	error_assert:
	free(k);
	free(v);
	free(res);
	return NULL;
}

/*
	Return array of string representation of element of coll
*/
static char **get_array(Node *node)
{
	Node *sn = collection_size(node);
	Collection *coll = STRUCT(node);
	if(coll->size <= 0)
		return NULL;

	char **str_res = malloc(coll->size * sizeof(char *));
	ASSERT(str_res, "Error allocationg string array");

	for(long i = 0; i < coll->size; i++)
	{
		Node *curr = collection_nth(node, integer(i));
		// here we will print the node
		char *value;
		if(!curr)
			value = strdup("(null)");
		else if(curr->type->int_type == IKEYVAL )
			value = string_keyval(curr, node->type->int_type == IMAP);
		else
			value = print(curr);
		str_res[i] = value;
		free(value);
		free(curr);
	}
	return str_res;

	//*****************
	error_assert:
	free(str_res);
	return NULL;
}

/*
	calculate the size of the string to display inner elements
	There is at last one element
*/
static long list_size(long size, char *arr[])
{
	long res = 0;
	for(int i = 0; i < size; i++)
		res += strlen(arr[i]) + 1; // space
	return res; // '\0' on the last space
}

/*
	Return string of all elements of coll in right order
*/
static char *collection_get_inner_content(Node *node)
{
	bool rev = node->type->int_type == ILIST; // LIST is growing from head
	Collection *coll = STRUCT(node);
	long size = coll->size;
	if(size <= 0)
		return strdup("");

	char **str_res = get_array(node);
	ASSERT(str_res, "reasding the elements of inner list");
	long str_size = list_size(size, str_res);

	char *string_res = malloc(sizeof(char) * str_size);
	string_res[0] = '\0';

	for(long i = rev ? size - 1 : 0;
				 rev ? i >=0 : i < size;
				 rev ? i-- : i++)
	{
		strcat(string_res, str_res[i]);
		if(i < size - 1)
			strcat(string_res, " ");
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
	char *res = NULL;
	if(!inner_content)
		ABORT("Error getting inner content of collection");

	switch(coll->type->int_type)
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
	if(FALSE_Q_(var_bound_Q_(node)))
		res = asprintf("<%s symbol*=%s unbound>", sym);
	else
	{
		char* val = GET_ELEM_STRING(node, &var_value);
		res = asprintf("<%s symbol*=%s value=%s>", sym);
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
	if (env->map)
	{
		char *map_str = string_collection(env->map);
		char *res = asprintf("<%s map=%s>", str_type(IENVIRONMENT), map_str);
		free(map_str);
		return res;
	}

	return asprintf("<%s map=null>", str_type(IENVIRONMENT));
}


/*
	String representation for functions
	returns linked allocated String
*/
static char *string_function(Node *node)
{
	Node *res = NULL;
	char *closure = GET_ELEM_STRING(node, &function_closure);
	char *args = GET_ELEM_STRING(node, &function_args);

	if(node->type->int_type == ILAMBDA)
	{
		char *body = GET_ELEM_STRING(node, &function_body);
		res = asprintf("<%s macro=%s special=%s args=%s closure=%s body=%s>",
						str_type(node->type->int_type),
						TRUE_Q_(function_is_macro(node)) ? "yes" : "no",
						TRUE_Q_(function_is_special(node)) ? "yes" : "no",
						args, closure, body);
		free(body);
	}
	else
	{
		res = asprintf("<%s macro=%s special=%s args=%s closure=%s>",
						str_type(node->type->int_type),
						TRUE_Q_(function_is_macro(node)) ? "yes" : "no",
						TRUE_Q_(function_is_special(node)) ? "yes" : "no",
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
	Node *name = named_name(node);
	Node *ns = named_ns(node);

	if(FALSE_Q_(ns))
		complete = GET_STRING(name);
	else
	{
		char *ns_str = GET_STRING(ns);
		char *name_str = GET_STRING(name);

		complete = asprintf("%s/%s", ns_str, name_str);
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
	Node *formated = NULL;
	char *compl_str = string_named_interned(node);
	switch(node->type->int_type)
	{
		case IKEYWORD :
			formated = string_sprintf(":%s", compl_str);
			break;
		case ISYMBOL :
			formated = string_sprintf("%s", compl_str);
			break;
		default:
			break;;
	}
	free(compl_str);

	ASSERT(formated, "cannot format node");
	return formated;

	//*****************
	error_assert:
	unlink_node(&formated);
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
static string *string_formated(Node *node)
{
	String *str = STRUCT(node);
	char *formated = NULL;
	asprintf(&formated"\"%s\"",str->string);
	return formated;
}

/*
	return string version of nodes according to type
*/
char *print_node(Node *node, bool readable)
{
	char *res = NULL;
	ASSERT_NODE(node, tmp_node, INODES);
	switch(tmp_node->type->int_type)
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
			res = string_named_formated(tmp_node);
			break;

		case ISTRING :
			if(readable)
				res = string_formated(tmp_node);
			else
				// res will be node and this node will be unlinked...
				res = GET_STRING(tmp_node);
			break;

		case ILIST :
		case IARRAY :
		case IMAP :
		case ISET :
			res = string_collection(tmp_node);
			break;


//      case ENV_STACK :

		case IENVIRONMENT :
			res = string_env(tmp_node);
			break;

		case IKEYVAL :
			res = string_keyval(tmp_node, BOOL_FALSE);
			break;

		case IFUNCTION :
		case ILAMBDA :
			res = string_function(tmp_node);
			break;

		case IVAR :
			res = string_var(tmp_node);
			break;

//    	case REF :
//    	case FUTURE :

		case IREADER :
			res = string_reader(tmp_node);
	        break;

		case IWRITER :
			res = string_writer(tmp_node);
	        break;

		case IINTEGER :
			res = string_integer(tmp_node);
			break;

		case IDECIMAL :
			res = string_decimal(tmp_node);
			break;

		default :
			TRACE("Unable to write %s", tmp_node->type->str_type);
			break;
	}
	unlink_node(&tmp_node);
	return res;

	// *****************
	error_assert:
	unlink_node(&res);
	unlink_node(&tmp_node);
	return NULL;
}

/*
	def pointer for print
*/
char *(*print_ptr)(Node *node, bool readable) = &print_node;

/*
	PRINT node using pointer readable
*/
string *print(Node *node)
{
	return (*print_ptr)(node, BOOL_FALSE);
}

/*
	PR node using pointer, non readable
*/
string *pr(Node *node)
{
	return (*print_ptr)(node, BOOL_TRUE);
}

/*
	PRINT node using pointer readable
*/
Node *PRINT(Node *node)
{
	// If no current output is selectioned : stdout
	if(!curr)
		writer_curr(writer_stdout());

	writer_print(print(node));
	return NIL;
}

/*
	PR node using pointer, non readable
*/
Node *PR(Node *node)
{
	// If no current output is selectioned : stdout
	if(!curr)
		writer_curr(writer_stdout());

	writer_print(pr(node));
	return NIL;
}

/*
	PRINT node using pointer readable
*/
Node *PRINTLN(Node *node)
{
	// If no current output is selectioned : stdout
	if(!curr)
		writer_curr(writer_stdout());

	writer_print(print(node));

	writer_nl();
	return NIL;
}

/*
	PR node using pointer, non readable
*/
Node *PRN(Node *node)
{
	// If no current output is selectioned : stdout
	if(!curr)
		writer_curr(writer_stdout());

	writer_print(pr(node));

	writer_nl();
	return NIL;
}

