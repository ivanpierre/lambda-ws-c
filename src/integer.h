/****
	Integers

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef INTEGER_H
#define INTEGER_H
#include "nodes.h"

Node *new_integer(long value);
long get_integer(Node *node);
bool integerp(Node *node);
Node *string_integer(Node *node);

#endif
