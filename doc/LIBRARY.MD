library
=======

There's now four libraries
--------------------------

As project evolves it arises that C is really a structured assembler. So it looks better to let it manage the lower level.

### [LWS](LSW.MD) Low level Nodes Library

This library will manage low level elements such as : NUMBERS, STRINGS, FUNCTIONS. This also manage [Garbage Collection](GARBAGE.MD) and Hash codes.

### [PWS](PSW.MD) Polymorphic Nodes library

Tghis library will define type of complex data structures, their functions and their interface definitions. This will enhance basic LIST, ARRAY and MAPs. Here will be managed the [Multithreding](MULTITHREADING.MD)

### [CDWS](CDWS.MD) Complex data Nodes library

Now we are ready to create the complex data types such as PERSISTANT, TRANSIENT and THREADED LIST, SET, MAP, ARRAY, STACK, SEQUENCE, ITERATOR and all base datatypes needed to construct languages.

### [CWS](CWS.MD) Compiler toolbox library

This will be the tool box to generate an intermediate machine code generator (pseudo-code) that should be able to be emulated or compiled.
