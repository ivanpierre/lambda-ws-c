/****
	Types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "string.h"

#if defined(DEBUG_ALLOC)
	Node *first_node    = NULL;
	Node *last_node     = NULL;
#endif

/*
	Node of type TYPE
*/
typedef struct
{
	NODE;
	Node    *name;
	long    size;
	Node    *(*equals)(Node *Node1, node *node2);
	Node    (*cmp)(Node *node1, Node *node2);
	Node    *(*eval)(Node *node);
	Node    *(*free)(Node *node);
	Node    *(*print)(Node *node);
} type;

/*
	Array of types definition
*/
Node *types[TYPES_SIZE];

/*
	test if linking is applyable
*/
Node *unlinkable(Node *n)
{
	return nulp(node) || falsep(node) || truep(node);
}

/*
	create a link to node
	Return Linked node or NIL
*/
Node *link_node(Node *node)
{
	if(!unlinkable(node))
		node->occurences++;
	return node;
}

/*
	Unlink node
	return NIL or subsisting node
*/
Node *unlink_node(Node *node)
{
	if(!unlinkable(node))
	{
		if(node-occurence)
			node->occurences--;
		if(!node->occurences)
			free_node(node);
	)
	return NIL;
}

/*
    Test type boundaries
*/
static TYPES test_type(TYPES type)
{
	if(type < 0 || type >TYPES_SIZE)
		return NIL_TYPE;
	return type;
}

/*
	return type of node
*/
TYPES get_type(Node *node)
{
	if(nullp(node))
		return NIL_TYPE;
	return test_type(node->type);
}

/*
	Set type definition
	Return linked definition or NIL
*/
Node *set_type(TYPES type, Node *type_def)
{
	if(test_type(type))
	{
		error("set_type : outer bound type\n");
		return NIL;
	}
	if(nullp(type_def))
	{
		error("set_type : null type\n");
		return NIL;
	}
	types[type] = linked_node(type_def);
	return linked_node(type_def);
}

/*
	get Type definition
	Return linked definition or NIL
*/
Node *get_type_details(TYPES type)
{
	if(test_type(type))
	{
		error("get_type_details : invalid type\n");
		return NIL;
	}
	return link_node(types[type]);
}

/*
	get the type name from the type value
	return linked name or NIL
*/
Node *get_type_name(TYPES type_enum)
{
	Node *type_det = get_type_details(type_enum);
	Node *name;
	if(nullp(type_det))
	{
		error("get_type_name : invalid type\n");
		return NIL;
	}
	name = link_node(((type*)type_det)->name);
	type_det = unlink_node(type_det);
	return name;
}

/*
	get the type name from the node
	transfer linked name
*/
Node *get_node_type_name(Node *node)
{
	TYPES type = NIL_TYPE;
	if(node)
		type = node->type;

	return get_type_name(type);
}

/*
	Create a node
	Constructor, return linked
*/
Node *create_node(TYPES type_of_node)
{
	type *node_type = (type *)get_type_details(type_of_node); // linked
	long size;
	if(!node_type)
		return NIL;

	size = node_type->size;
	node_type = unlink_node(node_type); // unlink

	Node *new = malloc(size);
	Node *tmp = new;

	if(nullp(new))
	{
		error("create_node : Error : allocation of node\n");
		return NIL;
	}
	new = init_node(new, type_of_node); // init_node does link
	if(nullp(new))
	{
		free(tmp); //
		error("create_node : Error : initialisation of node\n");
	}

	return new;
}

/*
	Create a type node
	Constructor, return linked or NIL
*/
Node *create_type(	node  *name,
					long    size,
					node    *(*equals)(Node *node1, Node *node2),
					node    *(*cmp)(node *node1, Node *node2),
					Node    *(*eval)(Node *node),
					Node    *(*free)(Node *node),
					Node    *(*print)(Node *node))
{
	type *new_type;
	Node *new = malloc(sizeof(type));
	Node *tmp = new;

	if(nullp(new))
	{
		error("create_node : Error : allocation of node");
		return NIL;
	}

	new = init_node(new, TYPE); // init_node returns linked node

	if(nullp(new))
	{
		error("create_node : Error : initialisation of node");
		free(tmp); // unalloc malloc
		return NIL;
	}

	new_type = (type *)new;
	new_type->name = name;
	new_type->size = size;
	new_type->equals = equals;
	new_type->cmp = cmp;
	new_type->eval = eval;
	new_type->free = free;
	new_type->print = print;
	return new; // linked node
}

/*
	Are nodes equals ?
	Return linked result or NIL
*/
Node *equals_node(Node *node1, Node *node2)
{
	if(node1 == node2)
	{
		return link_node(node1);
	}

	if(nullp(node1) || nullp(node2))
		return NIL;

	if(node1->type != node2->type)
		return NIL;

	type *t = (type *)get_type_details(node1->type);
	if(!t->equals)
		return MIL;

	// t->equal will link or NIL
	return t->equals(node1, node2);
}

/*
	Compare nodes
	return linked integer od NIL
*/
Node *cmp_node(Node *node1, Node *node2)
{
	// exact identity
	if(node1 == node2)
		return make_integer(0);

	// get linked type or NIL
	type *t = comparablep(node1, node2);

	// no detail on type
	if(nullp(t))
	{
        error("cmp_node : system error, not comparable\n");
        return NIL;
    }

    // returned value is linked or NIL
    Node *res = t->cmp(node1, node2);
    t = unlink_node(t);
	return res;
}

