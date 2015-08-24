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
    ASSERT(node, "eval_node : NULL node");

    Node *res = NULL;

    switch(node->type)
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
            return node;

        case IINVALID :
        default:
            ERROR("cannot evaluate '%s' of type '%s'", GET_STRING(pr(node)), str_type(node->type));
            break;
    }
    unlink_node(node);
    return res;
}

