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
#define ERR_INIT        "Initialization of %s."
#define ERR_TYPE        "type error %s, expected %s."
#define ERR_INDEX       "Index %ld out of bound."
#define ERR_NEG_ALLOC   "Allocation cannot be negative %ld."
#define ERR_CREATE_NEW  "cannot create new %s."

/*
    Errors and assertions
*/
extern struct Node *error_node;
void ERROR_STAR(const char *file, int line, const char func[], char *fmt, ...);
void TRACE_STAR(const char *file, int line, const char func[], char *fmt, ...);

#define TRACE(fmt, ...) \
        TRACE_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__);

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

#define ASSERT_TYPE(node, typ, curr_type) \
    if(!(node && (exp_type(node->type) & (typ)))) \
        ABORT(ERR_TYPE, str_type(curr_type), str_btype(typ));

#define ASSERT_ALLOC(alloc) \
    if(!(alloc)) \
        ABORT(ERR_ALLOC);

#endif
