/****
	Seq : sequence on a collection

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "seq.h"
#include "collection.h"

/*
	Constructor
*/
Node *seq(long index, Node *coll)
{
	Node *new_coll = NULL;
	Seq *seq = NULL;

	// loop across seq if we make a seq from a seq until we find a collection
	while(coll->type->int_type == ISEQ)
	{
		/*
			We will manage the CONS, BUNDLE, etc. types
		*/
		switch(coll->type->int_type)
		{
			case ISEQ:
				seq = STRUCT(coll);
				link_node(&new_coll, seq->coll);
				index += seq->index;
				link_node(&coll, new_coll);
				unlink_node(&new_coll);
		        break;

			default:
				break;
		}
	}

	// (seq ()) => nil
	Collection *collection = STRUCT(coll);
	index = collection->size - index;
	if(index <= 0)
	{
		unlink_node(&coll);
		return NIL;
	}

	// create seq
	Node *node = new_node(ISEQ);
	ASSERT(node, "Creation of new seq", str_type(ISEQ));

	seq = STRUCT(node);
	seq->index = index;
	link_node(&seq->coll, coll);
	unlink_node(&coll);
	return node;

	// ******************
	error_assert:
	unlink_node(&coll);
	unlink_node(&new_coll);
	unlink_node(&node);
	return NULL;
}

/*
	length of the sequence
*/
long seq_size(Node *node)
{
	Node *tmp_node = NULL;
	ASSERT_NODE(node, tmp_node, ISEQ);

	Seq *seq = STRUCT(tmp_node);
	Collection *coll = STRUCT(seq->coll);
	long coll_size = coll->size - seq->index;

	unlink_node(&tmp_node);
	return coll_size;

	//**********************
	error_assert:
	unlink_node(&node);
	unlink_node(&tmp_node);
	return -1;
}

/*
	Get index
*/
long seq_index(Node *node)
{
	Node *tmp_node = NULL;
	ASSERT_NODE(node, tmp_node, ISEQ);
	Seq *seq = STRUCT(tmp_node);
	return seq->index;

	// ****************
	error_assert:
	unlink_node(&node);
	return -1;
}

/*
	Get collection
*/
Node *seq_coll(Node *node)
{
	ASSERT(node, "Seq null");
	Seq *seq = STRUCT(node);
	Node *res = NULL;

	link_node(&res, seq->coll);
	unlink_node(&node);
	return res;

	// ***********
	error_assert:
	unlink_node(&node);
	return NULL;
}

/*
	Free sequence
*/
Node *seq_free(Node *node)
{
	Seq *seq = STRUCT(node);
	unlink_node(&seq->coll);
	free(node);
	return NULL;
}
