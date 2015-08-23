/****
    types

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef TYPE_H
#define TYPE_H

/*
    type of nodes we only export composet types
*/
#define NodeType    long        // on 8 bytes, 64 bits
extern const NodeType    BNUMBER;
extern const NodeType    BNAMED;
extern const NodeType    BITERABLE;
extern const NodeType    BCOLLECTION;
extern const NodeType    BSEQUABLE;
extern const NodeType    BINDEXED;
extern const NodeType    BMAPPED;
extern const NodeType    BCALLABLE;
extern const NodeType    BUNLINKABLE;

/*
    type of nodes
*/
typedef enum TYPE
{
    INIL             =   1,  // Constant nil value
    ITRUE            =   2,  // Constant true value
    IFALSE           =   3,  // Constant FALSE value
    ISYMBOL          =   4,  // Symbol that can be binded in ENVIRONMENT
    IKEYWORD         =   5,  // Constant symbol :key evaluate to itself
    IINTEGER         =   6,  // Integer numeric values
    IFRACTION        =   7,  // Fractional numeric values
    IDECIMAL         =   8,  // floating numeric values
    ISTRING          =   9,  // String
    ILIST            =   10, // reversed array (growing from head)
    IARRAY           =   11, // ARRAY
    IMAP             =   12, // Mapped array of KEYVAL
    ISET             =   13, // Mapped array of keys
    ISEQ             =   14, // Walker on a sequence
    ICONS            =   15, // Walker on two SEQUABLES
    ILAZY            =   16, // Walker on a lazy sequence
    INAMESPACE       =   17, // Interning place for global symbols
    IENV_STACK       =   18, // is a list of ENVIRONMENT
    IENVIRONMENT     =   19, // is a map of nodes, mapped by SYMBOL
    IAPI             =   20, // is a map of FUNCTION, mapped by args (ARRAY)
    IFUNCTION        =   21, // Function pointer
    ILAMBDA          =   22, // Body of language to evaluate
    IVAR             =   23, // Values of global vars (bind)
    IREF             =   24, // CSP managed values
    IFUTURE          =   25, // Asynchronously managed values
    IAGENT           =   26, // Agent management through messages
    IREADER          =   27, // Reader implemented in language
    IWRITER          =   28, // Writer implemented in language
    IKEYVAL          =   29, // Binding of key / values for MAP
    IINVALID         =   30  // Self explaining... used not to go too far... :D
} TYPE;

typedef struct Type
{
    Node        *symbol;
    TYPE        itype;
    NodeType    btype;
} Type;

// public function for types
char *      str_type(enum TYPE type);
char *      str_btype(NodeType type);
NodeType    exp_type(enum TYPE type);

#endif
