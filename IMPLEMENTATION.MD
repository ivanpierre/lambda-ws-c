# Implementation
## Main types
```c
/*
    type of nodes
*/
typedef enum
{
    NIL_NODE        =   1,       // Constant nil value
    TRUE_NODE       =   1 << 2,  // Constant true value
    FALSE_NODE      =   1 << 3,  // Constant false value
    SYMBOL          =   1 << 4,  // Symbol that can be binded in ENVIRONMENT
    KEYWORD         =   1 << 5,  // Constant symbol :key evaluate to itself
    INTEGER         =   1 << 6,  // Integer numeric values
//	FRACTION        =   1 << 7,  // Fractional numeric values
    DECIMAL         =   1 << 8,  // floating numeric values
    STRING          =   1 << 9,  // String
    LIST            =   1 << 10, // reversed array (growing from head)
    ARRAY           =   1 << 11, // ARRAY
    MAP             =   1 << 12, // Mapped array of KEYVAL
    SET             =   1 << 13, // Mapped array of keys
    SEQ             =   1 << 14, // Walker on a collection
    NAMESPACE       =   1 << 15, // Interning place for global symbols
    ENV_STACK       =   1 << 16, // is a list of ENVIRONMENT
    ENVIRONMENT     =   1 << 17, // is a map of nodes, mapped by SYMBOL
    API             =   1 << 18, // is a map of FUNCTION, mapped by args (ARRAY)
    FUNCTION        =   1 << 19, // Function pointer
    LAMBDA          =   1 << 20, // Body of language to evaluate
    VAR             =   1 << 21, // Values of global vars (bind)
//	REF             =   1 << 22, // CSP managed values
//	FUTURE          =   1 << 23, // Asynchronously managed values
//  AGENT           =   1 << 24  // Agent management through messages
    READER          =   1 << 24, // Reader for a syntax
    KEYVAL          =   1 << 25, // Binding of key / values for MAP
    INVALID         =        26,  // Self explaining... used not to go too far... :D

    NUMBER          =   INTEGER | DECIMAL,

    SEQUABLE        =   STRING |        // Walk on string's characters
                        LIST |          // Walk on list's nodes
                        ARRAY |         // Walk on array's nodes
                        MAP |           // Walk on map's keyvals. [key value]
                        SEQ |           // returns itself's ref
                        NAMESPACE |     // Walk on namespace's symbols
                        ENV_STACK       // Walk on binding's environments
                        ENVIRONMENT |   // Walk on environment's bindings as keyvals [symbol value]
                        API |           // Walk on function's implementations as keyval [args function]
                        LAMBDA,          // Walk on body's Nodes

    INDEXED         =   STRING |        // Get char at position
                        ARRAY |         // Get Node at postion
                        KEYVAL,          // 0 = key, 1 = val (kewyval is a tuple of 2)
                        
    MAPPED          =   MAP |
                        SET |
                        NAMESPACE |
                        ENVIRONMENT |
                        API,
} NodeType;  // WIP

```
## Boxing `nodes.c`, `nodes.h`
Every types of AST element have it's own structure. This structure is an implementation detail and can change as 
project evolves. These types are treated, based on the language definition AND on objects needed to the language 
management. Boxing is needed to manage data types as C doesn't do it for us...

All instances of these types are nodes witch will be managed by the allocator.

```c
/*
    Struct of a base node
*/
typedef struct Node
{
    NodeType        type;
    long            occurrences;
#ifdef DEBUG_ALLOC
    struct Node     *previous_node;
    struct Node     *next_node;
#endif
    union
    {
        Integer     integer;
        Decimal     decimal;
        String      string;
        Symbol      *symbol;
        Collection  *coll;
        KeyValue    *keyval;
        Function    *function;
        Env         *env;
        struct Node *atom;
        Reader      *reader;
    } val;
} Node;


```
- [`nodes.c`](src/nodes.c) : contain allocation and general node management.
- [`nodes.h`](src/nodes.h) : gives all structures of nodes and all public management functions.

Ordering of nodes as keys is defined by the comparison function. witch is different from the equality function.
For example 0 is equal to 0.0, but they can both be keys for maps or sets.

## Collections [`collections.c`](src/collections.c)
All collections are stored in an array. With 

- `size`, giving the prensent number of valid nodes of the collection and 
- `max`, giving the number of allocated nodes.

LIST and ARRAY are ordinated node's sequences. List goes backward growing to the head and arrays upward
growing to the tail. Other collections are ordinated by the key order.

LIST and ARRAY are equals if they share the same structure and the equal values for elements.

### LIST 
This is linked list data type. We need it to implement function calls and definitions.

This contains a first element witch is a node and a next element witch should be a LIST or NULL (for list ending). 
This should ensure that all lists are lists and not conses to enable management of lists as arrays.

### ARRAY
Not needed now, but in fact all collections are arrays.

### MAP
Is needed to define data dictionary and environment for functions and lets. Nodes of a map are KEYVALs.

### SET
Sets are maps where keys and values are the same. So it's an array of nodes ordinated by nodes order as keys.

### KEYVAL
Association of keys and values. The are printed as key, values pair as an array if they are not in a map.
 
## Textual values [`strings.c`](src/strings.c)
These are all stored as strings without decoration say :key is stored as the string 'key' as symbol key and 
string "key". But they are not equals, order is first string order and second type order.

### STRING
Hosts the name of symbols,

### SYMBOL
To define symbolic names, function names, argument names.

### KEYWORD
To define symbolic constant names. Keywords evaluate to themselves.

## Functions [`function.c`](src/function.c) and [`env.c`](src/env.c)
They keep track of their arity and their eventual closures. They can have a macro-expansion capability (only at 
read/compile time), and an evaluation of args capability.

- `is_macro` defines if the function is for macro expansion.
- `is special` defines if argument are evaluated before execution.
- `closure` the optional closure environment of the function.
- `args` array of arguments in case of vararg an '&' symbol is the penultimate.
- `next` Other function with other arities. Perhaps a map with args as keys...

### FUNCTION 
To define a call to C functions. These are varargs functions where the function arguments should match the args data.

### LAMBDA
To define LWC functions that should be evaluated under the arguments. Interpreted function.
These are not defined now in the current language definition, but will be used in REPL creation.

### ENVIRONMENT 
Global environment is a mapped collection of symbols with values. If dynamic binding is enabled a dynamic 
environment will stack over it. So there will be two stack, one global on witch every local environment will 
grow, and a local one. Implementation details are still in reflexion...

Calling a function will stack local arguments as a new local stack. Enter in a let block will stack new environment and 
adding bindings. Function creation inner in a local block will keep it's syntactical local environment. Output from 
these blocks will unstack environment.

##Numeric values [`numbers.c`](src/numbers.c)
There is no automatic type enhancement on overflow, but cast to DECIMAL will be done on binary operations with a 
FLOAT value.

### INTEGER
Manage integer values. Implemented as longs

### DECIMAL
Manage floating point values. Implemented as doubles.

## Other elements
### Global [`global.c`](src/global.c)
Here will be stored the core functions of the LWC language. 

This will manage :

- Interaction function with data structure and manage the dispatching to correct functions.
- Special functions witch doesn't evaluate arguments
- Basic macros... well no...
- These function will be accessible by the language

### Reader [`reader.c`](src/reader.c)
The reader will read in the current reader file handler to transform character strings into AST structure. This will 
recognize symbols, numbers. Complementary syntax will be managed by a functional indirection through an array linking
character with specific reader function. For example '(' character with list reader or '[' with array reader.

