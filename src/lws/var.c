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
	Node *tmp_symbol= NULL;
	Node *tmp_value= NULL;
	ASSERT_NODE(symbol, tmp_symbol, ISYMBOL);
	ASSERT_NODE(value, tmp_value, INODES);

	Node *node = new_node(IVAR);
	Var *var = STRUCT(node);
	var->symbol = symbol;
	var->value  = value;

	unlink_node(&tmp_symbol);
	unlink_node(&tmp_value);
	return node;

	//***********
	error_assert:
	unlink_node(&symbol);
	unlink_node(&value);
	unlink_node(&tmp_symbol);
	unlink_node(&tmp_value);
	return NULL;
}

/*
    Free var data
*/
Node *var_free(Node **node)
{
	Var *var = STRUCT(*node);
	unlink_node(&var->symbol);
	unlink_node(&var->value);
	free(*node);
	*node = NULL;
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

	ASSERT_NODE(node, tmp_node, IVAR);

	Var *var = STRUCT(tmp_node);
	sym = GET_STRING(var->symbol);
	ASSERT(var->value, ERR_VAR_UNBOUND, sym);

	link_node(&res, var->value);

	free(sym);
	unlink_node(&tmp_node);
	return res;

	//**********************
	error_assert:
	free(sym);
	unlink_node(&node);
	unlink_node(&tmp_node);
	return NULL;
}

/*
    Test binding
*/
Node *var_bound_Q_(Node *node)
{
	Node *tmp_node = NULL;
	ASSERT_NODE(node, tmp_node, IVAR);

	Var *var = STRUCT(tmp_node);
	Node *res   = var->value ? TRUE : FALSE;
	unlink_node(&tmp_node);
	return res;

	//**********************
	error_assert:
	unlink_node(&node);
	unlink_node(&tmp_node);
	return NULL;
}

/*
    Set value
*/
Node *var_set_value(Node *node, Node *value)
{
	Node *tmp_node = NULL;
	Node *tmp_value = NULL;
	ASSERT_NODE(node, tmp_node, IVAR);
	ASSERT_NODE(value, tmp_value, INODES);
	Var *var = STRUCT(tmp_node);
	link_node(&var->value, tmp_value);
	unlink_node(&tmp_value);
	return tmp_node;

	//**********************
	error_assert:
	unlink_node(&node);
	unlink_node(&value);
	unlink_node(&tmp_node);
	unlink_node(&tmp_value);
	return NULL;
}
