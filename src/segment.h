/****
	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef SEGMENT_H
#define SEGMENT_H

#include "types.h"

typedef segment struct {
	void    *node;
	TYPES   type;
	long    occurences;
} segment;

#endif