/****
    Errors

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef ERROR_H
#define ERROR_H

#include "type.h"

/* standard error texts */
#define ERR_NULL_PTR    "Null pointer assignement."
#define ERR_ALLOC       "Allocation error."
#define ERR_DEALLOC     "Deallocation error."
#define ERR_NEG_ALLOC   "Allocation cannot be negative %ld."
#define ERR_LINK        "Linking error."
#define ERR_CREATE_NEW  "cannot create new %s."
#define ERR_INIT        "Initialization of %s."
#define ERR_TYPE        "type error %s, expected %s."
#define ERR_INDEX       "Index %ld out of bound."
#define ERR_VAR         "Null pointer on var."
#define ERR_NODE        "Null pointer on node."

/*
 * Manage the stack
 */
typedef struct Exception
{
	struct Exception *previous;
	const char *file;
	int line;
	const char *func;
	char *mess;
} Exception;

extern Exception *stack;

/*
    Errors and assertions
*/
void ERROR_STAR(const char *file, int line, const char func[], char *fmt, ...);

void TRACE_STAR(const char *file, int line, const char func[], char *fmt, ...);

/*
 * trace management
 */
void stack_push(const char file[], int line, const char func[], char *mess);

void stack_print();

void stack_free();

#define TRACE(fmt, ...) \
        TRACE_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#define ABORT(fmt, ...) \
    { \
        ERROR_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__); \
        goto error_assert; \
    }

#define ASSERT(cond, fmt, ...) \
    if(!(cond)) \
    { \
        ERROR_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__); \
        goto error_assert; \
    }

#define ASSERT_TYPE(node, type) \
    if(!((node) && node_isa_type(node, type))) \
        ABORT(ERR_TYPE, (node)->type->str_type, str_type(type))

#define ASSERT_NODE(node, tmpnode, type) \
    ASSERT(node, ERR_NODE); \
    ASSERT_TYPE(node, type); \
    tmpnode = link_node(node)

#endif
