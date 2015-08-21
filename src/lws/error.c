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

// Error signal
Node *error_node = NULL;

// Error* function
void ERROR_STAR(const char *file, int line, const char func[], char *fmt, ...)
{
    char buffer[4000];
    va_list args;
    va_start(args, fmt);
    va_start(args, fmt);

    sprintf(buffer, "ERROR !!!! %s(%d) %s() : %s\n", file, line, func, fmt);
    vfprintf(stderr, buffer, args);
    fflush(stderr);
}

// Error* function
void TRACE_STAR(const char *file, int line, const char func[], char *fmt, ...)
{
    char buffer[4000];
    va_list args;
    va_start(args, fmt);
    va_start(args, fmt);

                        sprintf(buffer, "            %s(%d) %s() : %s\n", file, line, func, fmt);
    // sprintf(buffer, "            %s\n", fmt);
    vfprintf(stdout, buffer, args);
    fflush(stdout);
}

