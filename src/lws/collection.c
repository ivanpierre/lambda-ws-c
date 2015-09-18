/****
	Collections List, array, set and map

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "nodes.h"
#include "number.h"
#include "collection.h"
#include "function.h"
#include "writer.h"
#include "eval.h"
#include "free_internal.h"

/*
	create a new empty collection
	We will alloc one more block to put a NULL for usage with varargs
*/
static Node *collection(TYPE type, bool mut)
{
	TRACE("collection...");
	// Create node base
	Node *node = new_node(type);
	ASSERT(node, ERR_INIT, str_type(type));

	// Get collection
	Collection *coll = STRUCT(node);
	ASSERT(coll, ERR_ALLOC);

	// init collection nodes
	coll->mut   = mut;
	coll->size  = 0;
	coll->max   = 0;
	coll->nodes = malloc(sizeof(Node *));
	coll->nodes[0] = NULL;

	TRACE("collection return...");
	return node;

	//************
	error_assert:
	unlink_node(&node);
	return NULL;
}

/*
 * empty_list
 */
Node *empty_list()
{
	return collection(ILIST, BOOL_FALSE);
}

/*
 * empty_mutable_list
 */
Node *empty_transient_list()
{
	return collection(ILIST, BOOL_TRUE);
}

/*
 * empty_array
 */
Node *empty_array()
{
	return collection(IARRAY, BOOL_FALSE);
}

/*
 * empty_mutable_array
 */
Node *empty_transient_array()
{
	return collection(IARRAY, BOOL_TRUE);
}

/*
 * empty_map
 */
Node *empty_map()
{
	return collection(IMAP, BOOL_FALSE);
}

/*
 * empty_mutable_map
 */
Node *empty_transient_map()
{
	return collection(IMAP, BOOL_TRUE);
}

/*
 * empty_set
 */
Node *empty_set()
{
	return collection(ISET, BOOL_FALSE);
}

/*
 * empty_mutable_set
 */
Node *empty_transient_set()
{
	return collection(ISET, BOOL_TRUE);
}

/*
Reallocate nodes
We will alloc one more block to put a NULL for usage with varargs
*/
static Node *collection_realloc(Node *node, long size)
{
	ASSERT(node, ERR_NODE);
	ASSERT_TYPE(node, ICOLLECTION);
	ASSERT(size >= 0, ERR_NEG_ALLOC, size);

	Collection *coll = STRUCT(node);

	// unalloc nodes if collection shrinks
	if (size < coll->size)
	{
		for (long i = size; i < coll->size; i++)
			if (coll->nodes[i])
				unlink_node(&coll->nodes[i]);
		coll->size = size;
	}
	coll->max        = size;
	coll->nodes      = realloc(coll->nodes, sizeof(Node *) * size + 1);
	ASSERT(coll->nodes, ERR_ALLOC);
	coll->nodes[coll->size] = NULL; // NULL at end of array
	return node;

	//************
	error_assert:
	return NULL;
}

/*
Free coll
*/
Node *collection_free(Node **node)
{
	ASSERT_TYPE(*node, ICOLLECTION);

	Collection *coll = STRUCT(*node);
	long       size  = coll->size;

	for (long i = 0; i < size; i++)
		if (coll->nodes[i])
			unlink_node(&coll->nodes[i]);

	free(*node);
	*node = NULL;
	return NULL;

	//************
	error_assert:
	return NULL;
}

/*
	Mutable coll
*/
Node *collection_mut_Q_(Node *node)
{
	if(node->type->int_type == INIL)
		return FALSE;
	ACCESS_BOOL(Collection, mut, ICOLLECTION);
}

bool COLLECTION_MUT_Q_(Node *node)
{
	if(node->type->int_type == INIL)
		return BOOL_FALSE;
	Collection *coll = STRUCT(node);
	return coll->mut;
}

/*
	Size of coll
*/
Node *collection_count(Node *node)
{
	if(node->type->int_type == INIL)
		return integer(0);
	ACCESS_INTEGER(Collection, size, ICOLLECTION);
}

long COLLECTION_COUNT(Node *node)
{
	if(node->type->int_type == INIL)
		return 0l;
	Collection *coll = STRUCT(node);
	return coll->size;
}

/*
	Max allocation of coll
*/
Node *collection_max(Node *node)
{
	if(node->type->int_type == INIL)
		return integer(0);
	ACCESS_INTEGER(Collection, max, ICOLLECTION);
}

long COLLECTION_MAX(Node *node)
{
	if(node->type->int_type == INIL)
		return 0l;
	Collection *coll = STRUCT(node);
	return coll->max;
}

/*
	Get first element of coll or nil, nil gives nil
*/
Node *collection_first(Node *node)
{
	Node *tmpnode = NULL;
	Node *res  = NULL;
	ASSERT_NODE(node, tmpnode, ISEQUABLE);
	if(node->type->int_type == INIL)
	{
		res = NIL;
		goto end_assert;
	}

	Collection *coll = STRUCT(node);
	if (tmpnode->type->int_type == INIL || coll->size <= 0)
		res = NIL;
	else if (tmpnode->type->int_type == ILIST)
		res = coll->nodes[coll->size - 1];
	else
		res = coll->nodes[0];

	unlink_node(&tmpnode);
	return res;

	//******************
	end_assert:
	error_assert:
	unlink_node(&tmpnode);
	unlink_node(&res);
	return res;
}

