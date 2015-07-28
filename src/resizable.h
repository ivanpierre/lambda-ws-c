/****
	Resizable array, will be used for all collections storage

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef INTEGER_H
#define INTEGER_H
#include "types.h"

Node *make_integer(long value);
Node *integerp(Node *node);
long get_size(Node *node);
long get_top(Node *node);
Node *add_node(Node *Node, Node *element);
Node *mut_node(Node *node, Node *element, long pos);
bool init_resizable_type();

#endif
