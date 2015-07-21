# lambda-ws-c
Lambda Calculus Workshop in C

## Introduction
This is result of the workshop of Functional Romandie the 16/07/2015. 
You can see the github https://github.com/FunctionalRomandie/LambdaCalculusWorkshop.

## Goals
- A simple AST for a defined language. Let's call it LWC
- An interpreter on this AST.
- A reader to generate AST data in order to execute language code.
- A writer to be able to output AST data and program result.
- A simple REPL probabely implemented in the language itself.

## Issues
As the program is written in C, I'll try to only use the language and the standard library. This mean that all
data structures of LWC should be created. 

This mean too that a garbage collector should be written. C memory managent is too messy to be used as is.
The memory management should be included in AST inner implementation so WSC user doesn't hate to bother with
these type of problem.

AST of WSC should be implementation agnostic, so that public function should not have usage change even if inner 
structure drastically changes.

Language elements should be as decoupled from AST element types as possible. It should give the less work as 
possible to change language definition and syntax. So a lot of non defined core language functions should be 
implemented. These are base functions that enable to manage AST objects.

Based on this, internal representation of the AST should be defined WITH AST elements, so WSC can be completely 
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

All instances of these types are nodes witch will be managed by the garbage collector. The only data that will not be
 nodes will be the garbage collector itself...

#### TYPE
Definition of an AST type. These will give :
- The name of the AST type
- Equality test
- Ordering function if the type is ordered
- Evaluation function if evaluation is different from itself
- Representation function to be able to output it's representation as a readable string

#### LIST
This is linked list data type. We need it to implement function calls and definitions.

This contains a first element witch is a node and a next element witch should be a LIST or NULL (for list ending).

#### ARRAY
Not needed now, but 'ça ne mange pas de pain' ;)

#### MAP
Is needed to define data dictionary and environment for functions and lets.

#### SYMBOL
To define symbolic names, function names, argument names.

#### FUNCTION
To define a call to a C function, with argument evaluation. Normal core functions

#### LAMBDA
To define an WSC function that should be evaluated, with argument evaluation. Normal interpreted function.
These are not defined now in the current language definition, but will be used in REPL creation.

#### SPECIAL
To define a call to a C function, without argument evaluation. For exemple `let` should not evaluate the local to 
be defined.

#### STRING
Hosts the name of symbols,

#### INT
Manage integers. Implementation detail.

### Garbage collector
These elements will manage garbage collection.

#### Segments
Every node is linked to a segment witch contains a reference count ofnodes references enabling to free node when no 
more reference is present.

These segment are stored in memory chunks.

#### Chunks
Chunks are fixed arrays of segments. Chunks count the number of allocated segments. One particular segment is the 
last one where every node creation will have a new segment added.

#### GC
Main garbage collector. It will contains function for nodes allocation, deallocation, link and unlink. It will also 
contain a linked link of memory chunks, with first as the last chunk. At some time if two chunks (except the last) have
a number of segmentequal to a chunk size, the both are compackter un a chunk added to the list and old ones are 
deallocated.

#### linking and unlinking
Every node that is used in some process should be linked in garbage collector to avoid it to be deallocated, and 
unlinked when no more in use. Link and unlink should be done in a same function to avoid memory leaks of bad memory 
management. The only way not to unlink it is when trhe node is linked to a persistent value, generally to an 
environment interning.

### Reader
The reader will read in the current reader file handler to transform character strings into AST structure. This will 
recognize symbols, numbers. Complementary syntax will be managed by a functional indirection through an array linking
 character with specific reader function. For example '(' character with list reader or '[' with array reader.
 
### Writer
The writer will sent to the current output. Character representation will be managed by the node type itself.

### Environment
Global environment is a mapped collection of symbols with values. 

Entry in a function will stack global environment and add local arguments.

Entry in a let block will stack last stacked environment and add bindings.

Output from these blocks will unstack environment.

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
		(SYMBOL ADD)
		(LIST
			(INTEGER 21)
			(LIST
				(INTEGER 21)
				NULL)))
				
and

	(LIST
		(SPECIAL LET)
		(LIST 
			(MAP 1
				(SYMBOL X) 
				(INTEGER 21))
			(LIST
				(LIST
					(SYMBOL ADD)
					(LIST 
						(SYMBOL X)
						(LIST
							(INTEGER 21)
							NULL)))
				NULL)))
			
			
I think I should rename LIST as CONS cells, or store them as arrays... ;)

as arrays it would give :

	(LIST 3
		(SPECIAL LET)
		(MAP 1
			(SYMBOL X) 
			(INTEGER 21))
		(LIST 3
			(SYMBOL ADD)
			(SYMBOL X)
			(INTEGER 21)))

But all that is omplementation details :D

## An now what ?
For any question or issue you can write to me on twitter @ivanpierre. It's currently a WIP.

## Licence
For now Eclipse Public License - v 1.0