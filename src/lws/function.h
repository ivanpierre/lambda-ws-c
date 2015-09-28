/****
	Function header

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef FUNCTION_H
#define FUNCTION_H

/*
	Functions
*/
typedef struct
{
	Node    *is_macro;
	Node    *is_special;
	Node    *closure; // as a previous Environment
	Node    *(*f0) ();
	Node    *(*f1) (Node*);
	Node    *(*f2) (Node*,Node*);
	Node    *(*f3) (Node*,Node*,Node*);
	Node    *(*f4) (Node*,Node*,Node*,Node*);
	Node    *(*f5) (Node*,Node*,Node*,Node*,Node*);
	Node    *(*f6) (Node*,Node*,Node*,Node*,Node*,Node*);
	Node    *(*f7) (Node*,Node*,Node*,Node*,Node*,Node*,Node*);
	Node    *(*f8) (Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*);
	Node    *(*f9) (Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*);
	Node    *(*f10)(Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*);
	Node    *(*f11)(Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*);
	Node    *(*f12)(Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*);
	Node    *(*f13)(Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,
					Node*);
	Node    *(*f14)(Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,
					Node*,Node*);
	Node    *(*f15)(Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,
					Node*,Node*,Node*);
	Node    *(*f16)(Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,
					Node*,Node*,Node*,Node*);
	Node    *(*f17)(Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,
					Node*,Node*,Node*,Node*,Node*);
	Node    *(*f18)(Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,
					Node*,Node*,Node*,Node*,Node*,Node*);
	Node    *(*f19)(Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,
					Node*,Node*,Node*,Node*,Node*,Node*,Node*);
	Node    *(*f20)(Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*,
					Node*,Node*,Node*,Node*,Node*,Node*,Node*,Node*);
} Function;

Node *function_is_macro(Node *node);
Node *function_set_macro(Node *node, Node *macro); // nil, FALSE, or else
Node *function_is_special(Node *node);
Node *function_set_special(Node *node, Node *macro); // nil, FALSE, or else
Node *function_clojure(Node *node);
Node *function_args(Node *node);
Node *function_body(Node *node);
void *function_func(Node *node);
Node *function_closure(Node *node);
Node *function_apply(Node *node, Node *args, Node *environment); // sequable
long count_args(va_list args);

#endif
