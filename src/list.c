/****
	Linked lists

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

static Node *set_car(Node *node, Node *car)
{
	if(!nullp(node))
	{
		error("set_car: can't set car of nil\n");
		return NIL;
	}
	if(!listp(node))
	{
		error("set_car: only can set car of a list\n");
		return node;
	}
	node->val.car = link_node(car);
	return node;
}

static Node *set_cdr(Node *nodes, Node *cdr)
{
	if(!node)
	{
		error("set_car: can't set cdr of nil\n");
		return NIL;
	}
	if(!nullp(cdr) && (cdr->type != LIST))
	{
		error("set_cdr: set cdr with a non list or nil\n");
		return NIL;
	}
	node->val.cdr = link_node(cdr);
	return cons;
}

Node *new_list(Node *car, Node *cdr)
{
	Node *node = create_node(LIST);

	if(!node)
		return NIL;

	node->val.car = link_node(car);
	node->val.cdr = link_node(cdr);

	return node;
}

Node *get_car(Node *node)
{
	if(!node)
		return NIL;
	return link_node(node->val.car);
}

Node *get_cdr(Node *node)
{
	if(!node)
		return NIL;
	return link_node(node->val.cdr);
}

/*
	unalloc list content
*/
void free_list(Node *node)
{
	list *lst = (list *)node;
	unlink_node(lst->car);
	lst->car = NULL;
	unlink_node(lst->cdr);
	lst->cdr = NULL;

}

/*
	print list
*/
Node *string_list(Node *node)
{
	char *formatted = strdup("(");
	char *sep = " ";
	char *tmp;
	while(!nullp(node))
	{
		tmp = print_node(((list *)node)->car);
		asprintf(&tmp, "%s%s%s", formatted, tmp, sep);
		free(formatted);
		formatted = tmp;
		node = ((list *)node)->cdr;
		if(!((list *)node)->cdr)
			sep = "";
	}
	asprintf(&formatted, "%s%s", tmp, ")");
	free(tmp);
	return formatted;

}

