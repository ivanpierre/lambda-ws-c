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
#include "env.h"
#include "collection.h"
#include "function.h"
#include "named.h"
#include "writer.h"
#include "number.h"
#include "var.h"
#include "free.h"

/*
    Writer
*/
typedef struct
{
    FILE            *file;
} Writer;

Node *curr = NULL;

/*
    Access Writer from Node
*/
static Writer *GET_WRITER(Node *node)
{
    return (Writer *)(node->val.compl);
}

/*
    Constructor
*/
Node *writer(FILE *file)
{
    fprintf(stderr, "create writer %ld\n", WRITER);
    Node *new_writer = NEW(WRITER);
    new_writer->val.compl = malloc(sizeof(Writer));
    GET_WRITER(new_writer)->file = file;
    return new_writer;
}

/*
    Constructor avec fichier
*/
Node *writer_open_file(Node *name)
{
    char *filename = GET_STRING(name);
    unlink_node(name);
    FILE *handle = fopen(filename, "w");
    ASSERT(handle, "cannot open file %s for write", filename);
    free(filename);
    return writer(handle);
}

/*
    Constructor stdout
*/
Node *writer_stdout()
{
    FILE *handle = stdout;
    ASSERT(handle, "cannot open stdout");
    return writer(handle);
}

/*
    Constructor stderr
*/
Node *writer_stderr()
{
    FILE *handle = stderr;
    ASSERT(handle, "cannot open stderr");
    return writer(handle);
}

/*
    Create writer with a file
*/
FILE *writer_file(Node *node)
{
    return GET_WRITER(node)->file;
}

/*
    Change current output
*/
Node *writer_curr(Node *node)
{
    if(curr != NULL)
        curr = unlink_node(curr);
    return curr = node;
}

/*
    Change current output
*/
Node *writer_curr_close()
{
    if(curr != NULL)
    {
        unlink_node(curr);
        curr = NULL;
    }
    return nil;
}

/*
    Write string to current output
*/
Node *writer_print(Node *node)
{
    String str = GET_STRING(node);
    fprintf(writer_file(curr), "%s", str);
    fflush(writer_file(curr));
    unlink_node(node);
    return nil;
}

/*
    Write newline to current output
*/
Node *writer_nl()
{
    fprintf(writer_file(curr), "\n");
    fflush(writer_file(curr));
    return nil;
}

/*
    Free writer and close file
*/
Node *writer_free(Node *node)
{
    // close the file, standard files will not be closed
    fprintf(stderr, "Closing writer %ld\n", WRITER);
    fflush(writer_file(curr));
    fclose(writer_file(curr));
    free(GET_WRITER(node));
    free(node);
    return nil;
}

/*
    Return String representation a KEYVAL
*/
static Node *string_keyval(Node *node, bool map)
{
    ASSERT(node, "null pointer");
    ASSERT_TYPE(node, KEYVAL, "error printing bad type : %s",
                str_type(node->type));
    Node *res;
    String k = GET_ELEM_STRING(node, &keyval_key);
    String v = GET_ELEM_STRING(node, &keyval_value);
    if(map)
        res = string_sprintf("%s %s", k, v);
    else
        res = string_sprintf("[%s %s]", k, v);
    free(v);
    free(k);
    unlink_node(node);
    ASSERT(res, "Error printing keyval");
    return res;
}

/*
    Return array of string representation of element of coll
*/
static char **get_array(Node *node)
{
    ASSERT(node, "null pointer");
    ASSERT_TYPE(node, COLLECTION, "not a collection : %s",
                str_type(node->type));

    long size = collection_size(node);
    if(size <= 0)
        return NULL;

    char **str_res = malloc(size * sizeof(char *));
    ASSERT(str_res, "Error allocationg string array");

    for(long i = 0; i < size; i++)
    {
        Node *curr = collection_nth(node, i);

        // here we will print the node
        Node *value;
        if(curr->type & KEYVAL )
            value = string_keyval(curr, node->type & MAP);
        else
            value = PRINT(curr);
        str_res[i] = strdup(GET_STRING(value));
        unlink_node(value);
        unlink_node(curr);
    }
    return str_res;
}

static long list_size(long size, char *arr[])
{
    long res = 0;
    for(int i = 0; i < size; i++)
        res += strlen(arr[i]) + 1; // space
    return res + 1; // '\0'
}

/*
    Return string of all elements of coll in right order
*/
static String collection_get_inner_content(Node *node)
{
    ASSERT(node, "null pointer");
    ASSERT_TYPE(node, COLLECTION,
                "error stringing bad type : %s",
                str_type(node->type));

    bool rev = node->type & LIST; // LIST is growing from head
    long size = collection_size(node);
    char **str_res = get_array(node);
    if(!str_res)
        return strdup("");

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
}

/*
    Return String representation of coll
*/
static Node *string_collection(Node *coll)
{
    // get back inner content
    String inner_content = collection_get_inner_content(coll);
    Node *res;
    if(!inner_content)
        ABORT("Error getting inner content of collection");

    switch(log_type(coll->type))
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
            ABORT("string_coll : bad type for collection %s", coll->type);
    }
    free(inner_content);
    return res;
}

/*
    String representation of reader
    returns linked allocated String
*/
Node *string_reader(Node *node)
{
    ASSERT(node, "string_reader : null environment");
    ASSERT_TYPE(node, READER, "string_env : Bad type %s", str_type(node->type));
    return string_sprintf("<%s FILE*=?>",
//						   node->val.function->is_macro ? "yes" : "no",
//						   node->val.function->is_special ? "yes" : "no",
                           str_type(FUNCTION));
}

