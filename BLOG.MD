#BLOG (just what happens)
##04 aug 2015

- Changed function definition, functions will be a map of FUNCTION mapped by argument list characteristics.
- LAMBDA and FUNCTION share the same structure Function.
- The type for a function collection with the same name is API.
- ENVIRONMENT are grouped as a LIST (stack) named ENV_STACK.
- There will be two environment stacks, the global one and the local one. Local one is passed on call to the functions.
- Searches for symbols is done on the local environment witch test global one automatically.
- Local environment is stored in the function if it is defined in a non top context.
- Local environement is passed as argument and push and pop managed by the eval function.
- Local environment shaining pass through closure. Let for example is just a function call.

```
    (let [a va
          b vb]
       body)
```

is the same as

```
	((fn [a b] 
        body) 
       va vb)
```

so the body is evaluated with the fn arguments. And fn evaluation is made with the previous environment witch is
linked to the new local environment.

##03 aug 2015
- [ ] Clarify and precise implementation details.
- [ ] Finalizing previous enhancements. 
- [ ] Functions definition, creation calling.
- [ ] Environments creation and management based on MAP.
- [ ] Reader functions and dispatch functions.
- [ ] TDD functions
- [ ] Begin to test extensively all this stuff.
- Change and precise implementation documentation.
- String representation for types.
- Implementation as Strings for SYMBOL, KEYWORD, STRING.
- Implementation as Array for LIST, ARRAY, MAP and SET.
- Added type KEYVAL for maps key / values bindings.
- Implementation in numbers.c for INTEGER and DECIMAL.

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
- [x] consolidate changes.

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
