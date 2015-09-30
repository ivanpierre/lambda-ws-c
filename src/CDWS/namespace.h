/****
	Namespace

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NAMESPACE_H
#define NAMESPACE_H

typedef struct
{
	Node        *name;
	Node        *map;   // string -> value
	Node        *alias; // interned  symbol string -> symbol -> ns(name)
} Namespace;

#endif
