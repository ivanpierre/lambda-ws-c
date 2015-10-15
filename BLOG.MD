BLOG (just what happens)
========================

#### 15 Oct 2015

Type vision is bashed... alas a first pass through an object interface to construct the base seems unavoidable.

Big question... is it an awfull OOP bias and an laziness outrage, or is it a necessary layer.

I know, it's not necessary to make a lisp, but when you want to keep interoperability possible...

Still wondering....

#### 14 Oct 2015

Still on the boat even if lot of work outside...

#### 03 Oct 2015

As modification arise and change of structure become obvious the whole doc should be rewritten... For now it's only interesting as historical sources.

#### 28 Sept 2015

Problem found in the new GC version. If arguments are not linked to a new temporary variable error catching will badly unlinks nodes nodes. If there's an error on the first argument, the second will be unlinked and the count will not correctly match... shit... :(

#### 28 Sept 2015

A lot of reflexions and test around arising problems.

-	Hard to manage global naming and reconciling various function names in one name for various data types and arities...
-	Would be nice to manage it with the resulting library, but we don't have it.
-	We need polymorphism, but tools are not here.
-	But our current GC system works.
-	Treading is puting it's feets in... and that's bad (for now)

##### Current search option

-	Hash maps with keyword style keying (set of unique string).
-	Enable to use it to define complex data structures, sort of OO, but based on interface not on inheritance.
-	How to define related data in interfaces?
-	Base node are nice for now, functions should be usable as is.
-	Think about it an onions, with simple layers to more complex one and step across ;)
-	Perhaps a library by layer, good way to test layer way.
	-	LWS as only base elements : numerics, string, but no symbols, arrays, etc
	-	PWS (polymorphic WS) to add the polymorphic way to link data and polymorphic and multiarity methods. This through specific and efficient persistent maps
	-	CBDWS (Complex Base Datatypes WS) So now we can go where we have to... maps, symbols, etc...

For now change and dispatch to the new directories, and begin to write the new changes ;)

Lot of work...

#### 22 Sept 2015

Re-rewriting of allocation process. All functions link arguments and unlink them at the end, except constructor witch unlink_new them to let them have an occurences count of 0. The goal is to discard them if they are used in a function when not linked elsewhere. Going to the process to add Hash code management for Nodes. Adding Murmur3 functions. Modifying function argument specification to argcount (mandatory ones) and a vararg boolean.

#### 07 sept 2015

Ok, big tests and rewrites on allocation problems. I'll manage the explanations on[GABAGE.MD](GARBAGE.MD). It begins to seem obvious, but it's not a simple problem. In fact, it's simple but sooooo long time we have the habit to have one's own garbage collector, we don't even think about allocation problems :D

On the other side string representation of object is primary and not a Node ISTRING representation... else it goes to awful loops on creating objects, especially for debug purposes... :D

#### 24 aug 2015

Core functions will have this general format :

`Node *func([Node *arg [, arg2...]])`

These function will be directly linked to the Function nodes. Some function will have non Node arguments, but they will be only called internally, like string, number, function constructors.

Rewriting and adapting the whole thing.

Adding Type structure and Node. So all the internal bakery in encapsulated in it.

