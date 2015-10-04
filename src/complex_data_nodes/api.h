/****
	Api for functions, variable arguments function refs

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef API_H
#define API_H

/*
	Api
*/
typedef struct
{
	Node        *functions; /* Map of {Args Callable} */
} Api;

// Constructor
Node *api();

#endif
