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
	{"Const",		CONST,		0				},
	{"Byte",		BYTE,		sizeof(Byte)	},
	{"Short",		SHORT,		sizeof(Short)	},
	{"Int",			INT,		sizeof(Int)		},
	{"Long",		LONG,		sizeof(Long)	},
	{"Float",		FLOAT,		sizeof(Float)	},
	{"Double",		DOUBLE,		sizeof(Double)	},
	{"Char",		CHAR,		sizeof(Char)	},
	{"String",		STRING,		0,				},
	{"ZString",		ZSTRING,	0,				},
	{"Ptr",			PTR,		sizeof(void *)	},
	{"Array",		ARRAY,		0,				}
};

/*
	Representation of classes
*/
Class class_array[] = {
	{"Error",		ERROR		},
	{"Bigint",		BIGINT		},
	{"Ratio",		RATIO		},
	{"Bigdec",		BIGDEC		},
	{"Func",		FUNC		},
	{"Type",		TYPE		},
	{"Object",		OBJECT		},
	{"Interface",	INTERFACE	}
};

/*
	Representation of interfaces
*/
Class interface_array[] = {
	{"Node",		NODE}
};

/*
 * get type from an TYPE
 */
static Type *get_type(TYPES type)
{
	return &(type_array[type]);
}

/*
   get type name
*/
char *str_type(TYPES type)
{
	return get_type(type)->str_type;
}

/*
   get type size
*/
long size_type(TYPES type)
{
	return get_type(type)->size_type;
}

/*
 * Get type isa
 */
bool isa_type(TYPES type, TYPES isa)
{
	return  isa == NODE || // NODE accept anything, even a non node pointer
			(get_type(type)->bin_type & get_type(isa)->bin_type &&
			 get_type(type)->bin_type <= get_type(isa)->bin_type);
}
