/****
    Nodes

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include "types.h"

/*
    type of nodes
*/
const NodeType NODES           =   -1;                  // all nodes
const NodeType NIL             =   1l << INIL;          // Constant nil value
const NodeType TRUE            =   1l << ITRUE;         // Constant true value
const NodeType FALSE           =   1l << IFALSE;        // Constant false value
const NodeType SYMBOL          =   1l << ISYMBOL;       // Symbol that can be binded in ENVIRONMENT
const NodeType KEYWORD         =   1l << IKEYWORD;      // Constant symbol :key evaluate to itself
const NodeType INTEGER         =   1l << IINTEGER;      // Integer numeric values
const NodeType FRACTION        =   1l << IFRACTION;     // Fractional numeric values
const NodeType DECIMAL         =   1l << IDECIMAL;      // floating numeric values
const NodeType STRING          =   1l << ISTRING;       // String
const NodeType LIST            =   1l << ILIST;         // reversed array (growing from head)
const NodeType ARRAY           =   1l << IARRAY;        // ARRAY
const NodeType MAP             =   1l << IMAP;          // Mapped array of KEYVAL
const NodeType SET             =   1l << ISET;          // Mapped array of keys
const NodeType SEQ             =   1l << ISEQ;          // Walker on a sequence
const NodeType CONS            =   1l << ICONS;         // Walker on two SEQUABLES
const NodeType LAZY            =   1l << ILAZY;         // Walker on a lazy sequence
const NodeType NAMESPACE       =   1l << INAMESPACE;    // Interning place for global symbols
const NodeType ENV_STACK       =   1l << IENV_STACK;    // is a list of ENVIRONMENT
const NodeType ENVIRONMENT     =   1l << IENVIRONMENT;  // is a map of nodes; mapped by SYMBOL
const NodeType API             =   1l << IAPI;          // is a map of FUNCTION; mapped by args (ARRAY)
const NodeType FUNCTION        =   1l << IFUNCTION;     // Function pointer
const NodeType LAMBDA          =   1l << ILAMBDA;       // Body of language to evaluate
const NodeType VAR             =   1l << IVAR;          // Values of global vars (bind)
const NodeType REF             =   1l << IREF;          // CSP managed values
const NodeType FUTURE          =   1l << IFUTURE;       // Asynchronously managed values
const NodeType AGENT           =   1l << IAGENT;        // Agent management through messages
const NodeType READER          =   1l << IREADER;       // Reader implemented in language
const NodeType WRITER          =   1l << IWRITER;       // Writer implemented in language
const NodeType KEYVAL          =   1l << IKEYVAL;       // Binding of key / values for MAP
const NodeType INVALID         =         IINVALID;      // Self explaining... used not to go too far... :D

const NodeType    NUMBER       =   INTEGER | DECIMAL;
const NodeType    NAMED        =   SYMBOL | KEYWORD;
const NodeType    ITERABLE     =   LIST | ARRAY | SEQ;
const NodeType    MAPPED       =   MAP | SET;
const NodeType    COLLECTION   =   ITERABLE | MAPPED;
const NodeType    SEQUABLE     =   COLLECTION | NIL;
const NodeType    INDEXED      =   STRING | ARRAY;
const NodeType    CALLABLE     =   FUNCTION | LAMBDA;

/*
    String representation of types
*/
static char            *str_types[] =
                            {
                                "node"
                                "nil",
                                "true",
                                "false",
                                "symbol",
                                "keyword",
                                "integer",
                                "fraction",
                                "decimal",
                                "string",
                                "list",
                                "array",
                                "map",
                                "set",
                                "sequence",
                                "cons",
                                "lazy",
                                "namespace",
                                "env_stack",
                                "environment",
                                "api",
                                "function",
                                "lambda",
                                "var",
                                "ref",
                                "future",
                                "agent",
                                "reader",
                                "writer",
                                "keyval",
                                "<invalid type1>",
                                "<invalid type2>",
                                "<invalid type3>",
                                "<invalid type4>",
                                "<invalid type5>"
                            };

/*
   get bitmaped version of node type
*/
NodeType exp_type(enum TYPE type)
{
    return 1l << type - 1;
}

/*
   get type name
*/
char *str_type(enum TYPE type)
{
    return str_types[type];
}

