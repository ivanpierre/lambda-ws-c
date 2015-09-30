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
	INODES          = 0,    // All nodes
	INIL            ,       // Constant nil value
	ITRUE           ,       // Constant true value
	IFALSE          ,       // Constant FALSE value
	IINTEGER        ,       // Integer numeric values
	IFRACTION       ,       // Fractional numeric values
	IDECIMAL        ,       // floating numeric values
	ISTRING         ,       // String
	IFUNCTION       ,       // Function pointer
	IWRITER         ,       // Writer implemented in language
	ITYPE           ,       // types
	IUNLINKABLE     ,
	IBOOLEAN        ,
	IINVALID                // Self explaining... used not to go too far... :D
} TYPE;

typedef struct
{
	char        *str_type;
	TYPE        int_type;
	long        bin_type;
	long        size_type;
} Type;

typedef struct
{
	Type        *type;
} NodeType;

extern Type type_array[];

// public function for types
extern long     bin_type        (TYPE type);
extern char     *str_type       (TYPE type);
extern long     size_type       (TYPE type);
extern bool     isa_type        (TYPE type, TYPE isa);
extern Type     *get_type       (TYPE type);

#endif