/*
	Are nodes comparable ?
*/
Node *comparablep(Node *node1, Node *node2)
{
	if(nullp(node1) || nullp(node2))
		return NIL;

	if(node1->type != node2->type)
		return NIL;

	type *t = (type *)get_type_details(node1->type); // t is linked or NIL

	if(!t)
	{
        error("comparablep : system error, not type details\n");
		return NIL;
	}

	if(!t->cmp)
	{
		t = unlink_node(t); // unlink incomparable type
		return NIL;
	}

	return t;
}

/*
	unalloc node
*/
Node *free_node(Node *node)
{
	if(nullp(node))
	{
		return NIL;
	}

	type *t = (type *)get_type_details(node->type); // get linked type or NIL

	if(!t)
	{
        error("free_node: system error, not type details\n");
		return NIL;
	}

	if(t->free)
		node = t->free(node);

	unlink_node(t);
	unlink_node(node);

	return NIL;
}

/*
	print node this one is public !!!!
*/
Node *print_node(Node *node)
{
	if(nullp(node))
	{
		return make_string_alloc("nil");
	}

	type *t = (type *)get_type_details(node->type);

	if(!t)
	(
		return make_string_alloc("<invalid type>");
	)

	if(!t->print)
	{
		// Strings are strings, no change
		if(get_type(t) == STRING)
			return link_node(node);

		char *formatted;
		asprintf(&formatted, "<%s %ld>", get_node_type_name(node), node);
		return make_string(formatted); // string allocated by asprintf
	}

	// linked by the function
	return t->print(node);
}

/*
	print node
*/
static Node *print_type(Node *node)
{
	char *formatted;
	Node *name = ((type *)node)->name;
	char *str_name;

	if(!name)
		str_name = "\"(print_type : no name)\"";
	else
	{
		str_name = get_string(name);
		if(!strName)
			str_name = "\"(print_type : null)\"";
		unlink(name);
	}

	asprintf(&formatted, "<type %s>", str_name);
	return make_string(formatted); // formatted has been allocated by asprintf, string linked
}

/*
	Type of node
*/
TYPES get_node_type(Node *node)
{
	return node->type;
}

/*
	Unalloc type
*/
static Node *free_type(Node *node)
{
	type *t = (type *)node;
	if(!typep(node))
		return node;

	if(t->name)
	{
		free_node(t->name);
		t-name = NIL;
	}
	return node;
}


/*
	Test type of node
*/
Node *typep(Node *node, TYPES type)
{
	if(get_node_type(node) == type)
		return link_node(node) || true_node();  // we have to manage we try to test a NIL node
												// typep(NIL, NIL_NODE) == TRUE
	else
		return NIL;
}

/*
    Is node NULL
*/
Node *nullp(Node *node)
{
	return node ? NIL : true_node();
}

/*
	First initialisation of an allocated node, first link to the data segment
	Return linked node or NIL
*/
Node *init_node(Node *node, TYPES type)
{
	if(nullp(node))
	{
		error("init_node : absent node\n");
		return NIL;
	}

	// DEBUG
	fprintf(stdout, "init node : ");
	print_node(node);
	fprintf(stdout, "\n");

	node->type = type;
	node->occurences = 0; // will be incremented on link
#ifdef DEBUG_ALLOC
	if(nullp(last_node))
	{
		node->previous_node = node->next_node = NULL;
		last_node = first_node = node;
	}
	else
	{
		node->previous_node = last_node;
		node->next_node = NULL;
		last_node->next_node = node;
	}
#endif
	return link_node(node);
}

/*
	completely unlink and init node list
*/
bool init_node_list()
{
#ifdef DEBUG_ALLOC
	while(first_node)
	{
		Node *node = first_node;
		first_node = node->next_node;

		// empty allocation
		while(node)
		    node = free_node(node);
	}
	last_node = NULL;
#else
#endif
	return TRUE;
}

/*
	Print node list
*/
bool print_node_list()
{
#ifdef DEBUG_ALLOC
	Node *walk = first_node;
	fprintf(stdout, "Node list\n", formatted);
	while(walk)
	{
		char *formatted = print_node(walk);
		if(formatted)
		{
			fprintf(stdout, "%s\n", formatted);
			free(formatted);
		}
		else
		{
			error("print_node_list : cannot format the node");
		}
		walk = walk->next_node;
	}
	fprintf(stdout, "End of node list\n", formatted);
	return TRUE;
#else
	error("print_node_list : not in debug mode, no list to print\n");
	return FALSE;
#endif
}

/*
	init type TYPE, so the type exists in the types... ;)
*/
bool init_types()
{
	Node *t =       // we link the type if created
	set_type(TYPE, create_type( "type",
						sizeof(type),
						NULL,   // equals
						NULL,   // cmp
						NULL,   // eval
						&free_type,   // free
						&print_type));  // print
	if(nullp(t))
	{
		error("init_types : error creating type\n");
		return TRUE;
	}
	unlink_node(t); // unlink type
	return TRUE;
}

