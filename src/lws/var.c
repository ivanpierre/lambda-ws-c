/****
    Var : boxing of variable

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "var.h"

/*
    Var
*/
typedef struct
{
    Node                *symbol;  // reference symbol
    Node                *value;   // Bobed value
} Var;

/*
    Access Collection from Node
*/
static Var *GET_VAR(Node *node)
{
    return (Var *)(node->val.compl);
}

/*
    Constructor
*/
Node *var(Node *symbol, Node *value)
{
    ASSERT(symbol, "Null symbol");
    ASSERT_TYPE(symbol, SYMBOL, "Var not referencing a Symbol");

    Node *node = NEW(IVAR);
    GET_VAR(node)->symbol = symbol;
    GET_VAR(node)->value = value;

    return node;
}

/*
    Free var data
*/
Node *var_free(Node *node)
{
    unlink_node(GET_VAR(node)->symbol);
    unlink_node(GET_VAR(node)->value);
    free(GET_VAR(node));
    free(node);
    return NULL;
}

/*
    Return associated symbol
*/
Node *var_symbol(Node *node)
{
    ASSERT_TYPE(node, VAR, "Var not referencing a Symbol");
    return GET_VAR(node)->symbol;
}

/*
    Return associated symbol
*/
Node *var_value(Node *node)
{
    ASSERT_TYPE(node, VAR, "Var not referencing a Symbol");
    Node *value = GET_VAR(node)->symbol;
    if(!value)
    {
        String sym_str = GET_ELEM_STRING(node, &var_symbol);
        ERROR("%& is unbound", sym_str);
        free(sym_str);
    }
    return link_node(value);
}

/*
    Test binding
*/
Node *var_bound_Q_(Node *node)
{
    ASSERT_TYPE(node, VAR, "Var not referencing a Symbol");
    Node *value = GET_VAR(node)->symbol;
    if(!value)
    {
        String sym_str = GET_ELEM_STRING(node, &var_symbol);
        ERROR("%& is unbound", sym_str);
        free(sym_str);
    }
    Node *res = value ? true : FALSE;
    unlink_node(value);
    return res;
}

/*
    Set value
*/
Node *var_set_value(Node *node, Node *value)
{
    GET_VAR(node)->value = value;
    return node;
}
