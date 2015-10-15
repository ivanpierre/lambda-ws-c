/****
	types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef TYPE_H
#define TYPE_H

/*
	type of nodes
*/
typedef enum TYPE
{
	NODE = 0,	// All Nodes
	CONST,		// Constant nil, true and false values
	ERROR,		// Error. someway Exception.
	BYTE,		// Byte numeric value
	INT,		// Integer numeric value
	LONG,		// Long numeric value
	BIGINT,		// Big Integer numeric value
	RATIO,		// numerator and denominator values for rationals.
	FLOAT,		// Floating numeric values
	DOUBLE,		// Double numeric values
	BIGDEC,		// Big decimal numeric values
	CHAR,		// 16 bits unsigned char (UTF16)
	STRING,		// Sized constant String of bytes. Can be UTF.
				// `size` is a long.
	ZSTRING,	// Constant String of bytes. It's complemented by a final \0.
	FUNC,		// unique function, with arrity and vararg.
	PTR,		// Pointer on something.
	ARRAY,		// Sized array of same Types internals.
	TYPE,		// Type definition
	CLASS,		// Class definition
	OBJECT,		// Mapped array of nodes defined by CLASS
	INTERFACE,	// Interface definition
	NB_TYPES	// .... terminator for this library
} TYPES;



typedef struct
{
	char		*func_name;
	WS_INT		nb_args;
	void		*func;
} Method;

typedef struct
{
	char		*member_name;
	Node		*type;
} Member;

typedef struct
{
	char		*str_type;
	TYPES  		int_type;
	WS_LONG		size_type;
	struct Node	*interfaces; // Array of interfaces and classes
	struct Node	*name_index; // Map name id - function index
	WS_INT		nb_func;
	FuncDef		*func[];
} Type;

typedef struct
{
	char		*str_type;
	TYPES  		int_type;
	WS_LONG		size_type;
	struct Node	*interfaces; // Array of interfaces and classes
	struct Node	*name_index; // Map name id - function index
	WS_INT		nb_func;
	FuncDef		*func[];
	MemberDef	*member[];
} Class;

extern Type *type_array;

// public function for types
extern char		*str_type		(TYPES type);
extern WS_LONG	size_type		(TYPES type);
extern void 	*func_free_type	(TYPES type);
extern bool		isa_type		(TYPES type, TYPES isa);

#endif
