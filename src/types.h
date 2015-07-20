/****
	Types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef TYPES_H
#define TYPES_H

typedef TYPES enum {
	TYPE,
	LIST,
	ARRAY,
	SYMBOL,
	FUNCTION,
	STRING,
	INT,
	TYPES_SIZE
};

typedef node struct {
	void    *segment;
};

typedef type struct {
	void    *segment;
	boolean (*equals)((void *)node1, (void *) node2);
	boolean (*greater)((void *) node1, (void *) node2);
	void    *(*clone)((void *) node);
	void    (*print)((void *) node);
}

#endif