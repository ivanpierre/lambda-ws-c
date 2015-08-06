/****
    General evaluator of nodes

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"

/*
    return evaluation of nodes according to type
*/
Node *eval_node(Node *node, Node *env)
{
    ASSERT(node, "eval_node : NULL node");

    switch(node->type)
    {
        case SYMBOL :
            return eval_symbol(node, env);

        case LIST :
        case SEQ :
            return eval_list(node, env);

        case ARRAY :
        case MAP :
        case SET :
            return eval_coll(node, env);

        case KEYVAL :
            return eval_keyval(node, env);


        case NIL_NODE :
        case TRUE_NODE :
        case FALSE_NODE :
        case KEYWORD :
        case INTEGER :
//		case FRACTION :
        case DECIMAL :
        case STRING :
        case ENV_STACK :
        case ENVIRONMENT :
        case API :
        case FUNCTION :
        case LAMBDA :
        case VAR :
//		case REF :
//      case READER :
        case NUMBER :
        case NAMESPACE :
        case MAPPED :
        case SEQUABLE :
        case INDEXED :
        case NAMED :
        case CALLABLE :
            return node;

        case INVALID :
            break;
    }
    free(node);
    return NULL;
}

