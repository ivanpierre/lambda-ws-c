/****
	types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef TYPE_H
#define TYPE_H

#define bool int
/*
	type of nodes
*/
typedef enum TYPE
{
	NODE = 0,	// All Nodes
	CONST,		// Constant nil, true and false values
	BYTE,		// Byte numeric value
	INT,		// Integer numeric value
	LONG,		// Long numeric value
	BIGINT,		// Big Integer numeric value
	RATIO,		// Ratio numeric value
	FLOAT,		// Floating numeric values
	DOUBLE,		// Double numeric values
	BIGDEC,		// Big decimal numeric values
	CHAR,		// Character value
	HASH,		// Hash value
	STRING,		// String
	FUNC,		// Function pointer
	PTR,		// Pointer
	ARRAY,		// Array of constant size base types
	OBJECT,		// Objects
	NB_TYPES
} TYPE;

typedef struct
{
	const char	*str_type;
	const TYPE  int_type;
	long		size_type;
} Type;

extern Type type_array[];

// public function for types
extern Node		*type()
extern char		*str_type	(TYPE type);
extern long		size_type	(TYPE type);
extern bool		isa_type	(TYPE type, TYPE isa);

#endif
