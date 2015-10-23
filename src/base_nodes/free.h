/****
	Free

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef FREE_H
#define FREE_H

// public function for nodes
extern Object *link_node      (Object *);
extern Object *unlink_node    (Object *var);
extern Object *unlink_new     (Object *var);

extern void print_node_stack();
extern void init_node_list();

/*
	double linked list of nodes for debug
*/
#ifdef DEBUG_ALLOC
	extern Object *first_node;
	extern Object *last_node;
#endif

#endif
