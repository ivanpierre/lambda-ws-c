/****
	Symbols

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef SYMBOL_H
#define SYMBOL_H

typedef struct {
	void    *segment;
	void    *name;
	void    *value;
} symbol;

#endif