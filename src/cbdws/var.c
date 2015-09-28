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
#include "strings.h"
#include "free_internal.h"

/*
    Constructor
*/
Node *var(Node *symbol, Node *value)
{
	ASSERT_NODE(symbol, ISYMBOL);
	ASSERT_NODE(value, INODES);

	Node *node = new_node(IVAR);
	Var *var = STRUCT(node);
	var->symbol = symbol;
	var->value  = value;

	unlink_node(symbol);
	unlink_node(value);
	return node;

	//***********
	error_assert:
	unlink_node(symbol);
	unlink_node(value);
	return NULL;
}

/*
    Free var data
*/
Node *var_free(Node *node)
{
	Var *var = STRUCT(node);
	unlink_node(var->symbol);
	unlink_node(var->value);
	free(node);
	return NULL;
}

/*
    Return associated symbol
*/
Node *var_symbol(Node *node)
{
	ACCESS_NODE(Var, symbol, IVAR, ISYMBOL);
}

/*
    Return associated symbol
*/
Node *var_value(Node *node)
{
	Node *res = NULL;
	Node *tmp_node = NULL;
	char *sym = NULL;

	ASSERT_NODE(node, IVAR);

	Var *var = STRUCT(node);
	sym = GET_STRING(var->symbol);
	ASSERT(var->value, ERR_VAR_UNBOUND, sym);

	ASSIGN(res, var->value);

	free(sym);
	unlink_node(node);
	return res;

	//**********************
	error_assert:
	free(sym);
	unlink_node(node);
	return NULL;
}

/*
    Test binding
*/
Node *var_bound_Q_(Node *node)
{
	ASSERT_NODE(node, IVAR);

	Var *var = STRUCT(node);
	Node *res = var->value ? TRUE : FALSE;
	unlink_node(node);
	return res;

	//**********************
	error_assert:
	unlink_node(node);
	return NULL;
}

/*
    Set value
*/
void var_set_value(Node *node, Node *value)
{
	ASSERT_NODE(node, IVAR);
	ASSERT_NODE(value, INODES);
	Var *var = STRUCT(node);
	ASSIGN(var->value, value);
	unlink_node(value);
	unlink_node(node);
	return;

	//**********************
	error_assert:
	unlink_node(node);
	unlink_node(value);
	return;
}
