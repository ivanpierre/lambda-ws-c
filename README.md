# lambda-ws-c
Lambda Calculus Workshop in C

## Introduction
This is result of the workshop of Functional Romandie the 16/07/2015. 
You can see the github https://github.com/FunctionalRomandie/LambdaCalculusWorkshop.

## Goals
- A simple AST for a defined language. Let's call it LWC
- An interpreter on this AST.
- A reader to generate AST data in order to execute language code.
- A writer to be able to output AST data and program result in a readable form.
- A simple REPL probably implemented in the language itself.

You can see the [blog](BLOG.MD) to see advance... ;)

## Issues
As the program is written in C, I'll try to only use the language and the standard library. This mean that all
data structures of LWC should be created. 

This means too that a garbage collector should be written. C memory management is too messy to be used as is.
The memory management should be included in AST inner implementation so LSC user doesn't hate to bother with
these type of problem. Memory fragmentation is not taken in account for now.

AST of LWC should be implementation agnostic, so that public function should not have usage change even if inner 
structure drastically changes. Inner structure of data and even size and so on are not public. the only thing we'll 
have acces on nodes are the type. only management functions will be public. More, lot of core function will receive 
pointer to data and manage the type by themself completely putting out the inner structure to the user.

Language elements should be as decoupled from AST element types as possible. It should give the less work as 
possible to change language definition and syntax. So a lot of non defined core language functions should be 
implemented. These are base functions that enable to manage AST objects.

Based on this, internal representation of the AST should be defined WITH AST elements, so LWC can be completely 
implementation agnostic, even on thanguage used to implement it :D

For now threading will not be managed.

## Opinionated language
- Optimisation is a secondary goal, first implement correctly 
- Immutable data is a goal, temporary it can be mutable in implementation, but data should be manipulated as if it 
was the case. It should be an implementation detail.
- Data reutilisation should be a goal, but we first put data as is. It will be implemented afterward. It should be an
 implementation detail too.
- functions are first class citizens, so they are stored as symbol the same way as other variables.

## Implementation
### Types
Every types of AST element have it's own structure. This structure is an implementation detail and can change as 
project evolves. These types are treated, based on the language definition AND on objects needed to the language 
management.

All instances of these types are nodes witch will be managed by the allocator.

#### TYPE
Definition of an AST type. These will give :
- The name of the AST type
- Equality test
- Ordering function if the type is ordered
- Evaluation function if evaluation is different from itself
- Deallocation function if more nodes can be linked to the current node.
- Representation function to be able to output it's representation as a readable string

#### LIST
This is linked list data type. We need it to implement function calls and definitions.

This contains a first element witch is a node and a next element witch should be a LIST or NULL (for list ending). 
This should ensure that all lists are lists and not conses to enable another management of lists (i.e. arrays)

#### ARRAY
Not needed now, but 'ça ne mange pas de pain' ;)

#### MAP
Is needed to define data dictionary and environment for functions and lets.

#### SYMBOL
To define symbolic names, function names, argument names.

#### FUNCTION
To define a call to a C function, with argument evaluation. Normal core functions

#### LAMBDA
To define an LWC function that should be evaluated, with argument evaluation. Normal interpreted function.
These are not defined now in the current language definition, but will be used in REPL creation.

#### SPECIAL
To define a call to a C function, without argument evaluation. For exemple `let` should not evaluate the local to 
be defined.

#### STRING
Hosts the name of symbols,

#### INT
Manage integers. Implementation detail.

### Garbage collector
This part has been completely reworked. The previous version of GC was completely overwhelming and didn't resolve the
segmentation of allocated data problem. So get rid of a separated garbage collector. This one should have an 
addressing indirection to the data segments, witch should be managed in a contiguous memory allocation with free 
continuous segments lists and so on... so keep that as implementation details.

#### Nodes
Now nodes contains the number of links it manages. There is an option to manage an allocated node list witch is 
updated when allocation or deallocation occurs. This process is for debugging purposes only, so the program can be 
compiled with or without it with no more convenient problems than change of a constant definition. The debugging 
implementation only add a previous and next link to every nodes and call to appropriate management for allocation 
and desallocation.

Identity of pointers is when two nodes have the same address. Equality is managed by the types through the `equals` 
function pointer.

#### linking and unlinking
Every node that is used in some process should be linked to avoid it to be deallocated, and unlinked when no more in 
use. Link and unlink should be done in a same function to avoid memory leaks of bad memory management. The only way 
not to unlink it is when the node is linked to a persistent value, generally to an environment interning or if used 
by another node (i.e. lists, array, map, ...) Types manage the release of memory through the `free` function pointer.

The allocation is done by the constructor of each types, arguments for it depends on the type.

There is only three values that are never linked or unlinked : NIL, TRUE and FALSE. They are equal to themselves.
NIL and FALSE are false boolean values, FALSE is here for disambiguating NIL values than can be pertinent return 
values. 

### Reader
The reader will read in the current reader file handler to transform character strings into AST structure. This will 
recognize symbols, numbers. Complementary syntax will be managed by a functional indirection through an array linking
 character with specific reader function. For example '(' character with list reader or '[' with array reader.
 
### Writer
The writer return string version of the nodes. It is managed by the node type itself. Through the `print` function 
pointer.

### Environment
Global environment is a mapped collection of symbols with values. 

Entry in a function will stack global environment and add local arguments.

Entry in a let block will stack last stacked environment and add bindings.

Output from these blocks will unstack environment.

This is for immutable orientation. A mutable implementation should only stack local variables and walk down until root 
to access proper values storage.

## Language definition for now
Should manage

	(add (lit 21)(lit 21))
ou

	add(lit(21),lit(21))

et

	(let
		(bind x (lit 21))
		(add x (lit 21)))

Well, as reader should recognize numbers, there's no need of (lit INTEGER) AST will be created accordingly.
And binding could be created as an associative map giving first argument of let the binding that will be added to 
local environment.

So giving in language :
	
	(add 21 21)
	
and

	(let {x 21} (add x 21))
	
witch will be translated internally as AST

	(LIST
		(SYMBOL add)
		(LIST
			(INTEGER 21)
			(LIST
				(INTEGER 21)
				NIL)))
				
and

	(LIST
		(SYMBOL let)
		(LIST 
			(LIST 
				(SYMBOL x)
				(LIST
					(INTEGER 21)
					NIL))
			(LIST
				(LIST
					(SYMBOL add)
					(LIST 
						(SYMBOL x)
						(LIST
							(INTEGER 21)
							NIL)))
				NIL)))
			
			
I think I should rename LIST as CONS cells, or store them as arrays... ;)

as arrays it would give :

	(LIST 3
		(SYMBOL let)
		(LIST 2
			(SYMBOL x) 
			(INTEGER 21))
		(LIST 3
			(SYMBOL add)
			(SYMBOL x)
			(INTEGER 21)))

But all that is implementation details :D

As an issue. defining binding as a map doesn't guarantee order of bindings, as values can be any nodes. So it's 
probably better to define them as array or as list, so evaluation will be ordinated.

## And now what ?
For any question or issue you can write to me on twitter @ivanpierre. It's currently a WIP.

But as I have to manage all the data types to begin to put just a function call with a symbol in environment, I 
finish to have a complete functional language. Well this was the goal, as programming a functional language with a 
functional language is ways to easy ;)

Well, it will be when all the data types will be implemented.

But the BIG difficulty, is managing the memory, when we don't have an embedded garbage collector... :D

## Licence
For now Eclipse Public License - v 1.0
