# lambda-ws-c
Lambda Calculus Workshop in C

## Introduction
This is result of the workshop of Functional Romandie the 16/07/2015. 
You can see the github https://github.com/FunctionalRomandie/LambdaCalculusWorkshop.

- [Goals](GOALS.MD)
- [Implementation](IMPLEMENTATION.MD)
-- [Library](LWS.MD)
-- [Clojure](CLOJURE.MD)
-- [Basic](BASIC.MD)
-- [Java](JAVA.MD)
- [Garbage collection](GARBAGE.MD)
- Code generation (TBD)
- [Project requirements](REQUIREMENTS)

You can see the [blog](BLOG.MD) to see advance... ;)

## Behind the requirements

As this workshop is on AST (Abstract Syntax Tree) proof of concept, creating a Clojure like language with some AST
management function is a clear non-goal... So we'll put AST as a LWS library, and languages
on their own directories.

What is specific to languages ? The AST ? Well it can be a limitating factor, but in fact the only dependent
part of language is: its syntax (the reader, the writer) and semantic (the core elements of the 
language). THE AST only give access to basis computational concepts all languages would like to use.

For the AST point of view, the two following pieces of code here are quite the same :

```bas
    10 IF A& = 0 THEN PRINT "COUCOU" ELSE PRINT "CACA"
```
```.clj
    (if (zerop a) 
      (println "coucou")
      (println "caca"))
```

But that is not the case for the followings :

```.bas
    10 SUM = 0
    20 FOR I = 0 to 1000 - 1
    30 SUM = SUM + I
    40 NEXT I
    50 PRINT SUM
```
```.clj
    (prinln (reduce + (range 1000)))
```

So what's the difference ? 

In BASIC we are stateful, so we can modify the SUM variable, but we don't have function as first class
type, we don't have lazy list data structure. But we can spaghettify the code with an implicit GOTO in 
the form of NEXT.

So is AST different, no... just BASIC programmer has no access to certain data structure, so AST. If you want 
to enhance BASIC you'll try to manage an access to these elements, but without changing syntax and
main language ideas...

OR you do with the language. For example, some would think to use variable indexed GOSUB. And yes you can
do it with an old BASIC... but some would say, it's not idiomatically correct... poor guy... probably not a BASIC 
programmer :D. But yes, it could become an awful unmanageable boilerplate.

## How to figure out ?
So to have a proof of concept, the better way is to try to implement some different paradigms with
the same AST library. 

So we'll take :

- Clojure-like - functional, dynamically typed, immutable language.
- BASIC - original non structured, spaghetti, stateful, line based language.
- Java-like - object, structured, statically typed language.

Clearly separating the stuff better the implementation problems will arise. If I have to update the library to 
implement my language means or I don't know how to use it, or there is a paradigm that is not manageable by my AST.

## So what ?
Well, we'll see. How to separate AST specific things and language implementation details. 

For example is laziness an AST thing of we can manage it with a shorter AST. Yes any Turing language can do it,
but as a problem of efficiency where to put the balance ?

Yes KEYVAL can be an array, but it would take more space. Yes and array can be a linked list enabling
a better memory management, but you lose the indexing, map could be a list, but you lose the mapping.

So it's a question of data definition efficiency and somewhat taste. :D


## And now what ?
For any question or issue you can write to me on twitter @ivanpierre. It's currently a WIP.

But as I have to manage all the data types to begin to put just a function call with a symbol in environment, I 
finish to have a complete functional language. Well this was the goal, as programming a functional language with a 
functional language is ways too easy ;)

Well, it will be when all the data types will be implemented.

But the BIG difficulty, is managing the memory, even if we dont use a real garbage collector.

And it's a side project, so I can not always give to it intended time ;)

## Licence
For now :

- Eclipse Public License - v 1.0 for the code. See [Licence file](LICENCE).
- CC creative common for documentation.
