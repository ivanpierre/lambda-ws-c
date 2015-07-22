/****
	Types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef TYPES_H
#define TYPES_H

typedef enum {
	NULL_TYPE,
	ERROR,
	TYPE,
	LIST,
	ARRAY,
	MAP,
	SYMBOL,
	FUNCTION,
	SPECIAL,
	LAMBDA,
	STRING,
	INT,
	TYPES_SIZE
} TYPES;

#define boolean int

TYPES get_type(void *node);
boolean typep(void *node);
boolean nullp(void *node);

#endif