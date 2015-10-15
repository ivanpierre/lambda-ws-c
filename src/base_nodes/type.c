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
#include "func.h"
#include "writer.h"

/*
	Representation of types
*/
Type type_array[] = {
	{"Node",		NODE,		0				NULL},
	{"Const",		CONST,		0,				NULL},
	{"Error",		ERROR,		sizeof(Error),	NULL},
	{"Byte",		BYTE,		sizeof(Byte),	NULL},
	{"Int",			INT,		sizeof(Int),	NULL},
	{"Long",		LONG,		sizeof(Long),	NULL},
	{"Bigint",		BIGINT,		0,				&bigint_free}
	{"Ratio",		RATIO,		0,				&ratio_free}
	{"Float",		FLOAT,		sizeof(Float),	NULL},
	{"Double",		DOUBLE,		sizeof(Double),	NULL},
	{"Bigdec",		BIGDEC,		0,				&bigdec_free}
	{"Char",		CHAR,		sizeof(Char),	NULL},
	{"String",		STRING,		0,				NULL},
	{"ZString",		ZSTRING,	0,				NULL},
	{"Func",		FUNC,		0, 				NULL},
	{"Ptr",			PTR,		sizeof(void *),	NULL},
	{"Array",		ARRAY,		0,				&array_free},
	{"Type",		TYPE,		0,				&type_free},
	{"Record",		OBJECT,		0,				&object_free},
	{"Interface",	INTERFACE,	0,				&interface_free}
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
