/****
    Error

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "oop.h"

// Stack trace (this is a closure)
static Error *error_stack = NULL;

Class		*CLASS_ERROR = NULL;

// Error* function
void ERROR_STAR(char *file, int line, char *func, char *fmt, ...)
{
    char *mess;
    va_list args;

    // get message
    va_start(args, fmt);
    vasprintf(&mess, fmt, args);

    // Push it
	error_stack_push(error_box(file,line, func, mess));

    // print it
    TRACE("ERROR !!!! %s(%d) %s() : %s\n", file, line, func, mess);
}

// Trace* function
void TRACE_STAR(char *file, int line, char *func, char *fmt, ...)
{
    char *mess;
    va_list args;

    // get message
    va_start(args, fmt);
    vasprintf(&mess, fmt, args);

    // print it
    TRACE("            %s(%d) %s() : %s\n", file, line, func, mess);
    free(mess);
}

Error *error_box(char *file, int line, char *func, char *mess)
{
	Error *error = (Error *)new_node(ERROR);
	ASSERT(error, ERR_CREATE_NEW, str_type(ERROR));
	error->file = file;
    error->line = line;
    error->func = func;
    error->mess = mess;
	return unlink_new((void *)error);

	//*********************
	catch:
	unlink_node((void *)error);
	return NULL;
}

/*
 * Push exception on the trace stack
 */
void error_stack_push(Error *error)
{
    error->previous = error_stack;
    LINK_ARG(error_stack, error);
}

/*
 * Print stack trace
 */
void error_stack_print()
{
    Error *err = error_stack;

    TRACE("Stack trace");
    TRACE("===========");

    while(err)
    {
        TRACE("%s(%d) %s() : %s\n", err->file, err->line, err->func, err->mess);
        err = err->previous;
    }

    TRACE("===========");
}

/*
 * erase stack trace
 */
void error_stack_free()
{
    Object *walk = error_stack;

    while(walk)
    {
		Object *old = walk;
        Error *err = STRUCT(walk);
        walk = err->previous;
		free(err->mess);
		unlink_node(old);
    }
	error_stack = NULL;
}
