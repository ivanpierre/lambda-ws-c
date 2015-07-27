/****
	Linked Lists

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef LIST_H
#define LIST_H
#include "types.h"

node *cons(node *car, node *cdr);
node *car(node *list);
node *cdr(node *list);
// static node *set_car(node *list);
// static node *set_cdr(node *list);

#endif
