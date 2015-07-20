/****
	Linked Lists

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef LIST_H
#define LIST_H

typedef list struct {
	void    *segment;
	void    *car;
	void    *cdr;
} list;

void *cons(void *car, void *cdr);
void *car(void *list);
void *cdr(void *list)

#endif