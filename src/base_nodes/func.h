/****
	Function class

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef FUNCTION_H
#define FUNCTION_H

/*
	Functions or methods
*/
typedef struct
{
	Node		*name				// ZSTRING Name of function
 	Node		*start_arrity;		// BYTE nb of args of first function
	Node		*end_arrity;		// BYTE nb of args of last function
	Node		*methods;			// TYPED_ARRAY of PTR on functions
									// NIL for non existant intermediate
									// functions
	Node		*varargs;			// BOOLEAN define last function as varargs
} Function;

/**
	Definition structure for functions.
	This will be used to initialize Interfaces and Class
*/
typedef struct
{
	char		*name;
	WS_BYTE		nb_args;
	void		*function;
} MethodDesc;

// last line of MethodDesc ARRAY
#define METHOD_DESC_END {NULL, 0, NULL}

/*
	Class initialisation
*/
bool Function();

/*
	count nb of Node arguments in va_list until NULL
*/
WS_BYTE count_args(va_list args);

#endif
