#BLOG (just what happens)
##30 jul 2015
Ok, `glib` is a nice library. But I will go with the idea of writing the whole with standard lib.

In fact glib is a big boilerplate, ant it's hard to get some bite from it w/o the rest. And even is you link with 
some flags, there's still a big monster in the backyard ;)

So for compatibilty sake, I'll write the data structure mess, I anyway need to have, not only but first to have an 
environment to grab bindings in...

##29 jul 2015
- [x] Change node structure as value is an union to ease the data access.
- [x] Change list as an array access
- [x] Put all structures definitions in node.c
- [x] Suppress unnecessary sources : map.*, array.*, list.*, symbol.*
- [x] Add collection.* to manage array, map, list, set
- [x] Add set type.
- [x] All function and data definitions for structures are in node.h
- [x] Numbers are now managed by numbers.c
- [ ] consolidate changes.

##28 jul 2015
Some changes in view.

- [0] Use of glib library for ARRAY, MAP and SET. It will be easier doesn't change the problem a lot. Just unifies the 
management of collection of objects. abandon, boiler plate
- [x] Suppress the Type type. No real usage, these functions will be in global.c and so will be more managable than 
specific 
data type that can change. They will accept all data types and if not managed give an appropriate error message.
- [x] Going to unify the structures functions names. So global function will be easier to manage.
- [x] Create a new node .c and .h. With a structure embedding the whole other structures. SO NODE macro will have no 
sense anymore.
- [x] Update doc... perpetual mobile.... ;)

This should greatly simplify the code and enable a better journey.

##Started 28 Jul 2015

CC licence
