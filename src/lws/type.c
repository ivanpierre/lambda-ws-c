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
#include "collection.h"
#include "environment.h"
#include "api.h"
#include "function.h"
#include "var.h"
#include "reader.h"
#include "writer.h"
#include "keyval.h"

/*
	type of nodes
*/
const long BNODES       = -1;                    // all nodes
const long BNIL         = (1l << INIL);          // Constant nil value
const long BTRUE        = (1l << ITRUE);         // Constant true value
const long BFALSE       = (1l << IFALSE);        // Constant FALSE value
const long BSYMBOL      = (1l << ISYMBOL);       // Symbol that can be binded in ENVIRONMENT
const long BKEYWORD     = (1l << IKEYWORD);      // Constant symbol :key evaluate to itself
const long BINTEGER     = (1l << IINTEGER);      // Integer numeric values
const long BFRACTION    = (1l << IFRACTION);     // Fractional numeric values
const long BDECIMAL     = (1l << IDECIMAL);      // floating numeric values
const long BSTRING      = (1l << ISTRING);       // String
const long BLIST        = (1l << ILIST);         // reversed array (growing from head)
const long BARRAY       = (1l << IARRAY);        // ARRAY
const long BMAP         = (1l << IMAP);          // Mapped array of KEYVAL
const long BSET         = (1l << ISET);          // Mapped array of keys
const long BSEQ         = (1l << ISEQ);          // Walker on a sequence
const long BCONS        = (1l << ICONS);         // Walker on two SEQUABLES
const long BLAZY        = (1l << ILAZY);         // Walker on a lazy sequence
const long BNAMESPACE   = (1l << INAMESPACE);    // Interning place for global symbols
const long BENV_STACK   = (1l << IENV_STACK);    // is a list of ENVIRONMENT
const long BENVIRONMENT = (1l << IENVIRONMENT);  // is a map of nodes); mapped by SYMBOL
const long BAPI         = (1l << IAPI);          // is a map of FUNCTION); mapped by args (ARRAY)
const long BFUNCTION    = (1l << IFUNCTION);     // Function pointer
const long BLAMBDA      = (1l << ILAMBDA);       // Body of language to evaluate
const long BVAR         = (1l << IVAR);          // Values of global vars (bind)
const long BREF         = (1l << IREF);          // CSP managed values
const long BFUTURE      = (1l << IFUTURE);       // Asynchronously managed values
const long BAGENT       = (1l << IAGENT);        // Agent management through messages
const long BREADER      = (1l << IREADER);       // Reader implemented in language
const long BWRITER      = (1l << IWRITER);       // Writer implemented in language
const long BTYPE        = (1l << ITYPE);         // Type of nodes
const long BKEYVAL      = (1l << IKEYVAL);       // Binding of key / values for MAP
const long BINVALID     = IINVALID;              // Self explaining... used not to go too far... :D

const long BNUMBER     = BINTEGER | BDECIMAL;
const long BNAMED      = BSYMBOL | BKEYWORD;
const long BITERABLE   = BLIST | BARRAY | BSEQ;
const long BMAPPED     = BMAP | BSET;
const long BCOLLECTION = BITERABLE | BMAPPED;
const long BSEQUABLE   = BCOLLECTION | BNIL;
const long BINDEXED    = BSTRING | BARRAY;
const long BCALLABLE   = BFUNCTION | BLAMBDA;
const long BUNLINKABLE = BNIL | BTRUE | BFALSE | BTYPE;

/*
	Representation of types
*/
Type type_array[] = {{"Node",       INODES,         BNODES, 0},
					{"Nil",         INIL,           BNIL, 0},
					{"True",        ITRUE,          BTRUE, 0},
					{"False",       IFALSE,         BFALSE, 0},
					{"Symbol",      ISYMBOL,        BSYMBOL, sizeof(Named)},
					{"Keyword",     IKEYWORD,       BKEYWORD, sizeof(Named)},
					{"Integer",     IINTEGER,       BINTEGER, sizeof(Integer)},
					{"Fraction",    IFRACTION,      BFRACTION, 0},
					{"Decimal",     IDECIMAL,       BDECIMAL, sizeof(Decimal)},
					{"String",      ISTRING,        BSTRING, sizeof(String)},
					{"List",        ILIST,          BLIST, sizeof(Collection)},
					{"Array",       IARRAY,         BARRAY, sizeof(Collection)},
					{"Map",         IMAP,           BMAP, sizeof(Collection)},
					{"Set",         ISET,           BSET, sizeof(Collection)},
					{"Seq",         ISEQ,           BSEQ, 0},
					{"Cons",        ICONS,          BCONS, 0},
					{"Lazy",        ILAZY,          BLAZY, sizeof(Named)},
					{"Namespace",   INAMESPACE,     BNAMESPACE, 0},
					{"EnvStack",    IENV_STACK,     BENV_STACK, 0},
					{"Environment", IENVIRONMENT,   BENVIRONMENT, sizeof(Environment)},
					{"Api",         IAPI,           BAPI, sizeof(Api)},
					{"Function",    IFUNCTION,      BFUNCTION, sizeof(Function)},
					{"Lambda",      ILAMBDA,        BLAMBDA, sizeof(Function)},
					{"Var",         IVAR,           BVAR, sizeof(Var)},
					{"Ref",         IREF,           BREF, 0},
					{"Future",      IFUTURE,        BFUTURE, 0},
					{"Agent",       IAGENT,         BAGENT, 0},
					{"Reader",      IREADER,        BREADER, sizeof(Reader)},
					{"Writer",      IWRITER,        BWRITER, sizeof(Writer)},
					{"Type",        ITYPE,          BTYPE, sizeof(NodeType)},
					{"Keyval",      IKEYVAL,        BKEYVAL, sizeof(KeyVal)},
					{"Invalid",     IINVALID,       BINVALID, 0}};

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
	return get_type(type)->bin_type & get_type(isa)->bin_type &&
	       get_type(type)->bin_type <= get_type(isa)->bin_type;
}

