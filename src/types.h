/****
	Types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef TYPES_H
#define TYPES_H

typedef enum {
	TYPE,
	LIST,
	ARRAY,
	SYMBOL,
	FUNCTION,
	STRING,
	INT,
	TYPES_SIZE
} TYPES;

typedef struct {
	void    *segment;
} node;

typedef struct {
	void    *segment;
	int     (*equals)(void *node1, void *node2);
	int     (*cmp)(void * node1, void *node2);
	void    *(*clone)(void *node);
	void    (*print)(void *node);
} type;

#endif