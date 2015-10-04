/****
	internal free functions definition

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef FREE_INTERNAL_H
#define FREE_INTERNAL_H

// extern free functions
Node *function_free(Node *var);
Node *number_free(Node *var);
Node *string_free(Node *var);
Node *writer_free(Node *var);

#endif
