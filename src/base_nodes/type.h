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
	MFUNC,		// 21 function pointers for arrity 0 to 20.
	FUNC,		// unique function, with arrity and vararg.
	PTR,		// Pointer on something.
	ARRAY,		// Sized array of constant size `Nodes`.
	CLASS,		// Class definition
	OBJECT,		// Objects
	INTERFACE,	// Interface definition
	NB_TYPES	// .... terminator for this library
} TYPE;

typedef struct
{
	char		*func_name;
	WS_INT		nb_args;
	void		*func;
} FuncDef;

typedef struct
{
	char		*str_type;
	TYPE  		int_type;
	WS_LONG		size_type;
	struct Node	*name_index; // map name id - function index
	WS_INT		nb_func;
	FuncDef		*func[];
} Type;

extern Type type_array[];

// public function for types
extern char		*str_type		(TYPE type);
extern WS_LONG	size_type		(TYPE type);
extern void 	*func_free_type	(TYPE type);
extern bool		isa_type		(TYPE type, TYPE isa);

#endif
