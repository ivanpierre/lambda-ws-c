/****
	Method class

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef METHOD_H
#define METHOD_H

/*
	Functions or methods
*/
typedef struct
{
	STRUCT_NAMED;
 	WS_BYTE		start_arrity;		// BYTE nb of args of first function
	WS_BYTE		end_arrity;			// BYTE nb of args of last function
	void		*methods;			// Array of ptr on functions
									// NULL for non existant functions
	Object		*varargs;			// BOOLEAN define last function as varargs
} Method;

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
Method *make_method(char *name);

/*
	count nb of Object arguments in va_list until NULL
*/
WS_BYTE count_args(va_list args);

/*
	static functions
*/
Object *dot(String *func, Interface *place, ...);
Object *method(String *func, Object *obj, ...);

/*
	methods
*/
Object *method_invoke(Method *func, ...);

#endif
