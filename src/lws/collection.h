/****
    Collection header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef COLLECTION_H
#define COLLECTION_H

/*
    Collection : Array, List, Map and Set
*/
typedef struct
{
	bool mut;
	long size;
	long max;
	struct Node **nodes;
} Collection;

// Collections 
Node *empty_list();
Node *empty_array();
Node *empty_set();
Node *empty_map();
Node *list(Node *arg, ...);
Node *array(Node *arg, ...);
Node *set(Node *arg, ...);
Node *map(Node *arg, ...);

// Constructor
Node *empty_list();
Node *empty_transient_list();
Node *empty_arrray();
Node *empty_transient_array();
Node *empty_map();
Node *empty_transient_map();
Node *empty_set();
Node *empty_transient_set();

// allocation
Node *collection_resize(Node *coll, Node *size);
Node *collection_clone(Node *coll);

// accessors
Collection *GET_COLLECTION(Node *node);

Node *collection_size(Node *coll);
Node *collection_max(Node *coll);
Node *collection_mut(Node *coll);

// nodes accessors
Node *collection_first(Node *coll);
Node *collection_last(Node *coll);
Node *collection_nth(Node *coll, Node *index);
Node *collection_pos(Node *coll, Node *key);

// functions
Node *collection_dissoc(Node *map, Node *keyval);
Node *collection_take(Node *coll, Node *nb);
Node *collection_push(Node *coll, Node *elem);
Node *collection_pop(Node *coll);
Node *collection_sort(Node *coll); // TODO cmp func
Node *collection_reverse(Node *coll);
Node *collection_reduce(Node *init, Node *func2, Node *coll);
Node *collection_filter(Node *pred, Node *coll);
Node *collection_map(Node *func1, Node *coll);
Node *collection_map2(Node *func2, Node *coll1, Node *coll2);

// helpers for evaluation
Node *list_eval(Node *coll, Node *environment);
Node *collection_eval(Node *coll, Node *environment);

#endif
