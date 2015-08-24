/****
    All nodes

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NODES_H
#define NODES_H

#include "type.h"

#define BOOL_FALSE 0
#define BOOL_TRUE (!BOOL_FALSE)

/*
    Define in case of allocation debugging
*/
#define DEBUG_ALLOC

/*
    Used type definitions
*/
#define bool            int
struct Node; // forward

/*
    Struct of a base node
*/
typedef struct Node
{
	void        *type;
	long        occurrences;
#ifdef DEBUG_ALLOC
	struct Node *previous_node;
	struct Node *next_node;
#endif
} Node;

// Get Node internal struct
void *STRUCT(Node *node);

// global values
extern Node *NIL;
extern Node *TRUE;
extern Node *FALSE;

// public function for nodes
extern Node *link_node(Node **var, Node *);
extern Node *unlink_node(Node **var);

extern Node *new_node(TYPE type);
extern Node *false_Q_(Node *node);
extern Node *true_Q_(Node *node);

// Non-standard functions
extern void *NODE_STRUCT(Node *node, TYPE type);
extern bool FALSE_Q_(Node *node);
extern bool TRUE_Q_(Node *node);
extern void *THREAD_NODE(Node *init, ...);
extern bool node_isa_type   (Node *node, TYPE isa);

// DEBUG_ALLOC functions
extern bool init_node_list();
extern void print_node_list();

#endif
