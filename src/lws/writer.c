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
	char *filename = GET_STRING(name);
	unlink_node(&name);
	FILE *handle = fopen(filename, "w");
	ASSERT(handle, "cannot open file %s for write", filename);
	free(filename);
	return writer(handle);

	//************
	error_assert:
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
	Create writer with a file
*/
void *writer_file(Node *node)
{
	ACCESS_PTR(Writer, file, IWRITER);
}

/*
	Change current output
*/
Node *writer_curr(Node *node)
{
	if(curr != NULL)
		curr = writer_curr_close(curr);
	return curr = node;
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
Node *writer_print(Node *node)
{
	char *str = GET_STRING(node);
	FILE *handle = writer_file(curr);
	fprintf(handle, "%s", str);
	free(str);
	fflush(handle);

	return NIL;
}

/*
	Write newline to current output
*/
Node *writer_nl()
{
	FILE *handle = writer_file(curr);
	fprintf(handle, "\n");
	fflush(handle);
	return NIL;
}

/*
	Flush current output
*/
Node *writer_flush()
{
	FILE *handle = writer_file(curr);
	fflush(handle);
	return NIL;
}

/*
	Free writer and close file
*/
Node *writer_free(Node **node)
{
	// TODO clean up that mess
	FILE *file = writer_file(*node);
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
static Node *string_keyval(Node *node, bool map)
{
	ASSERT(node, "null pointer");
	ASSERT_TYPE(node, IKEYVAL);
	Node *res;
	char *k = GET_ELEM_STRING(node, &keyval_key);
	char *v = GET_ELEM_STRING(node, &keyval_value);
	if(map)
		res = string_sprintf("%s %s", k, v);
	else
		res = string_sprintf("[%s %s]", k, v);
	free(v);
	free(k);
	k = v = NULL;
	ASSERT(res, "Error printing keyval");
	return res;

	//*****************
	error_assert:
	unlink_node(&node);
	free(k);
	free(v);
	unlink_node(&res);
	return NULL;
}

/*
	Return array of string representation of element of coll
*/
static char **get_array(Node *node)
{
	ASSERT(node, "null pointer");
	ASSERT_TYPE(node, ICOLLECTION);

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
		Node *value;
		if(!curr)
			value = string("(null)");
		else if(curr->type->int_type == IKEYVAL )
			value = string_keyval(curr, node->type->int_type == IMAP);
		else
			value = print(curr);
		str_res[i] = GET_STRING(value);
		unlink_node(&value);
		unlink_node(&curr);
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
	ASSERT(node, "null pointer");
	ASSERT_TYPE(node, ICOLLECTION);

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
	unlink_node(&node);
	return NULL;
}

/*
	Return String representation of coll
*/
static Node *string_collection(Node *coll)
{
	// get back inner content
	char *inner_content = collection_get_inner_content(coll);
	Node *res;
	if(!inner_content)
		ABORT("Error getting inner content of collection");

	switch(coll->type->int_type)
	{
		case ILIST:
			res = string_sprintf("(%s)", inner_content);
			break;

		case IARRAY:
			res = string_sprintf("[%s]", inner_content);
			break;

		case ISET:
			res = string_sprintf("#{%s}", inner_content);
			break;

		case IMAP:
			res = string_sprintf("{%s}", inner_content);
			break;

		default :
			free(inner_content);
			ABORT("string_coll : bad type for collection %s", coll->type->str_type);
	}
	free(inner_content);
	return res;

	//*****************
	error_assert:
	unlink_node(&coll);
	free(inner_content);
	return NULL;
}

/*
	String representation of reader
	returns linked allocated String
*/
Node *string_reader(Node *node)
{
	ASSERT(node, "string_reader : null environment");
	ASSERT_TYPE(node, IREADER);
	unlink_node(&node);
	return string_sprintf("<%s FILE*=?>", str_type(IREADER));

	//*****************
	error_assert:
	unlink_node(&node);
	return NULL;
}

/*
	String representation of var
*/
Node *string_var(Node *node)
{
	Node *res = NULL;
	ASSERT(node, "null var");
	ASSERT_TYPE(node, IVAR);


	char *sym = GET_ELEM_STRING(node, &var_symbol);
	if(FALSE_Q_(var_bound_Q_(node)))
	{
		res = string_sprintf("<%s symbol*=%s unbound>", sym);
	}
	else
	{
		char* val = GET_ELEM_STRING(node, &var_value);
		res = string_sprintf("<%s symbol*=%s value=%s>", sym);
		free(val);
	}
	free(sym);

	return res;

	//*****************
	error_assert:
	unlink_node(&node);
	unlink_node(&res);
	return NULL;
}

/*
	String representation of environment
	returns linked allocated String
*/
static Node *string_env(Node *node)
{
	ASSERT(node, "null environment");
	ASSERT_TYPE(node, IENVIRONMENT);

	Node *map = environment_map(node);
	if (map)
	{
		Node *map_str = PRINT(map);
		unlink_node(&map);

		char *map_str_str = GET_STRING(map_str);
		Node *res = string_sprintf("<%s map=%s>", str_type(IENVIRONMENT), map_str_str);
		free(map_str_str);
		unlink_node(&map_str);
		return res;
	}

	return string_sprintf("<%s map=null>", str_type(IENVIRONMENT));

	//*****************
	error_assert:
	unlink_node(&node);
	unlink_node(&map);
	return NULL;
}


/*
	String representation for functions
	returns linked allocated String
*/
static Node *string_function(Node *node)
{
	ASSERT(node, "null pointer");
	ASSERT_TYPE(node, ICALLABLE);

	Node *res = NULL;
	char *closure = GET_ELEM_STRING(node, &function_closure);
	char *args = GET_ELEM_STRING(node, &function_args);

	if(node->type->int_type == ILAMBDA)
	{
		char *body = GET_ELEM_STRING(node, &function_body);
		res = string_sprintf("<%s macro=%s special=%s args=%s closure=%s body=%s>",
								str_type(node->type->int_type),
								TRUE_Q_(function_is_macro(node)) ? "yes" : "no",
								TRUE_Q_(function_is_special(node)) ? "yes" : "no",
								args, closure, body);
		free(body);
	}
	else
	{
		res = string_sprintf("<%s macro=%s special=%s args=%s closure=%s>",
								str_type(node->type->int_type),
								TRUE_Q_(function_is_macro(node)) ? "yes" : "no",
								TRUE_Q_(function_is_special(node)) ? "yes" : "no",
								args, closure);
	}

	unlink_node(&node);
	free(args);
	free(closure);
	return res;

	//*****************
	error_assert:
	unlink_node(&node);
	return NULL;
}

/*
	get interned name
*/
static char *string_named_interned(Node *node)
{
	Node *complete = NULL;
	ASSERT_TYPE(node, INAMED);
	Node *name = named_name(node);
	Node *ns = named_ns(node);
	if(FALSE_Q_(ns))
	{
		link_node(&complete, name);
	}
	else
	{
		char *ns_str = GET_STRING(ns);
		char *name_str = GET_STRING(name);

		complete = string_sprintf("%s/%s", ns_str, name_str);
		free(ns_str);
		free(name_str);
	}

	char *compl_str = GET_STRING(complete);
	unlink_node(&complete);

	return compl_str;

	//*****************
	error_assert:
	unlink_node(&node);
	unlink_node(&complete);
	return NULL;
}


/*
	Return allocated string of symbol name according to type
*/
static Node *string_named_formated(Node *node)
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
	unlink_node(&node);
	unlink_node(&formated);
	return NULL;
}

/*
	print integer
*/
static Node *string_integer(Node *node)
{
	Node *res = NULL;
	char *formated = NULL;

	ASSERT_TYPE(node, IINTEGER);
	Integer *integer = STRUCT(node);
	asprintf(&formated, "%ld", integer->integer);

	if(formated)
		res = string(formated);
	else
		res = string("NaN");

	free(formated);
	return res;

	//*****************
	error_assert:
	unlink_node(&node);
	return NULL;
}

/*
	print decimal
*/
static Node *string_decimal(Node *node)
{
	Node *res = NULL;
	char *formated = NULL;

	ASSERT_TYPE(node, IDECIMAL);
	Decimal *dec = STRUCT(node);
	asprintf(&formated, "%lf", dec->decimal);

	if(formated)
		res = string(formated);
	else
		res = string("NaN");

	free(formated);
	return res;

	//*****************
	error_assert:
	unlink_node(&node);
	return NULL;
}

/*
	Return allocated string node of string formatted according to type
*/
static Node *string_formated(Node *node)
{
	ASSERT_TYPE(node, ISTRING);

	String *str = STRUCT(node);
	Node *formated = string_sprintf("\"%s\"",str->string);
	unlink_node(&node);
	ASSERT(formated, "cannot format string");
	return formated; // formated allocated

	//*****************
	error_assert:
	unlink_node(&node);
	unlink_node(&formated);
	return NULL;
}

/*
	return string version of nodes according to type
*/
Node *print_node(Node *node, bool readable)
{
	ASSERT(node, "NULL node");
	Node *res = NULL;
	switch(node->type->int_type)
	{
		case INIL :
			res = string_sprintf("nil");
			break;

		case ITRUE :
			res = string_sprintf("true");
			break;

		case IFALSE :
			res = string_sprintf("false");
			break;

		case IKEYWORD :
		case ISYMBOL :
			res = string_named_formated(node);
			break;

		case ISTRING :
			if(readable)
			{
				res = string_formated(node);
				break;
			}
			else
			{
				// res will be node and this node will be unlinked...
				link_node(&res, node);
				break;
			}

		case ILIST :
		case IARRAY :
		case IMAP :
		case ISET :
			res = string_collection(node);
			break;


//      case ENV_STACK :

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

		case IINTEGER :
			res = string_integer(node);
			break;

		case IDECIMAL :
			res = string_decimal(node);
			break;

		default :
			break;
	}

	unlink_node(&node);
	return res;

	// *****************
	error_assert:
	unlink_node(&node);
	unlink_node(&res);
	return NULL;
}

/*
	def pointer for print
*/
Node *(*print_ptr)(Node *node, bool readable) = &print_node;

/*
	PRINT node using pointer readable
*/
Node *print(Node *node)
{
	return (*print_ptr)(node, BOOL_FALSE);
}

/*
	PR node using pointer, non readable
*/
Node *pr(Node *node)
{
	return (*print_ptr)(node, BOOL_TRUE);
}

/*
	PRINT node using pointer readable
*/
Node *PRINT(Node *node)
{
	if(!curr)
		writer_curr(writer_stdout());

	Node *pr_node = print(node);
	writer_print(pr_node);
	unlink_node(&pr_node);

	return NIL;
}

/*
	PR node using pointer, non readable
*/
Node *PR(Node *node)
{
	if(!curr)
		writer_curr(writer_stdout());

	Node *pr_node = pr(node);
	writer_print(pr_node);
	unlink_node(&pr_node);

	return NIL;
}

/*
	PRINT node using pointer readable
*/
Node *PRINTLN(Node *node)
{
	if(!curr)
		writer_curr(writer_stdout());

	Node *pr_node = print(node);
	writer_print(pr_node);
	unlink_node(&pr_node);

	writer_nl();
	return NIL;
}

/*
	PR node using pointer, non readable
*/
Node *PRN(Node *node)
{
	if(!curr)
		writer_curr(writer_stdout());

	Node *pr_node = pr(node);
	writer_print(pr_node);
	unlink_node(&pr_node);

	writer_nl();
	return NIL;
}

