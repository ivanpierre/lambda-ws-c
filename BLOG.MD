#BLOG (just what happens)
##29 juil 2015
- [x] Change node structure as value is an union to ease the data access.
- [x] Change list as an array access
- [x] Put all structures definitions in node.c
- [x] Suppress unnecessary sources : map.*, array.*, list.*, symbol.*
- [x] Add collection.* to manage array, map, list, set
- [x] Add set type.
- [x] All function and data definitions for structures are in node.h
- [x] Numbers are now managed by numbers.c
- [ ] consolidate changes.

##28 juil 2015
Some changes in view.

- [ ] Use of glib library for ARRAY, MAP and SET. It will be easier doesn't change the problem a lot. Just unifies the 
management of collection of objects.
- [x] Suppress the Type type. No real usage, these functions will be in global.c and so will be more managable than 
specific 
data type that can change. They will accept all data types and if not managed give an appropriate error message.
- [x] Going to unify the structures functions names. So global function will be easier to manage.
- [x] Create a new node .c and .h. With a structure embedding the whole other structures. SO NODE macro will have no 
sense anymore.
- [ ] Update doc...

This should greatly simplify the code and enable a better journey.

##Started 28 Juil 2015

CC licence
