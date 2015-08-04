/****
	colls sets and maps

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"

/*
	Free coll
*/
Node *free_coll(Node *node)
{
	ASSERT_TYPE(node, LIST | ARRAY | MAP | SET,
				"free_coll : error unallocatig bad type : %s",
				str_type(node->type));

	long size = size_coll(node);
	if(size <= 0)
		return NULL;

	for(long i = 0; i < size; i++)
	{
		if(node->val.coll->nodes[i])
		{
			free_node(node->val.coll->nodes[i]);
			node->val.coll->nodes[i] = NULL;
		}
	}
	return NULL;
}

/*
	Size of coll
*/
long size_coll(Node *node)
{
	if(!(node && (node->type & (LIST | ARRAY | MAP | SET))))
	{
		ERROR("size_coll : get size of bad type : %s", str_type(node->type));
		return -1;
	}
	if(!node->val.coll)
	{
		ERROR("size_coll : not allocated coll");
		return -1;
	}
	return node->val.coll->size;
}

/*
	Return array of string representation of element of coll
*/
static char **get_array(Node *node)
{
	long size = size_coll(node);
	if(size <= 0)
		return NULL;

	char **str_res = malloc(size * sizeof(char *));

	for(long i = 0; i < size; i++)
	{
		Node *curr = node->val.coll->nodes[i];
		Node *str_node;
		if(curr->type & KEYVAL && node->type & MAP)
		{
			// here we will peint he key / value pair
			Node *key = string_node(curr->val.keyval->key);
			Node *value = string_node(curr->val.keyval->value);
			str_node = sprintf_string("%s %s", key->val.string, value->val.string);
		}
		else
		{
			// here we will print the node
			Node *value = string_node(curr);
			str_node = sprintf_string("%s", value->val.string);
		}
		str_res[i] = strdup(str_node->val.string);
		unlink_node(str_node);
	}
	return str_res;
}

/*
	return total sring size of string representation of inner string
*/
static long list_size(long size, char **strings)
{
	long res = 0;
	for(long i = 0; i < size; i++)
		res += strlen(strings[i]) + 1; // counting space
	return res + 1; // for \0
}

