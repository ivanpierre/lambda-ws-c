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
const NodeType BNODES           =   -1;                  // all nodes
const NodeType BNIL             =   1l << INIL;          // Constant nil value
const NodeType BTRUE            =   1l << ITRUE;         // Constant true value
const NodeType BFALSE           =   1l << IFALSE;        // Constant FALSE value
const NodeType BSYMBOL          =   1l << ISYMBOL;       // Symbol that can be binded in ENVIRONMENT
const NodeType BKEYWORD         =   1l << IKEYWORD;      // Constant symbol :key evaluate to itself
const NodeType BINTEGER         =   1l << IINTEGER;      // Integer numeric values
const NodeType BFRACTION        =   1l << IFRACTION;     // Fractional numeric values
const NodeType BDECIMAL         =   1l << IDECIMAL;      // floating numeric values
const NodeType BSTRING          =   1l << ISTRING;       // String
const NodeType BLIST            =   1l << ILIST;         // reversed array (growing from head)
const NodeType BARRAY           =   1l << IARRAY;        // ARRAY
const NodeType BMAP             =   1l << IMAP;          // Mapped array of KEYVAL
const NodeType BSET             =   1l << ISET;          // Mapped array of keys
const NodeType BSEQ             =   1l << ISEQ;          // Walker on a sequence
const NodeType BCONS            =   1l << ICONS;         // Walker on two SEQUABLES
const NodeType BLAZY            =   1l << ILAZY;         // Walker on a lazy sequence
const NodeType BNAMESPACE       =   1l << INAMESPACE;    // Interning place for global symbols
const NodeType BENV_STACK       =   1l << IENV_STACK;    // is a list of ENVIRONMENT
const NodeType BENVIRONMENT     =   1l << IENVIRONMENT;  // is a map of nodes; mapped by SYMBOL
const NodeType BAPI             =   1l << IAPI;          // is a map of FUNCTION; mapped by args (ARRAY)
const NodeType BFUNCTION        =   1l << IFUNCTION;     // Function pointer
const NodeType BLAMBDA          =   1l << ILAMBDA;       // Body of language to evaluate
const NodeType BVAR             =   1l << IVAR;          // Values of global vars (bind)
const NodeType BREF             =   1l << IREF;          // CSP managed values
const NodeType BFUTURE          =   1l << IFUTURE;       // Asynchronously managed values
const NodeType BAGENT           =   1l << IAGENT;        // Agent management through messages
const NodeType BREADER          =   1l << IREADER;       // Reader implemented in language
const NodeType BWRITER          =   1l << IWRITER;       // Writer implemented in language
const NodeType BKEYVAL          =   1l << IKEYVAL;       // Binding of key / values for MAP
const NodeType BINVALID         =         IINVALID;      // Self explaining... used not to go too far... :D

const NodeType BNUMBER          =   BINTEGER | BDECIMAL;
const NodeType BNAMED           =   BSYMBOL | BKEYWORD;
const NodeType BITERABLE        =   BLIST | BARRAY | BSEQ;
const NodeType BMAPPED          =   BMAP | BSET;
const NodeType BCOLLECTION      =   BITERABLE | BMAPPED;
const NodeType BSEQUABLE        =   BCOLLECTION | BNIL;
const NodeType BINDEXED         =   BSTRING | BARRAY;
const NodeType BCALLABLE        =   BFUNCTION | BLAMBDA;
const NodeType BUNLINKABLE      =   BNIL | BTRUE | BFALSE;

/*
    String representation of types
*/
static char            *str_types[] =
                            {
                                "node"
                                "nil",
                                "true",
                                "FALSE",
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

