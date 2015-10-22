/****
	Struct Struct

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef STRUCT_H
#define STRUCT_H

typedef struct
{
	struct Node *super;				// super
	WS_LONG		pos;				// pos of struct
	WS_LONG		size;				// size of struct
} Struct;

#endif