/*
	Return string of all elements of coll in right order
*/
static String string_coll_elements(Node *node)
{
	long size = size_coll(node);
	char **str_res = get_array(node);
	if(!str_res)
		return strdup("");

	long str_size = list_size(size, str_res);
	char *string_res = malloc(sizeof(char) * str_size);
	string_res[0] = '\0';
	for(long i = 0; i < size; i++)
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
	Return string of all elements of coll in reverse order
*/
static String string_coll_elements_reverse(Node *node)
{
	long size = size_coll(node);
	char **str_res = get_array(node);
	if(!str_res)
		return strdup("");

	long str_size = list_size(size, str_res);
	char *string_res = malloc(sizeof(char) * str_size);
	string_res[0] = '\0';
	for(long i = size - 1; i >= 0; i--)
	{
		strcat(string_res, str_res[i]);
		if(i < size - 1)
			strcat(string_res, " ");
		free(str_res[i]); // free each allocated string
	}

	free(str_res); // free string array
	return string_res;
}

/*
	Return String representation a KEYVAL
*/
Node *string_keyval(Node *node)
{
	ASSERT(node, "string_keyval : null pointer");
	ASSERT_TYPE(node, KEYVAL,
				"string_keyval : error printing bad type : %s",
				str_type(node->type));
	Node *key = string_node(node->val.keyval->key);
	Node *value = string_node(node->val.keyval->value);
	Node *str_node = sprintf_string("[%s %s]", key->val.string, value->val.string);
	unlink_node(key);
	unlink_node(value);
	ASSERT(str_node, "string_keyval : Error printing keyval");
	return str_node;
}

/*
	Free keyval
*/
Node *free_keyval(Node *node)
{
	ASSERT_TYPE(node, KEYVAL,
				"free_keyval : error unallocatig bad type : %s",
				str_type(node->type));

	free_node(node->val.keyval->key);
	free_node(node->val.keyval->value);
	return NULL;
}

/*
	get inner conttent of collection as a string
*/
String get_inner_content_coll(Node *coll)
{
	ASSERT(coll, "get_inner_content_coll : null pointer");
	ASSERT_TYPE(coll, LIST | ARRAY | MAP | SET,
				"get_inner_content_coll : error stringing bad type : %s",
				str_type(coll->type));

	// get back inner content
	if(coll->type & LIST)
		return string_coll_elements_reverse(coll);
	else
		return string_coll_elements(coll);
}

/*
	Return String representation of coll
*/
Node *string_coll(Node *coll)
{
	// get back inner content
	String inner_content = get_inner_content_coll(coll);
	Node *res;
	if(!inner_content)
		ABORT("string_coll : Error getting inner content of collection");

	switch(coll->type)
	{
		case LIST:
			res = sprintf_string("(%s)", inner_content);
			break;

		case ARRAY:
			res = sprintf_string("[%s]", inner_content);
			break;

		case SET:
			res = sprintf_string("#{%s}", inner_content);
			break;

		case MAP:
			res = sprintf_string("{%s}", inner_content);
			break;

		default :
			free(inner_content);
			ABORT("string_coll : bad type for collection %s", coll->type);
	}
	free(inner_content);
	return res;
}

/*
	Get first element of coll or nil, nil gives nil
*/
Node *first_coll(Node *coll)
{
	ASSERT(coll, "first_coll : null pointer");
	ASSERT_TYPE(coll, LIST | ARRAY | MAP | SET | NIL_NODE,
				"first_coll : not a coll %s", str_type(coll->type));
	if(coll->type & NIL_NODE ||
	   coll->val.coll->size == 0)
		return nil_node;
	if(coll->type & LIST)
		return link_node(coll->val.coll->nodes[coll->val.coll->size - 1]);
	else
		return link_node(coll->val.coll->nodes[0]);
}

/*
	Get last element of coll or nil, nil gives nil
*/
Node *last_coll(Node *coll)
{
	ASSERT(coll, "last_coll : null pointer");
	ASSERT_TYPE(coll, LIST | ARRAY | MAP | SET | NIL_NODE,
				"last_coll : not a coll %s", str_type(coll->type));
	if(coll->type & NIL_NODE ||
	   coll->val.coll->size == 0)
		return nil_node;
	if(coll->type & LIST)
		return link_node(coll->val.coll->nodes[0]);
	else
		return link_node(coll->val.coll->nodes[coll->val.coll->size - 1]);
}

/*
	Get nth element of coll or nil, nil gives nil
*/
Node *nth(Node *coll, long index)
{
	ASSERT(coll, "nth_coll : null pointer");
	ASSERT_TYPE(coll, LIST | ARRAY | MAP | SET | NIL_NODE,
				"nth_coll : not a coll %s", str_type(coll->type));
	ASSERT(index < coll->val.coll->size || index < 0,
			"nth_coll : Index out of bound");
	if(coll->type & NIL_NODE ||
	   coll->val.coll->size == 0)
		return nil_node;
	if(coll->type & LIST)
		return link_node(coll->val.coll->nodes[coll->val.coll->size - index - 1]);
	else
		return link_node(coll->val.coll->nodes[index]);
}

/*
	Allocate nodes
*/
Node *malloc_coll(Node *coll, long size)
{
	ASSERT(coll, "malloc_coll : null pointer");
	ASSERT_TYPE(coll, LIST | ARRAY | MAP | SET,
				"alloc_coll : bad type %s",
				str_type(coll->type));
	ASSERT(size >= 0, "alloc_coll : Allocation cannot be negative %ld", size);
	coll->val.coll->nodes = malloc(sizeof(Node *) * size);
	ASSERT(coll->val.coll->nodes, "malloc_coll : Error alocating collection nodes");
	coll->val.coll->max = size;
	return coll;
}

/*
	Reallocate nodes
*/
Node *realloc_coll(Node *coll, long size)
{
	ASSERT(coll, "realloc_coll : null pointer");
	ASSERT_TYPE(coll, LIST | ARRAY | MAP | SET,
				"realloc_coll : bad type %s",
				str_type(coll->type));
	ASSERT(size >= 0, "realloc_coll : Allocation cannot be negative %ld", size);
	coll->val.coll->nodes = realloc(coll, sizeof(Node *) * size);
	ASSERT(coll->val.coll->nodes, "realloc_coll : Error alocating collection nodes");
	coll->val.coll->max = size;
	return coll;
}

/*
	create a new empty collection
*/
Node *new_empty_coll(NodeType type,  long alloc)
{
	ASSERT(type & (LIST | ARRAY | MAP | SET), "new_empty_coll : bad type %s", str_type(type));
	Node *coll = new_node(type);
	ASSERT(coll, "new_empty_coll : Error alocating collection node");
	if(malloc_coll(coll, alloc))
	{
		coll->val.coll->max = coll->val.coll->size = 0;
		unlink_node(coll);
		return NULL;
	}
	coll->val.coll->size = 0;
	return coll;
}

/*
Node        *reduce_coll(Node *init, Node *(*fn)(Node *arg1, Node *arg2), Node *coll);
Node        *filter_coll(Node *(*fn)(Node *node), Node *coll);
Node        *map_coll(Node *(*fn)(Node *node), Node *coll);
Node        *map2_coll(Node *(*fn)(Node *node1, Node *node2), Node *coll1, Node *coll2);
Node        *alloc_clone_coll(Node *coll, long diff);
Node        *assoc_coll(Node *map, Node *keyval);
Node        *dissoc_coll(Node *map, Node *keyval);
Node        *push(Node *coll, Node *elem);
Node        *pop(Node *coll);
Node        *sort(Node coll);
Node        *new_keyval(Node *key, Node *value);
long        pos_coll(Node *coll, Node *search);
*/
