/****
	Strings. This is base for all named nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef STRING_H
#define STRING_H

#include "types.h"

Node *make_string(char *value);
Node *make_string_alloc(char *value);
Node *stringp(Node *node);
char *get_string(Node *s);
bool init_string_type();
Node *concat_string(Node *s, Node *add);

#endif
