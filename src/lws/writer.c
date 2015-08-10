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

/*
    Return String representation a KEYVAL
*/
static Node *string_keyval(Node *node, bool map)
{
    ASSERT(node, "null pointer");
    ASSERT_TYPE(node, KEYVAL, "error printing bad type : %s",
                str_type(node->type));
    Node *str_node;
    Node *key = keyval_key(node);
    Node *value = keyval_value(node);
    Node *key_str = PRINT(key);
    Node *value_str = PRINT(value);
    if(map)
        str_node = string_sprintf("%s %s", STRING(key_str), STRING(value_str));
    else
        str_node = string_sprintf("[%s %s]", STRING(key_str), STRING(value_str));
    unlink_node(value_str);
    unlink_node(key_str);
    unlink_node(value);
    unlink_node(key);
    unlink_node(node);
    ASSERT(str_node, "Error printing keyval");
    return str_node;
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
static String string_coll_elements(Node *node)
{
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
    get inner conttent of collection as a string
*/
static String get_inner_content_coll(Node *coll)
{
    ASSERT(coll, "get_inner_content_coll : null pointer");
    ASSERT_TYPE(coll, LIST | ARRAY | MAP | SET,
                "get_inner_content_coll : error stringing bad type : %s",
                str_type(coll->type));

    // get back inner content
    return string_coll_elements(coll);
}

/*
    Return String representation of coll
*/
static Node *string_coll(Node *coll)
{
    // get back inner content
    String inner_content = get_inner_content_coll(coll);
    Node *res;
    if(!inner_content)
        ABORT("string_coll : Error getting inner content of collection");

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
static Node *string_env(Node *node)
{
    ASSERT(node, "string_env : null environment");
    ASSERT_TYPE(node, ENVIRONMENT, "string_env : Bad type %s", str_type(node->type));
    if(node->val.env->map)
    {
        Node *map = string(node->val.env->map);
        Node *res = string_sprintf("<%s map=%s>",
                                    str_type(ENVIRONMENT),
                                    map->val.string);
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
static String get_formated_symbol(Node *s)
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
static Node *string_integer(Node *node)
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
static Node *string_decimal(Node *node)
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
static Node *string_string(Node *node)
{
    ASSERT_TYPE(node, STRING|SYMBOL|KEYWORD, "string_string : node is not a string, symbol or keyword");
    String formated = get_formated_string(node);
    ASSERT(formated, "string_string : cannot format node");
    return new_string(formated); // formated allocated
}

/*
    return string version of nodes according to type
*/
Node *string(Node *node)
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
