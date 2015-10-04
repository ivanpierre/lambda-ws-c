# Implementation

Here are the main parts of the implementation. A library and three interpreters for various languages.

## [Library](LIBRARY.MD)

The library manages the main AST elements, with all the basic manipulation functions.

### Element of the library

The `READ` `PRINT`, `PR`, `EVAL`, `FREE` functions that depends on the AST call a function pointer, so every language can
extend the AST list at will. If the paradigm can be reused, the AST can be passed to the library.

Every AST has it's own header to be able to call public functions. Normally, language implementation should deal only
with Nodes that are the AST elements. There should be enough functions not to use implementation details.

### Garbage collection

AST element constructors already link the Nodes in the garbage collector. But every instance of a created node that
references this one should be linked too. It can be linked to another node and in this case, stay as is. Or consumed in
some function, in case if should be unlinked. At the end of every process there should only stay in the garbage
collector the nodes that are bound to the namespaces. Even the working objects of the language are bound here.

### Language management

Language should exclusively use Nodes without any knowledge of something else that the API. Any optimisation should
only be enhanced in the AST level, if a more efficient function is needed, it's here that it should be made.

### Enhancements of the library

Some elements should not be changed. If they are specific variant should be managed in the library level, if it's not
possible a new AST can be created in a way that they does not interfere with the existing library.

### Unmodifiable elements

- Structure of the AST.
- Their functions, creators, garbage collection and memory management.
- The global state variables that control its work.
- Library errors

### What can be rewritten

- Readers.
- Writers, that's obvios it should comply with the language syntax.
- Evaluators, it will manage the way the AST element will be used and the way they will perform actions. But normally a
lot of basic functions like calculations, C function calls and even internal evaluation process should remain mostly
unchanged. Mutability for example will be configurable from out of the library. Static typing for example will nee some
more work.

## [Clojure](CLOJURE.MD)

It will not be Clojure per se, as it would need a grat deal of AST enhancements... and multithreading... but, well, just
make the basic element of a list with a Clojure syntax should enable to use most of the Clojure library.

## [Basic](BASIC.MD)

The spaghetti goto mess should be an interesting point, just to see if the REPL can be a BASIC like with line numbers.
With a save and load function.

## [Tiny Java](JAVA.MD)

Here it will be more complicated : class management, static typing, imperative programming, say mutable state...
