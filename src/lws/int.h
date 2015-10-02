/****
    Integer

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef INTEGER_H
#define INTEGER_H

typedef struct
{
	int 	integer;
} Integer;

Node    *integer(int value);
int     integer_integer(Node * node);
Node 	*integer_to_byte(Node * node);
Node 	*integer_to_char(Node * node);
// Node	*integer_to_integer(Node * node);
Node 	*integer_to_long(Node * node);
Node 	*integer_to_float(Node * node);
Node 	*integer_to_double(Node * node);
Node    *integer_Q_(Node * node);

#endif
