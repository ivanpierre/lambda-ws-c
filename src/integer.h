/****
	Integers

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef INTEGER_H
#define INTEGER_H
#include "types.h"

node *make_integer(long value);
node *integerp(node *node);
long get_integer(node *node);
bool init_integer_type();

#endif