/*
	Get last element of coll or nil, nil gives nil
*/
Node *collection_last(Node *node)
{
	Node *tmpnode = NULL;
	Node *res  = NULL;
	ASSERT_NODE(node, tmpnode, ISEQUABLE);
	if(node->type->int_type == INIL)
	{
		res = NIL;
		goto end_assert;
	}

	Collection *coll = STRUCT(node);
	if (tmpnode->type->int_type == INIL || coll->size <= 0)
		res = NIL;
	else if (tmpnode->type->int_type == ILIST)
		res = coll->nodes[0];
	else
		res = coll->nodes[coll->size - 1];

	unlink_node(&tmpnode);
	return res;

	//****************
	end_assert:
	error_assert:
	unlink_node(&tmpnode);
	unlink_node(&res);
	return res;
}

/*
	Get nth element of coll or nil, nil gives nil
*/
Node *collection_nth(Node *node, Node *index)
{
	Node *tmpnode = NULL;
	Node *res  = NULL;
	ASSERT_NODE(node, tmpnode, ISEQUABLE);
	if(node->type->int_type == INIL)
	{
		res = NIL;
		goto end_assert;
	}

	// Manage index arg
	Node *tmpindex = NULL;
	ASSERT_NODE(index, tmpindex, IINTEGER);
	Integer *i = STRUCT(tmpindex);
	ASSERT(i, ERR_ARG, "index");
	long idx = i->integer;
	unlink_node(&tmpindex);

	Collection *coll = STRUCT(node);
	if (tmpnode->type->int_type == INIL)
		res = NIL;
	else if (coll->size == 0 || (idx >= coll->size && idx < 0))
		ABORT(ERR_INDEX, idx);

	if (tmpnode->type->int_type == ILIST)
		res = coll->nodes[coll->size - idx - 1];
	else
		res = coll->nodes[idx];

	unlink_node(&tmpnode);
	return res;

	//********************
	end_assert:
	error_assert:
	unlink_node(&tmpnode);
	unlink_node(&tmpindex);
	unlink_node(&res);
	return res;
}

/*
 * list function
 */
Node *list(Node *arg, ...)
{
	va_list args, save;
	Node *node = empty_list();

	if(arg == NULL)
		return node;

	va_copy(save, args);
	va_start(save, arg);

	long count = count_args(save);
	Collection *coll = STRUCT(node);
	node = collection_realloc(node, count + 1);
	link_node(&coll->nodes[count], arg);
	TRACE("Last element = '%s'", print(arg));

	va_start(args, arg);
	Node *walk = va_arg(args, Node *);
	for(long i = count - 1; walk; i--)
	{
		coll->nodes[i] = NULL;
		link_node(&coll->nodes[i], walk);
		TRACE("Element #%ld = '%s'", i, print(coll->nodes[i]));
		walk = va_arg(args, Node *);
	}
	coll->size = count + 1;
	va_end(args);
	return node;
}

/*
 *
 */
Node *array(Node *arg, ...)
{
	va_list args, save;
	Node *node = empty_array();

	if(arg == NULL)
		return node;

	va_copy(save, args);
	va_start(save, arg);

	long count = count_args(save);
	Collection *coll = STRUCT(node);
	node = collection_realloc(node, count + 1);
	link_node(&coll->nodes[0], arg);
	TRACE("First element = '%s'", print(arg));

	va_start(args, arg);
	Node *walk = va_arg(args, Node *);
	for(long i = 1; walk; i++)
	{
		coll->nodes[i] = NULL;
		link_node(&coll->nodes[i], walk);
		TRACE("Element #%ld = '%s'", i, print(coll->nodes[i]));
		walk = va_arg(args, Node *);
	}
	coll->size = count + 1;
	va_end(args);
	return node;
}

/*
 *
 */
Node *set(Node *arg, ...)
{
	return NIL;
}

/*
 *
 */
Node *map(Node *arg, ...)
{
	return NIL;
}

/*
	Evaluation of lists
*/
Node *list_eval(Node *node, Node *environment)
{
	// TODO implement evaluation
	return node;
}

/*
	Evaluation of other collections
*/
Node *collection_eval(Node *node, Node *environment)
{
	Node *tmp_node = NULL;
	Node *tmp_environment = NULL;
	ASSERT_NODE(node, tmp_node, ICOLLECTION);
	ASSERT_NODE(environment, tmp_environment, ICOLLECTION);
	Collection *org = STRUCT(tmp_node);
	Node *res = NULL;
	res = collection_realloc(new_node(tmp_node->type->int_type), org->size);

	Collection *dest = STRUCT(res);
	dest->mut = org->mut;
	for(long i = 0; i < org->size; i++)
	{
		link_node(&dest->nodes[i], EVAL(org->nodes[i], environment));
	}

	unlink_node(&tmp_node);
	unlink_node(&tmp_environment);
	return res;

	//********************
	end_assert:
	error_assert:
	unlink_node(&tmp_node);
	unlink_node(&tmp_environment);
	unlink_node(&res);
	return res;
}
