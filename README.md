lambda-ws-c
===========

Project evolved a lot and goes in another direction... so documentation is to be completely rewritten...

Ideas
-----

Define all data elements of a language. They will be bricks for any AST system. The whole in C.

Immutability is the key. But mutable object should be accessible through protected thread access. all elements from bit to complex structures will be seen as a Node. Every Node is a specific datatype with it's own management functions. All these should enable to construct any possible data structures.

Especially it should enable to create evaluatable Nodes as algorithmic units corresponding to languages specific implementations. These nodes should be readable in a syntax defined by the languages and writable as language source of machine code functions. Simple evaluation of these nodes should provide emulation of execution of the corresponding machine code generation.

These nodes should be able to manage all nodes giving the ability to make a language grow by successive layers, giving to every layer the ability to construct the next one.

### Threading

threads will be managed by nodes by usage of mutex (equivatent of Java synchronize).

### base_nodes library.

This library will manage all the base simple Nodes.

Base `Node` hold the `TYPE` enum id.

Every nodes are tracked and managed so unreferenced Nodes will be discarded from memory.

Basic data elements bricks.

-	`CONST` : Unique void nodes as nil, true, false. Some will be used as lock for some processes.
-	`TYPE` : Type definition. Primitive class type.
-	`BOOLEAN` : TRUE or FALSE values.
-	`BYTE`, `SHORT`, `INT`, `LONG` : Integers of 8, 16, 32 and 64 bits.
-	`UBYTE`, `USHORT`, `UINT`, `ULONG` : Unsigned Integers of 8, 16, 32 and 64 bits.
-	`RATIO` : Numerator and denominator values for ratios.
-	`BIGINT`, `UBIGINT` and `BIGDEC` : unlimited size Integers and Floats.
-	`CHAR`: 16 bits signed char (UTF16). Implemented as SHORT.
-	`UCHAR`: 16 bits unsigned char (UTF16). Implemented as USHORT.
-	`STRING` : Sized constant String of bytes. Can be UTFed.`size` is a long.
-	`ZSTRING` : Constant String of bytes. It's terminated by a final \0.
-	`MFUNC` : Multiple arrity functions.
-	`FUNC` : Single function, with arrity and vararg.
-	`PTR` : Pointer on a Node.
-	`SARRAY` : Sized array of constant size `Nodes`.
-	`SLIST` : Sized list of constant size `Nodes`.
-	`BITARRAY` : Array of bits (implemented as UBIGINT)
-	`ARRAY` : Immutable hashed array
-	`ORDEREDARRAY` : Immutable ordered hashed array
-	`LIST` : Immutable hashed list
-	`KEYVAL` : Associative value as a key and a value.
-	`MAP` : Immutable hashed map
-	`ARRAYMAP` : Immutable hashed array map
-	`ORDEREDMAP` : Immutable ordered hashed array map
-	`SET` : Immutable hashed set
-	`CLASS` : Class definition. Derived class type.
-	`OBJECT` : Object according to a class of interface.
-	`INTERFACE` : Interface definition. Polymorphic class type.

### polymorphic_nodes library
