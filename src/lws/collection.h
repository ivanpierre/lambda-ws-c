/****
    Ciollection header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef COLLECTION_H
#define COLLECTION_H

// Collections
bool collection(Node **node, enum TYPE type, long alloc);
bool collection_free(Node **node); // internal
bool collection_malloc(Node **node, long diff);
bool collection_realloc(Node **node, long diff);
bool collection_malloc_clone(Node **node, Node *coll, long diff);

// accessors
long        collection_size(Node *coll);
Node        *collection_first(Node *coll);
Node        *collection_last(Node *coll);
Node        *collection_take(Node *coll, long nb);
Node        *collection_assoc(Node *map, Node *keyval, Node *value);
Node        *collection_dissoc(Node *map, Node *keyval);
Node        *collection_nth(Node *coll, long index);
Node        *collection_push(Node *coll, Node *elem);
Node        *collection_pop(Node *coll);
Node        *collection_sort(Node coll); // TODO cmp func
Node        *collection_reverse(Node coll);
long        collection_pos(Node *coll, Node *key);

// helpers for evaluation
Node        *list_eval(Node *node, Node *env);
Node        *keyval_eval(Node *node, Node *env);
Node        *collection_eval(Node *node, Node *env);

// functions
Node        *collection_reducel(Node *init, Node *(*fn)(Node *arg1, Node *arg2), Node *coll);
Node        *collection_filter(Node *(*fn)(Node *node), Node *coll);
Node        *collection_map(Node *(*fn)(Node *node), Node *coll);
Node        *collection_map2(Node *(*fn)(Node *node1, Node *node2), Node *coll1, Node *coll2);
Node        *collection_eval(Node *node, Node *env);

#endif
