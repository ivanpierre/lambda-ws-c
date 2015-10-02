/****
	Nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
#include "named.h"
#include "number.h"
#include "strings.h"
#include "function.h"
#include "writer.h"

/*
	type of nodes
*/
const long BNODES       = (1l << IINVALID) - 1;  // all nodes
const long BCONST       = (1l << ICONST);        // Constant nil, false, true values
const long BINTEGER     = (1l << IINTEGER);      // Integer numeric values
const long BFRACTION    = (1l << IFRACTION);     // Fractional numeric values
const long BDECIMAL     = (1l << IDECIMAL);      // floating numeric values
const long BSTRING      = (1l << ISTRING);       // String
const long BFUNCTION    = (1l << IFUNCTION);     // Function pointer
const long BWRITER      = (1l << IWRITER);       // Writer implemented in language
const long BTYPE        = (1l << ITYPE);         // Type of nodes
const long BINVALID     = IINVALID;              // Self explaining... used not to go too far... :D

/*
	Representation of types
*/
Type type_array[] = {{"Node",       INODES,         BNODES,     0},
					{"Nil",         INIL,           BNIL,       0},
					{"True",        ITRUE,          BTRUE,      0},
					{"False",       IFALSE,         BFALSE,     0},
					{"Integer",     IINTEGER,       BINTEGER,   sizeof(Integer)},
					{"Fraction",    IFRACTION,      BFRACTION,  0},
					{"Decimal",     IDECIMAL,       BDECIMAL,   sizeof(Decimal)},
					{"String",      ISTRING,        BSTRING,    sizeof(String)},
					{"Function",    IFUNCTION,      BFUNCTION,  sizeof(Function)},
					{"Writer",      IWRITER,        BWRITER,    sizeof(Writer)},
					{"Type",        ITYPE,          BTYPE,      sizeof(NodeType)},
					{"Invalid",     IINVALID,       BINVALID,   0},
					{"Unlikable",   IUNLINKABLE,    BUNLINKABLE, 0},
					{"Boolean",     IBOOLEAN,       BBOOLEAN,   0}};

/*
 * get type from an TYPE
 */
Type *get_type(TYPE type)
{
	return &(type_array[type]);
}

/*
   get bitmaped version of node type
*/
long bin_type(TYPE type)
{
	return get_type(type)->bin_type;
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
	return  isa == INODES || // INODES accept anything, even a non node pointer
			(get_type(type)->bin_type & get_type(isa)->bin_type &&
	       get_type(type)->bin_type <= get_type(isa)->bin_type);
}
