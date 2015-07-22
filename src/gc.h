/****
	Garbage collector

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef GC_H
#define GC_H

void *init_gc();
void *add_gc(void *node);
void *link_gc(void *node);
void *unlink_gc(void *node);

#endif