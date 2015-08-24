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
Exception *stack = NULL;

// Error* function
void ERROR_STAR(const char *file, int line, const char func[], char *fmt, ...)
{
    char *mess;
    va_list args;

    // get message
    va_start(args, fmt);
    vasprintf(&mess, fmt, args);

    // Push it
    stack_push(file,line, func, mess); // message has been allocated

    // print it
    fprintf(stderr, "ERROR !!!! %s(%d) %s() : %s\n", file, line, func, mess);
    fflush(stderr);
}

// Error* function
void TRACE_STAR(const char *file, int line, const char func[], char *fmt, ...)
{
    char *mess;
    va_list args;

    // get message
    va_start(args, fmt);
    vasprintf(&mess, fmt, args);

    // print it
    fprintf(stdout, "            %s(%d) %s() : %s\n", file, line, func, mess);
    fflush(stdout);
    free(mess);
}

/*
 * Push exception on the trace stack
 */
void stack_push(const char file[], int line, const char func[], char *mess)
{
    Exception *error = malloc(sizeof(Exception));
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
void stack_print()
{
    Exception *walk = stack;

    fprintf(stderr, "Stack trace");
    fprintf(stderr, "===========");

    while(walk)
    {
        fprintf(stderr, "%s(%d) %s() : %s\n",
                walk->file, walk->line, walk->func, walk->mess);
        walk = walk->previous;
    }

    fprintf(stderr, "===========");
}

/*
 * erase stack trace
 */
void stack_free()
{
    Exception *walk = stack;

    while(walk)
    {
        Exception *old = walk;
        walk = walk->previous;
        free(old->mess);
        free(old);
    }
}
