/****
	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef SEGMENT_H
#define SEGMENT_H

typedef segment struct {
	void    *node;
	long    occurences;
} segment;

#endif