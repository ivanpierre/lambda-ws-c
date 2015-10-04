/****
	Types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
#include "number.h"
#include "strings.h"
#include "function.h"
#include "writer.h"

/*
	Representation of types
*/
Type type_array[] = {
	{"Node",		0},
	{"Byte",		sizeof(Byte)},
	{"Int",			sizeof(Int)},
	{"Long",		sizeof(Long)},
	{"BigInt",		0,
	{"Ratio",		0,
	{"Float",		sizeof(Float)},
	{"Double",		sizeof(Double)},
	{"BigDec",		0,
	{"Char",		sizeof(Char)},
	{"Hash",		sizeof(Hash)},
	{"String",		sizeof(String)},
	{"Function",	sizeof(Function)},
	{"Writer",		sizeof(Writer)},
	{"Invalid",		0}
};

/*
 * get type from an TYPE
 */
static Type *get_type(TYPE type)
{
	return &(type_array[type]);
}

/*
   get type name
*/
char *str_type(TYPE type)
{
	return get_type(type)->str_type;
}

/*
   get type size
*/
long size_type(TYPE type)
{
	return get_type(type)->size_type;
}

/*
 * Get type isa
 */
bool isa_type(TYPE type, TYPE isa)
{
	return  isa == NODE || // NODE accept anything, even a non node pointer
			(get_type(type)->bin_type & get_type(isa)->bin_type &&
			 get_type(type)->bin_type <= get_type(isa)->bin_type);
}
