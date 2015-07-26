/****
	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef GLOBAL_H
#define GLOBAL_H

#define error(message) \
	fprintf(stderr, message)

#define boolean int
#define FALSE 0
#define TRUE (!FALSE)

#endif