Problems with GitHub... :( OK, t'was only a missed push...

#### 23 aug 2015

Testing various data models. Big problem, ensure that all bind Node will be traced.

Nodes will be bind :

-	To a C variable : link_node of Node. NO direct assignment. Bound variables will be unbound in the same function.
-	To an argument of function : Function will bind and unbind arguments.
-	To a Namespace : this will be the DEF function.
-	To a closure, this will be made in the APPLY function

#### 22 aug 2015

Completely missed the point too complicated and overwhelming code. I finish current version and should begin a new one from scratch. Begin to modify data model.

#### 21 aug 2015

Tests on collections.

-	Missing allocation on creation.
-	Ok empty list, array, map, set + print.
-	Adding error.c & .h for assertions and texts.
-	Adding type.c, .h, error.c, .h

Change in allocation deallocation mode.

For every node creation, link, and unlink the address of a variable should be given. This is reasonable as every node value should be bond to something... Unallocation or allocation on a bound value should deallocate value and ensure the variable is set to NULL before any action as new allocation... So we insure that there will not be any dandling node hanging somewhere... such as passing a constructor result as argument...

A new ASSERT_ALLOC error helper will make a `goto error_assert;` to proceed with clean-up. All failing assertion will also do the same ensuring that any failing assertion will do intended clean-ups.

All ERROR() should be replaced by an ABORT...

#### 20 aug 2015

Symbol OK. But it gives some problem in the way to be sure that all object creation and deletion will be matched. Hammock design... :D Should continue tests...

#### 18 aug 2015

-	[X] Don't close stdout and stderr. It really close them... :D
-	[X] Complete review of writer for allocations and unallocations.
-	[X] Bad thought, function doesen't unalloc arguments, only temporary values used to proceed with its functions. Assigning a node to a variable mean we link it. And end of scope for this variable means that we unlink it.
-	[X] Generalize TRACE function for debugging reasons.
-	[X] write_string and write_formated FALSE unallocation of string.
-	[X] nil, true, FALSE OK
-	[X] Missing allocation of named in named_base.
-	[X] GET_STRING return a duplicate of the string, as this is a reference that is quite always unallocated.

#### 17 aug 2015

-	[X] Closing the writer and release ressources.
-	[X] Adding stdout and stderr.
-	[X] Decimal memory leak.
-	[X] String desallocated 2 times :(
-	[X] Closing writer keep old config...

#### 17 aug 2015

Ok, that was a little painful to manage all the different stuff. Now as it's a little stabilized, we proceed to the first exhaustive test on all the AST elements. Especially tracing memory leaks. As we have a stack printing function, it's possible to monitor activities. Some points to overview.

-	All free function should completely clean up the whole mess.
-	Output should be managed too.
-	As soon as possible put the environment active to write the first functions.
-	A tinming function should be put in place to see everwhelmig usage of ressouces.
-	as soon it's done, proceed with the writing of tzhe core functions and write a repl.

#### 10 aug 2015

-	Reformat all names of structure source.e, each one manage a structure.
-	A header should be created for public access functions
-	PRINT, EVAL, FREE, READ will be managed through a function pointer, so it can be enhanced a an upper level. Specific functions will be forwarded hardcoded way and not through header. We should only use PRINT(node), EVAL(node), and not the function specific to the structures.
-	At language level all specific functions will be overloaded if needed...

#### 06 aug 2015

-	Split source into AST library and language implementation.
-	Simplifying Node definition.

#### 04 aug 2015

-	Separate STRING et SYMBOL, new [symbol.c\`](src/lws/namned.c) for keywords and symbols.
-	Adding evaluation functions.
-	Adding NAMESPACE.
-	ATOM is deprecated split into VAR, REF, FUTURE... [`atom.c`](src/lws/atom.c) get the management.
-	Changed function definition, functions will be a map of FUNCTION mapped by argument list characteristics.
-	LAMBDA and FUNCTION share the same structure Function.
-	The type for a function collection with the same name is API.
-	ENVIRONMENT are grouped as a LIST (stack) named ENV_STACK.
-	There will be two environment stacks, the global one and the local one. Local one is passed on call to the functions.
-	Searches for symbols is done on the local environment witch test global one automatically.
-	Local environment is stored in the function as a closure if it is defined in a non top context.
-	Local environment is passed as argument and push and pop managed by the FUNCTION eval function.
-	Local environment chaining pass through closure. Let for example is just a function call.

```clj
    (let [a va
          b a]
       body)
```

is the same as

```
    ((fn [a b] ; fn do the evaluation of args, so the [a b] is accessible while
        body)  ; evaluating va and a, so b is bind to a bind to the evaluation of va.
       va a)
```

so the body is evaluated with the fn arguments. And fn evaluation is made with the previous environment witch is linked to the new local environment.

#### 03 aug 2015

-	Clarify and precise implementation details.
-	Finalizing previous enhancements.
-	Functions definition, creation calling.
-	Environments creation and management based on MAP.
-	Reader functions and dispatch functions.
-	TDD functions
-	Begin to test extensively all this stuff.
-	Change and precise implementation documentation.
-	String representation for types.
-	Implementation as Strings for SYMBOL, KEYWORD, STRING.
-	Implementation as Array for LIST, ARRAY, MAP and SET.
-	Added type KEYVAL for maps key / values bindings.
-	Implementation in numbers.c for INTEGER and DECIMAL.

#### 30 jul 2015

Ok, `glib` is a nice library. But I will go with the idea of writing the whole with standard lib.

In fact glib is a big boilerplate, ant it's hard to get some bite from it w/o the rest. And even is you link with some flags, there's still a big monster in the backyard ;)

So for compatibilty sake, I'll write the data structure mess, I anyway need to have, not only but first to have an environment to grab bindings in...

#### 29 jul 2015

-	[x] Change node structure as value is an union to ease the data access.
-	[x] Change list as an array access
-	[x] Put all structures definitions in node.c
-	[x] Suppress unnecessary sources : map.*, array.*, list.*, symbol.*
-	[x] Add collection.* to manage array, map, list, set
-	[x] Add set type.
-	[x] All function and data definitions for structures are in node.h
-	[x] Numbers are now managed by numbers.c
-	[x] consolidate changes.

#### 28 jul 2015

Some changes in view.

-	[0] Use of glib library for ARRAY, MAP and SET. It will be easier doesn't change the problem a lot. Just unifies the management of collection of objects. abandon, boiler plate
-	[x] Suppress the Type type. No real usage, these functions will be in global.c and so will be more managable than specific data type that can change. They will accept all data types and if not managed give an appropriate error message.
-	[x] Going to unify the structures functions names. So global function will be easier to manage.
-	[x] Create a new node .c and .h. With a structure embedding the whole other structures. SO NODE macro will have no sense anymore.
-	[x] Update doc... perpetual mobile.... ;)

This should greatly simplify the code and enable a better journey.

#### Started 28 Jul 2015

CC licence
