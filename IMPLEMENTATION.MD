# Implementation
## Types
Every types of AST element have it's own structure. This structure is an implementation detail and can change as 
project evolves. These types are treated, based on the language definition AND on objects needed to the language 
management.

All instances of these types are nodes witch will be managed by the allocator.

`nodes.c`: contain allocation and general node management.
`nodes.h`: gives all structures of nodes and all public management functions.

### LIST `collections.c`
This is linked list data type. We need it to implement function calls and definitions.

This contains a first element witch is a node and a next element witch should be a LIST or NULL (for list ending). 
This should ensure that all lists are lists and not conses to enable another management of lists (i.e. arrays)

### ARRAY `collections.c`
Not needed now, but 'ça ne mange pas de pain' ;)

### MAP `collections.c`
Is needed to define data dictionary and environment for functions and lets.

### SET `collections.c`
Sets are maps where keys and values are the same.

### KEYVAL `collection.c`
Association of keys and values, especially in maps

### STRING `strings.c`
Hosts the name of symbols,

### SYMBOL `strings.c`
To define symbolic names, function names, argument names.

### KEYWORD `strings.c`
To define symbolic names, function names, argument names.

### FUNCTION `function.c`
To define a call to a C function. Normally core functions

### LAMBDA `functions.c`
To define an LWC function that should be evaluated. Interpreted function.
These are not defined now in the current language definition, but will be used in REPL creation.

### INTEGER `number.c`
Manage integers. Implemented as longs

### FLOAT `number.c`
Manage integers. Implemented as doubles.

### ENVIRONMENT `env.c`
Global environment is a mapped collection of symbols with values. 

Calling a function will stack global environment and add local arguments.

Enter in a let block will stack last stacked environment and add bindings.

Output from these blocks will unstack environment.

This is for immutable orientation. A mutable implementation should only stack local variables and walk down until root 
to access proper values storage.

## Other elements
### Global
Here will be the core functions of the LWC language. This will manage :

- Interaction function with data structure and manage the dispatching to correct functions.
- Special functions witch doesn't evaluate arguments
- These function will be accessible by the language

### Reader
The reader will read in the current reader file handler to transform character strings into AST structure. This will 
recognize symbols, numbers. Complementary syntax will be managed by a functional indirection through an array linking
 character with specific reader function. For example '(' character with list reader or '[' with array reader.
 
