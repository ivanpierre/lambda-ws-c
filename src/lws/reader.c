/****
	General reader to create objects

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"

/*
	Unalloc reader
*/
Node *reader_free(Node *node)
{
	ASSERT(node, ERR_NODE);
	ASSERT_TYPE(node, IREADER);
	free(node);
	error_assert:
	return NULL;
}
