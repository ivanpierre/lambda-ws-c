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

typedef struct
{
	NODE;
	Node    *car;
	Node    *cdr;
} list;

static Node *set_car(Node *cons, Node *car)
{
	if(nullp(cons))
	{
		error("set_car: can't set car of nil\n");
		return NULL;
	}
	unlink_node(((list *)cons)->car);
	((list *)cons)->car = link_node(car);
	return cons;
}

static Node *set_cdr(Node *cons, Node *cdr)
{
	if(nullp(cons))
	{
		error("set_car: can't set car of nil\n");
		return NULL;
	}
	if(!nullp(cdr) && (get_type(cdr) != LIST))
	{
		error("set_car: can't set cdr as a non list or nil\n");
		return NULL;
	}
	unlink_node(((list *)cons)->cdr);
	((list *)cons)->car = link_node(cdr);
	return cons;
}

Node *cons(Node *car, Node *cdr)
{
	Node *cons = create_node(LIST);
	Node *new = NULL;

	if(nullp(cons))
		return NULL;

	((list*)cons)->car = NULL;
	((list*)cons)->cdr = NULL;

	new = set_car(cons, car);
	if(nullp(new))
		unlink_node(cons);

	new = set_cdr(new, cdr);
	if(nullp(new))
		unlink_node(cons);

	return new;
}

Node *car(Node *cons)
{
	if(nullp(cons))
	{
		return NULL;
	}
	return link_node(((list*)cons)->car);
}

Node *cdr(Node *cons)
{
	if(nullp(cons))
	{
		return NULL;
	}
	return link_node(((list*)cons)->cdr);
}

/*
	unalloc list content
*/
static void free_list(Node *node)
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
static char *print_list(Node *node)
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

/*
	init type LIST, so the type exists in the types... ;)
*/
bool init_list_type()
{
	if(!set_type(LIST, create_type( "list",
						sizeof(list),
						NULL,   // equals
						NULL,   // cmp
						NULL,   // eval
						&free_list,   // free
						&print_list)))  // print
	{
		error("init_list_type : error creating list type\n");
		return FALSE;
	}
	return TRUE;
}


