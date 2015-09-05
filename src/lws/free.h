/****
	Named : Symbol and keyword header

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef FREE_H
#define FREE_H

// public function for nodes
extern Node *get_node       (Node *);
extern Node *link_node      (Node **var, Node *);
extern Node *unlink_node    (Node **var);
extern Node *unlink_new     (Node *var);

extern void print_node_stack();

extern Node *(*free_ptr)(Node **node);

/*
	double linked list of nodes for debug
*/
#ifdef DEBUG_ALLOC
	extern Node *first_node;
	extern Node *last_node;
#endif

#endif