/*
    String representation of var
*/
Node *string_var(Node *node)
{
    ASSERT(node, "null var");
    ASSERT_TYPE(node, VAR, "Bad type %s", str_type(node->type));
    String sym = GET_ELEM_STRING(node, &var_symbol);
    Node *res = NULL;

    if(FALSE_Q_(var_bound_Q_(node)))
    {
        res = string_sprintf("<%s symbol*=%s unbound>", sym);
        free(sym);
    }
    else
    {
        String val = GET_ELEM_STRING(node, &var_value);
        res = string_sprintf("<%s symbol*=%s value=%s>", sym);
        free(val);
        free(sym);
    }

    return res;
}

/*
    String representation of environment
    returns linked allocated String
*/
static Node *string_env(Node *node)
{
    ASSERT(node, "null environment");
    ASSERT_TYPE(node, ENVIRONMENT, "Bad type %s", str_type(node->type));
    Node *map = env_map(node);
    if(map)
    {
        Node *map_str = PRINT(map);
        Node *res = string_sprintf("<%s map=%s>",
                                    str_type(ENVIRONMENT),
                                    GET_STRING(map_str));
        unlink_node(map_str);
        unlink_node(map);
        return res;
    }
    return string_sprintf("<%s map=null>", str_type(ENVIRONMENT));
}

/*
    String representation for functions
    returns linked allocated String
*/
static Node *string_function(Node *node)
{
    ASSERT(node, "null pointer");
    ASSERT_TYPE(node, CALLABLE, "Bad type %s", str_type(node->type));
    Node *res = NULL;
    String closure = GET_ELEM_STRING(node, &function_closure);
    String args = GET_ELEM_STRING(node, &function_args);

    if(node->type & LAMBDA)
    {
        String body = GET_ELEM_STRING(node, &function_body);
        res = string_sprintf("<%s macro=%s special=%s args=%s closure=%s body=%s>",
                                str_type(node->type),
                                TRUE_Q_(function_is_macro(node)) ? "yes" : "no",
                                TRUE_Q_(function_is_special(node)) ? "yes" : "no",
                                args, closure, body);
        free(body);
    }
    else
    {
        res = string_sprintf("<%s macro=%s special=%s args=%s closure=%s>",
                                str_type(node->type),
                                TRUE_Q_(function_is_macro(node)) ? "yes" : "no",
                                TRUE_Q_(function_is_special(node)) ? "yes" : "no",
                                args, closure);
    }

    free(args);
    free(closure);
    unlink_node(node);
    return res;
}

/*
    get interned name
*/
static String string_named_interned(Node *node)
{
    ASSERT_TYPE(node, NAMED, "node is not a symbol or keyword");
    Node *name = named_name(node);
    Node *ns = named_ns(node);

    Node *complete = NULL;
    if(FALSE_Q_(ns))
    {
        complete = name;
    }
    else
    {
        String ns_str = GET_STRING(ns);
        String name_str = GET_STRING(name);
        unlink_node(name);

        complete = string_sprintf("%s/%s", ns_str, name_str);
        free(ns_str);
        free(name_str);
    }
    unlink_node(ns);

    String compl_str = GET_STRING(complete);
    unlink_node(complete);

    return compl_str;
}


/*
    Return allocated string of symbol name according to type
*/
static Node *string_named_formated(Node *node)
{
    Node *formated = NULL;
    String compl_str = string_named_interned(node);
    switch(log_type(node->type))
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
    unlink_node(node);

    ASSERT(formated, "cannot format node");
    return formated;
}

/*
	print integer
*/
static Node *string_integer(Node *node)
{
	ASSERT_TYPE(node, INTEGER, "Node is not an integer");

	char *formated;
	asprintf(&formated, "%ld", number_integer(node));

	if(formated)
		return string(formated);

	free(formated);
	return string_allocate("NaN");
}

/*
	print decimal
*/
static Node *string_decimal(Node *node)
{
	ASSERT_TYPE(node, DECIMAL, "Node is not an decimal");

	char *formatted;
	asprintf(&formatted, "%lf", number_decimal(node));

	if(formatted)
		return string(formatted);

    free(formatted);
    return string_allocate("NaN");
}

/*
    Return allocated string node of string formatted according to type
*/
static Node *string_formated(Node *node)
{
    fprintf(stderr, "string_formatted = '%s'", node->val.compl);
    ASSERT_TYPE(node, STRING, "node is not a string");
    String str = GET_STRING(node);
    Node *formated = string_sprintf("\"%s\"",str);
    ASSERT(formated, "cannot format node");
    return formated; // formated allocated
}

/*
    return string version of nodes according to type
*/
Node *print_node(Node *node, bool readable)
{
    ASSERT(node, "string_node : NULL node");
    Node *res = NULL;
    switch(log_type(node->type))
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
                print_stack_trace();
                break;
            }
            else
            {
                // res will be node and node will be unlinked...
                res = link_node(node);

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

    unlink_node(node);
    return res;
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
        writer_curr(writer_stderr());
    writer_print(print(node));
    return nil;
}

/*
    PR node using pointer, non readable
*/
Node *PR(Node *node)
{
    if(!curr)
        writer_curr(writer_stderr());
    writer_print(pr(node));
    return nil;
}

/*
    PRINT node using pointer readable
*/
Node *PRINTLN(Node *node)
{
    if(!curr)
        writer_curr(writer_stderr());
    writer_print(print(node));
    writer_nl();
    return nil;
}

/*
    PR node using pointer, non readable
*/
Node *PRN(Node *node)
{
    if(!curr)
        writer_curr(writer_stderr());
    writer_print(pr(node));
    writer_nl();
    return nil;
}

