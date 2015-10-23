/****
    Functions, lambdas, macros and specials

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "object.h"
#include "func.h"

/*
 * Get varargs length
 */
long count_args(va_list args)
{
	Object *walk = va_arg(args, Object *);
	long i = 0;
	while(walk)
	{
		i++;
		walk = va_arg(args, Object *);
	}
	va_end(args);
	return i;
}

/**
	define function interface
*/
MethodDesc	functionInit[]
{
	METHOD_DESC_END
};

/*
	Class initialisation
*/
bool Function()
{

}
