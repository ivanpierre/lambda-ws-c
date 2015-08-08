/****
    General reader to create objects

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"

make clean


/*
    Unalloc reader
*/
Node *free_reader(Node *node)
{
    ASSERT(node, "free_reader : null environment");
    ASSERT_TYPE(node, READER, "free_reader : Bad type %s", str_type(node->type));
//	if(node->val.function->closure)
//		node->val.function->closure = free_node(node->val.function->closure);
    return NULL;
}

/*
    String representation of reader
    returns linked allocated String
*/
Node *string_reader(Node *node)
{
    ASSERT(node, "string_reader : null environment");
    ASSERT_TYPE(node, READER, "string_env : Bad type %s", str_type(node->type));
//	if(node->val.function->closure)
//	{
//		Node *map = string_node(node->val.function->closure);
//		Node *res = sprintf_string("<%s macro=%s special=%s closure=%s>",
//									node->val.function->is_macro ? "yes" : "no",
//									node->val.function->is_special ? "yes" : "no",
//									str_type(FUNCTION),
//									map->val.string);
//		unlink_node(map);
//		return res;
//	}
    return sprintf_string("<%s FILE*=?>",
//						   node->val.function->is_macro ? "yes" : "no",
//						   node->val.function->is_special ? "yes" : "no",
                           str_type(FUNCTION));
}



