/****
	Linked Lists

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef SYMBOL_H
#define SYMBOL_H

#include "types.h"

typedef list struct {
	void    *segment;
	void    *car;
	void    *cdr;
};

#endif