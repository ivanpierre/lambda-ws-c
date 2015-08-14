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
#include "string.h"
#include "env.h"

/*
    Return String representation a KEYVAL
*/
static Node *string_keyval(Node *node, bool map)
{
    ASSERT(node, "null pointer");
    ASSERT_TYPE(node, KEYVAL, "error printing bad type : %s",
                str_type(node->type));
    Node *res;
    String k = get_string(node, &keyval_key);
    String v = get_string(node, &keyval_value);
    if(map)
        res = string_sprintf("%s %s", k, v);
    else
        res = string_sprintf("[%s %s]", k, v);
    free(v);
    free(k);
    unlink_node(node);
    ASSERT(str_node, "Error printing keyval");
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

    long size = size_coll(node);
    if(size <= 0)
        return NULL;

    char **str_res = malloc(size * sizeof(char *));
    ASSERT(str_res, "Error allocationg string array");

    for(long i = 0; i < size; i++)
    {
        Node *curr = nth(node, i);

        // here we will print the node
        Node *value;
        if(curr->type & KEYVAL )
            value = string_keyval(curr, node->type & MAP);
        else
            value = PRINT(curr);
        str_res[i] = strdup(STRING(value));
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
static String get_inner_content_coll(Node *node)
{
    ASSERT(node, "null pointer");
    ASSERT_TYPE(node, COLLECTION,
                "error stringing bad type : %s",
                str_type(node->type));

    bool rev = node->type & LIST; // LIST is growing from head
    long size = size_coll(node);
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
static Node *collection_string(Node *coll)
{
    // get back inner content
    String inner_content = get_inner_content_coll(coll);
    Node *res;
    if(!inner_content)
        ABORT("Error getting inner content of collection");

    switch(coll->type)
    {
        case LIST:
            res = string_sprintf("(%s)", inner_content);
            break;

        case ARRAY:
            res = string_sprintf("[%s]", inner_content);
            break;

        case SET:
            res = string_sprintf("#{%s}", inner_content);
            break;

        case MAP:
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
    String representation of environment
    returns linked allocated String
*/
static Node *env_string(Node *node)
{
    ASSERT(node, "null environment");
    ASSERT_TYPE(node, ENVIRONMENT, "Bad type %s", str_type(node->type));
    Node *map = env_map(node);
    if(map)
    {
        Node *map_str = PRINT(map);
        Node *res = string_sprintf("<%s map=%s>",
                                    str_type(ENVIRONMENT),
                                    STRING(map_str));
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
static Node *function_string(Node *node)
{
    ASSERT(node, "string_function : null environment");
    ASSERT_TYPE(node, FUNCTION, "string_function : Bad type %s", str_type(node->type));
    Node *map = string(node->val.function->closure);
    Node *args = string(node->val.function->args);
//	Node *body = string(node->val.function->func.body);
    Node *res = string_sprintf("<%s macro=%s special=%s args=%s closure=%s>",
                                node->type,
                                node->val.function->is_macro ? "yes" : "no",
                                node->val.function->is_special ? "yes" : "no",
                                args->val.string,
                                map->val.string);
    unlink_node(map);
    return res;
}

/*
    Return allocated string of symbol name according to type
*/
static String symbol_string_formated(Node *s)
{
    ASSERT_TYPE(s, SYMBOL|KEYWORD, "get_string : node is not a string, symbol or keyword");
    String formated = NULL;
    switch(s->type)
    {
        case KEYWORD :
            asprintf(&formated, ":%s", (s->val.string));
            break;
        case SYMBOL :
            asprintf(&formated, "%s", (s->val.string));
            break;
        default :
            break;
    }
    ASSERT(formated, "get_formated_string : cannot format node");
    return formated;
}

/*
	print integer
*/
static Node *integer_string(Node *node)
{
	ASSERT_TYPE(node, INTEGER, "print_integer : Node is not an integer\n");

	char *formated;
	asprintf(&formated, "%ld", get_integer(node));

	if(formated)
		return new_string(formated);

	free(formated);
	return new_string_allocate("NaN");
}

/*
	print decimal
*/
static Node *decimal_string(Node *node)
{
	char *formatted;
	asprintf(&formatted, "%lf", get_decimal(node));

	if(formatted)
		return new_string(formatted);
	else
	{
		free(formatted);
		return new_string_allocate("NaN");
	}
}

/*
    Return allocated string node of string formatted according to type
*/
static Node *string_string_formated(Node *node)
{
    ASSERT_TYPE(node, STRING, "string_string : node is not a string");
    String formated = get_formated_string(node);
    ASSERT(formated, "string_string : cannot format node");
    return new_string(formated); // formated allocated
}

/*
    return string version of nodes according to type
*/
Node *print_node(Node *node)
{
    ASSERT(node, "string_node : NULL node");

    switch(node->type)
    {
        case NIL_NODE :
            return string_sprintf("nil");

        case TRUE_NODE :
            return string_sprintf("true");

        case FALSE_NODE :
            return string_sprintf("false");

        case KEYWORD :
        case SYMBOL :
        case STRING :
            return string_string(node);

        case LIST :
        case ARRAY :
        case MAP :
        case SET :
        case ENV_STACK :
        case ENVIRONMENT :
            return string_coll(node);

        case KEYVAL :
            return string_keyval(node, false);

        case FUNCTION :
        case LAMBDA :
            return string_function(node);

        case VAR :
//    	case REF :
//    	case FUTURE :
            return string(node->val.atom);

        case READER :
            return string_reader(node);

        case INTEGER :
            return string_integer(node);

        case DECIMAL :
            return string_decimal(node);

        default :
            break;
    }

    free(node);
    return NULL;
}

/*
    def pointer for print
*/
Node *(*print_ptr)(Node *node) = &print_node;

/*
    PRINT node using pointer
*/
static Node *PRINT(Node *node)
{
    return (*print_ptr)(node);
}

