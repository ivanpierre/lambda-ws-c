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
#define ERR_INIT        "Error in initialization of %s."
#define ERR_TYPE        "type error %s, expected %s."
#define ERR_INDEX       "Index %ld out of bound."
#define ERR_NULL_INDEX  "Index %ld is NULL."
#define ERR_VAR         "Null pointer on var."
#define ERR_NODE        "Null pointer on node."
#define ERR_ARG         "Bad argument %s."
#define ERR_VAR_UNBOUND "#'%s is unbound."
#define ERR_NEW_BIND    "Unlinking new '%s' witch is linked."
#define ERR_STACK_TRACE "Stack error trace."

/*
 * Manage the stack
 */
typedef struct Error
{
	struct Error 	*previous;
	char 			*file;
	int 			line;
	char 			*func;
	char 			*mess;
} Error;

extern Error *error_stack;

/*
	Errors and assertions
*/
void ERROR_STAR			(const char *file, int line, const char func[], char *fmt, ...);
void TRACE_STAR			(const char *file, int line, const char func[], char *fmt, ...);

/*
 * trace management
 */
void error				(char *file, int line, const char func[], char *mess);
void error_stack_push	(Node *node);
void error_stack_print	();
void error_stack_free	();

/*
	Error Message
*/
#define ERROR(fmt, ...) \
	ERROR_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

/*
	Trace message
*/
#define TRACE(fmt, ...) \
	TRACE_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

/*
	Throw error
*/
#define THROW(fmt, ...) \
	{ \
		ERROR_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__); \
		goto catch; \
	}

#define CATCH_ERROR \
	if(error_stack) \
		goto catch

/*
	Link all arguments, test NULLs, and break on exceptions
*/
#define PUSH_ARGS(nb, ...) \
	if(push_args(nb, ##__VA_ARGS__)) \
		THROW(ERR_VAR) \
	if(error_stack) \
		goto catch

/*
	Unink all arguments, Push error trace if in error condition
*/
#define POP_ARGS(nb, ...) \
	pop_args(nb, ##__VA_ARGS__)); \
	if(error_stack) \
		ERROR(ERR_STACK_TRACE)

/*
	Throw error on condition
*/
#define ASSERT(cond, fmt, ...) \
	if(!(cond)) \
	{ \
		ERROR_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__); \
		goto catch; \
	}

/*
	Throw error on type mismatch (to be deprecated)
*/
#define ASSERT_TYPE(nod, typ) \
	if(!((nod) && node_isa_type(nod, typ))) \
		THROW(ERR_TYPE, (nod)->type->str_type, str_type(typ))

#endif
