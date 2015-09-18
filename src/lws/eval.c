/****
	General evaluator of nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
#include "named.h"
#include "collection.h"
#include "keyval.h"
#include "strings.h"
#include "writer.h"

/*
	return evaluation of nodes according to type
*/
Node *eval_node(Node *node, Node *environment)
{
	Node *res = NULL;

	switch(node->type->int_type)
	{
		case ISYMBOL :
			res = symbol_eval(node, environment);
			break;

		case ILIST :
		case ISEQ :
			res = list_eval(node, environment);
			break;

		case IARRAY :
		case IMAP :
		case ISET :
			res = collection_eval(node, environment);
			break;

		case IKEYVAL :
			res = keyval_eval(node, environment);
			break;

		case INIL :
		case ITRUE :
		case IFALSE :
		case IKEYWORD :
		case IINTEGER :
//		case IFRACTION :
		case IDECIMAL :
		case ISTRING :
		case IENV_STACK :
		case IENVIRONMENT :
		case IAPI :
		case IFUNCTION :
		case ILAMBDA :
		case IVAR :
		case IREF :
		case IREADER :
		case INAMESPACE :
			ASSIGN(res, node);
			break;

		case IINVALID :
		default:
			ABORT("cannot evaluate '%s' of type '%s'",
				  pr(node), node->type->str_type);
			break;
	}

	//************
	error_assert:
	return res;
}

/*
 * Evaluation function pointer
 */
Node *(*eval_ptr)(Node *node, Node *environment) = &eval_node;

/*
 * evaluation function
 */
Node *EVAL(Node *node, Node *environment)
{
	Node *res = NULL;

	ASSERT_NODE(node, ICOLLECTION);
	ASSERT_NODE(environment, ICOLLECTION);

	res = (*eval_ptr)(node, environment);

	unlink_node(node);
	unlink_node(environment);
	return res;

	//************
	error_assert:
	unlink_node(node);
	unlink_node(environment);
	unlink_node(res);
	return res;
}
