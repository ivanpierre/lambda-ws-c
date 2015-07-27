/****
	Strings. This is base for all named nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef STRING_H
#define STRING_H

#include "types.h"

node *make_string(char *value);
bool stringp(node *node);
char *get_string(node *s);
bool init_string_type();

#endif
