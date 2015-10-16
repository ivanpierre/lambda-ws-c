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
#include "nodes.h"

// Stack trace
Node *error_stack = NULL;

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

Node *error_box(char *file, int line, char *func, char *mess)
{
	Node *node = new_node(ERROR);
	ASSERT(node, ERR_CREATE_NEW, str_type(ERROR));
	Error *error = STRUCT(node);
	error->file = file;
    error->line = line;
    error->func = func;
    error->mess = mess;
	return unlink_new(node);

	//*********************
	catch:
	unlink_node(node);
	return NULL;
}

/*
 * Push exception on the trace stack
 */
void error_stack_push(Node *node)
{
    Error *error = STRUCT(node);
    error->previous = error_stack;
    LINK_ARG(error_stack, node);
}

/*
 * Print stack trace
 */
void error_stack_print()
{
    Node *walk = error_stack;

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
		free(err->mess);
		unlink_node(old);
    }
	error_stack = NULL;
}
