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
#define bool        int
#define Integer     long
#define Decimal     double
#define String      char *
struct  Node; // forward

/*
    Struct of a base node
*/
typedef struct Node
{
    enum TYPE       type;
    long            occurrences;
#ifdef DEBUG_ALLOC
    struct Node     *previous_node;
    struct Node     *next_node;
#endif
    union
    {
        Integer     integer;        // Integer as long
        Decimal     decimal;        // Floats as double
        void        *compl;         // all node details
    } val;
} Node;

// global values
extern Node *nil;
extern Node *true;
extern Node *false;

/*
    Main functions pointers FREE, EVAL, PRINT
*/
extern Node *(*eval_ptr)(Node *node, Node *env);

// Node *FREE(Node *node); // called by unlink_node
Node *EVAL(Node *node, Node *env);

// public function for nodes
bool        *link_node(Node **node);
bool        *unlink_node(Node **node);
bool        FALSE(Node *node);
bool        TRUE(Node *node);
bool        NEW(Node **node, enum TYPE type);
bool        thread_node(void **res, Node *init, ...);
bool        GET_ELEM_STRING(void **node, Node *elem, Node *(*func)(Node *));


// Atom
Node        *var_deref(Node *node); // internal

// DEBUG_ALLOC functions
bool        init_node_list();
void        print_node_list();

#endif
