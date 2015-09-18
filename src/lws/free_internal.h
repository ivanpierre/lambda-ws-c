/****
	internal free functions definition

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef FREE_INTERNAL_H
#define FREE_INTERNAL_H

// extern free functions
Node *api_free(Node *var);
Node *collection_free(Node *var);
Node *environment_free(Node *var);
Node *function_free(Node *var);
Node *keyval_free(Node *var);
Node *named_free(Node *var);
Node *namespace_free(Node *var);
Node *number_free(Node *var);
Node *reader_free(Node *var);
Node *seq_free(Node *var);
Node *string_free(Node *var);
Node *var_free(Node *var);
Node *writer_free(Node *var);

#endif
