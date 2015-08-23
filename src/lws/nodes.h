/****
    All nodes

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NODES_H
#define NODES_H

#include "error.h"
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
#define Integer         long
#define Decimal         double
#define String          char *
struct  Node; // forward

/*
    Struct of a base node
*/
typedef struct Node
{
    enum TYPE           type;
    long                occurrences;
#ifdef DEBUG_ALLOC
    struct Node         *previous_node;
    struct Node         *next_node;
#endif
} Node;

void *NODE_STRUCT(Node *node);

// global values
extern Node             *NIL;
extern Node             *TRUE;
extern Node             *FALSE;

// public function for nodes
Node *link_node          (Node **var, Node *);
Node *unlink_node        (Node **var);
Node *new_node           (Node **var, enum TYPE type);

Node *false_Q_           (Node **var, Node *node);
Node *true_Q_            (Node **var, Node *node);

// Non-standard functions
void *NODE_STRUCT       (Node *node, enum TYPE type);
bool FALSE_Q_           (Node *node);
bool TRUE_Q_            (Node *node);
void *THREAD_NODE       (void **var, Node *init, ...);

// DEBUG_ALLOC functions
bool init_node_list     ();
void print_node_list    ();

#endif
