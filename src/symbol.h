/****
	Symbols

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef SYMBOL_H
#define SYMBOL_H

#include "types.h"

typedef symbol struct {
	void    *segment;
	void    *name;
	void    *value;
}

#endif