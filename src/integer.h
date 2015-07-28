/****
	Integers

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef INTEGER_H
#define INTEGER_H
#include "types.h"

Node *make_integer(long value);
Node *integerp(Node *node);
long get_integer(Node *node);
bool init_integer_type();

#endif
