/****
    Nodes

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "error.h"

// Stack trace
Error *error_stack = NULL;

// Error* function
void ERROR_STAR(const char *file, int line, const char func[], char *fmt, ...)
{
    char *mess;
    va_list args;

    // get message
    va_start(args, fmt);
    vasprintf(&mess, fmt, args);

    // Push it
	Node err = *error(file,line, func, mess);
	error_stack_push(err); // message has been allocated

    // print it
    TRACE("ERROR !!!! %s(%d) %s() : %s\n", file, line, func, mess);
}

// Trace* function
void TRACE_STAR(const char *file, int line, const char func[], char *fmt, ...)
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

/*
 * Push exception on the trace stack
 */
void error_stack_push(char *file, int line, const char func[], char *mess)
{
    Error *error = malloc(sizeof(Exception));
    error->file = file;
    error->line = line;
    error->func = func;
    error->mess = mess;
    error->previous = stack;
    stack = error;
}

/*
 * Print stack trace
 */
void error_stack_print()
{
    NODE *walk = error_stack;

    TRACE("Stack trace");
    TRACE("===========");

    while(walk)
    {
		Error *err = STRUCT(walk);
        TRACE("%s(%d) %s() : %s\n", err->file, err->line, err->func, err->mess);
        walk = err->previous;
    }

    TRACE("===========");
}

/*
 * erase stack trace
 */
void error_stack_free()
{
    Node *walk = error_stack;

    while(walk)
    {
		Node *old = walk;
        Error *err = STRUCT(walk);
        walk = err->previous;
        unlink_node(old);
    }
	error_stack = NULL;
}
