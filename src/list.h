/****
	Linked Lists

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef LIST_H
#define LIST_H
#include "types.h"

Node *cons(Node *car, Node *cdr);
Node *car(Node *list);
Node *cdr(Node *list);
bool init_list_type();
// static Node *set_car(Node *list);
// static Node *set_cdr(Node *list);

#endif
