# lambda-ws-c
Lambda Calculus Workshop in C

## Introduction
This is result of the workshop of Functional Romandie the 16/07/2015. 
You can see the github https://github.com/FunctionalRomandie/LambdaCalculusWorkshop.

- [Goals](GOALS.MD)
- [Implementation](IMPLEMENTATION.MD)
- [Garbage collection](GARBAGE.MD)
- Code generation (TBD)


- [Project requirements](REQUIREMENTS)

You can see the [blog](BLOG.MD) to see advance... ;)

## Behind the requirements

As this workshop is on AST concept's proof, creating a Clojure like language with some AST
management function is a clear non-goal... So I put AST as a LWS library, and languages
on their own directories.

What is specific to languages ? The AST, well it can limit, but in fact the only dependent
part of language is its syntax (the reader, the writer) and semantic (the core elements of the 
laguage). THE AST only give access to basis computational concepts all languages would like to use.

In the AST point of view, the two following pieces of code here are the same.

```
    10 IF A& = 0 THEN PRINT "COUCOU" ELSE PRINT "CACA"
```
```
    (if (zerop a) 
      (println "coucou")
      (println "caca"))
```

So to have a proof of concept the better is to try to implement some different paradigms with
the same AST library. I so choose :

- Clojure - like. functional, dynamically typed, immutable.
- BASIC - original non structured, spaghetti, stateful, line based language.
- Java - like. object, structured, statically typed.

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
functional language is ways to easy ;)

Well, it will be when all the data types will be implemented.

But the BIG difficulty, is managing the memory, even if we dont use a real garbage collector.

And it's a side project, so I can not always give to it intended time ;)

## Licence
For now :

- Eclipse Public License - v 1.0 for the code.
- CC creative common for documentation.
