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
	INIL            = 1,    // Constant nil value
	ITRUE           = 2,    // Constant true value
	IFALSE          = 3,    // Constant FALSE value
	ISYMBOL         = 4,    // Symbol that can be binded in ENVIRONMENT
	IKEYWORD        = 5,    // Constant symbol :key evaluate to itself
	IINTEGER        = 6,    // Integer numeric values
	IFRACTION       = 7,    // Fractional numeric values
	IDECIMAL        = 8,    // floating numeric values
	ISTRING         = 9,    // String
	ILIST           = 10,   // reversed array (growing from head)
	IARRAY          = 11,   // ARRAY
	IMAP            = 12,   // Mapped array of KEYVAL
	ISET            = 13,   // Mapped array of keys
	ISEQ            = 14,   // Walker on a sequence
	ICONS           = 15,   // Walker on two SEQUABLES
	ILAZY           = 16,   // Walker on a lazy sequence
	INAMESPACE      = 17,   // Interning place for global symbols
	IENV_STACK      = 18,   // is a list of ENVIRONMENT
	IENVIRONMENT    = 19,   // is a map of nodes, mapped by SYMBOL
	IAPI            = 20,   // is a map of FUNCTION, mapped by args (ARRAY)
	IFUNCTION       = 21,   // Function pointer
	ILAMBDA         = 22,   // Body of language to evaluate
	IVAR            = 23,   // Values of global vars (bind)
	IREF            = 24,   // CSP managed values
	IFUTURE         = 25,   // Asynchronously managed values
	IAGENT          = 26,   // Agent management through messages
	IREADER         = 27,   // Reader implemented in language
	IWRITER         = 28,   // Writer implemented in language
	ITYPE           = 29,   // types
	IKEYVAL         = 30,   // Binding of key / values for MAP
	IINVALID        = 31,   // Self explaining... used not to go too far... :D
	INUMBER         = 32,   // Numbers all
	INAMED          = 33,   // Symbols
	IITERABLE       = 34,   // Taking next
	IMAPPED         = 35,   // Maps and sets
	ICOLLECTION     = 36,   // All collections
	ISEQUABLE       = 37,   // Can be sequed
	IINDEXED        = 38,   // STRING and arrays
	ICALLABLE       = 39,   // Function of lambda
	IUNLINKABLE     = 40    // Can't be linked
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


// public function for types
extern long     bin_type        (TYPE type);
extern char     *str_type       (TYPE type);
extern long     size_type       (TYPE type);
extern bool     isa_type        (TYPE type, TYPE isa);
extern Type     *get_type       (TYPE type);

#endif
