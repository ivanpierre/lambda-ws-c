/****
    Functions, lambdas, macros and specials

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "nodes.h"
#include "func.h"

/*
 * Get varargs length
 */
long count_args(va_list args)
{
	Node *walk = va_arg(args, Node *);
	long i = 0;
	while(walk)
	{
		i++;
		walk = va_arg(args, Node *);
	}
	va_end(args);
	return i;
}
