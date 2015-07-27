/****
	Linked lists

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "list.h"

typedef struct {
	NODE;
	node    *car;
	node    *cdr;
} list;

static node *set_car(node *cons, node *car) {
	if(nullp(cons)) {
		error("set_car: can't set car of nil\n");
		return NULL;
	}
	unlink_node(((list *)cons)->car);
	((list *)cons)->car = link_node(car);
	return cons;
}

static node *set_cdr(node *cons, node *cdr) {
	if(nullp(cons)) {
		error("set_car: can't set car of nil\n");
		return NULL;
	}
	if(!nullp(cdr) && (get_type(cdr) != LIST)) {
		error("set_car: can't set cdr as a non list or nil\n");
		return NULL;
	}
	unlink_node(((list *)cons)->cdr);
	((list *)cons)->car = link_node(cdr);
	return cons;
}

node *cons(node *car, node *cdr) {
	node *cons = create_node(LIST);
	node *new = NULL;

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

node *car(node *cons) {
	if(nullp(cons)) {
		return NULL;
	}
	return link_node(((list*)cons)->car);
}

node *cdr(node *cons) {
	if(nullp(cons)) {
		return NULL;
	}
	return link_node(((list*)cons)->cdr);
}


