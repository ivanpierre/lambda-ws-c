#GOALS
## Goals list
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
