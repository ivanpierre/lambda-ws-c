/****
	Collections List, array, set and map

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "number.h"
#include "collection.h"

/*
	create a new empty collection
	We will alloc one more block to put a NULL for usage with varargs
*/
static Node *collection(TYPE type, bool mut)
{
	// Create node base
	TRACE("Creating %s", str_type(type));
	Node *node = new_node(type);
	ASSERT(node, ERR_INIT, str_type(type));

	// Get collection
	Collection *coll = STRUCT(node);
	ASSERT(coll, ERR_ALLOC);

	// init collection nodes
	TRACE("Allocating %s", str_type(type));
	coll->mut   = mut;
	coll->size  = 0;
	coll->max   = 0;
	coll->nodes = malloc(sizeof(Node *));
	coll->nodes[0] = NULL;
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
Node *collection_realloc(Node *node, long size)
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
	unlink_node(&node);
	return NULL;
}

/*
Free coll
*/
Node *collection_free(Node **node)
{
	ASSERT_TYPE(*node, ICOLLECTION);

	Collection *coll = GET_COLLECTION(*node);
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
	ACCESS_BOOL(Collection, mut, ICollection);
}

/*
Size of coll
*/
Node *collection_size(Node *node)
{
	ACCESS_BOOL(Collection, size, ICollection);
}

/*
Max allocation of coll
*/
Node *collection_max(Node *node)
{
	ACCESS_BOOL(Collection, max, ICollection);
}

/*
	Get first element of coll or nil, nil gives nil
*/
Node *collection_first(Node *node)
{
	Collection *coll = STRUCT(node);
	Node *tmpnode = NULL;
	Node       *res  = NULL;

	ASSERT_NODE(node, tmpnode, ISEQUABLE);

	if (tmpnode->type->int_type == INIL || coll->size <= 0)
		res = NIL;
	else if (tmpnode->type->int_type == ILIST)
		link_node(&res, coll->nodes[coll->size - 1]);
	else
		link_node(&res, coll->nodes[0]);
	return res;

	error_assert:
	unlink_node(&tmpnode);
	unlink_node(&node);
	return NULL;
}

/*
	Get last element of coll or nil, nil gives nil
*/
Node *collection_last(Node *node)
{
	Collection *coll = STRUCT(node);
	Node *tmpnode = NULL;
	Node       *res  = NULL;

	ASSERT_NODE(node, tmpnode, ISEQUABLE);

	if (tmpnode->type->int_type == INIL || coll->size <= 0)
		res = NIL;
	else if (tmpnode->type->int_type == ILIST)
		link_node(&res, coll->nodes[0]);
	else
		link_node(&res, coll->nodes[coll->size - 1]);

	return res;

	error_assert:
	unlink_node(&tmpnode);
	unlink_node(&node);
	return NULL;
}

/*
	Get nth element of coll or nil, nil gives nil
*/
Node *collection_nth(Node *node, Node *index)
{
	// managenode node arg
	ASSERT_TYPE(node, ISEQUABLE);

	// Manage index arg
	ASSERT_TYPE(index, IINTEGER);
	Integer *i = STRUCT(index);
	ASSERT(i, ERR_ARG, "index");
	long idx = i->integer;

	// get indexed value
	Node       *res  = NULL;
	Collection *coll = STRUCT(node);
	if (node->type->int_type == INIL)
		res = NIL;
	else if (coll->size == 0 || (idx >= coll->size && idx < 0))
	ABORT(ERR_INDEX, idx);
	if (node->type->int_type == ILIST)
		link_node(&res, coll->nodes[coll->size - idx - 1]);
	else
		link_node(&res, coll->nodes[idx]);

	//*************
	error_assert:
	unlink_node(&node);
	unlink_node(&index);
	return res;
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
	// TODO implement evaluation
	return node;
}
