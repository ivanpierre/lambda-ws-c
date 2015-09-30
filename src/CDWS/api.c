/****
	Api for functions, variable arguments function refs

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
#include "api.h"
#include "collection.h"
#include "free_internal.h"

/*
 * Create empty api
 */
Node *api()
{
	Node *res = new_node(IAPI);
	Api *functions = NULL;
	ASSERT(res, ERR_CREATE_NEW, str_type(IAPI));
	functions = STRUCT(res);
	functions->functions = empty_map();
	ASSERT(functions->functions, ERR_INIT, str_type(IAPI));
	return res;

	//**************
	error_assert:
	unlink_node(res);
	if(functions)
		unlink_node(functions->functions);
	return NULL;
}

/*
 * get api map of functions
 */
Node *api_api(Node *node)
{
	ACCESS_NODE(Api, functions, IAPI, IMAP);
}
