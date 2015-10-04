Requirements
============

Language definition for now
---------------------------

Should manage

```
(add (lit 21)(lit 21))
```

ou

```
add(lit(21),lit(21))
```

et

```
(let
    (bind x (lit 21))
    (add x (lit 21)))
```

Well, as reader should recognize numbers, there's no need of (lit INTEGER) AST will be created accordingly. And binding could be created as an associative map giving first argument of let the binding that will be added to local environment.

So giving in language :

```
(add 21 21)
```

and

```
(let {x 21} (add x 21))
```

witch will be translated internally as AST

```
(LIST
    (SYMBOL add)
    (LIST
        (INTEGER 21)
        (LIST
            (INTEGER 21)
            NIL)))
```

and

```
(LIST
    (SYMBOL let)
    (LIST
        (LIST
            (SYMBOL x)
            (LIST
                (INTEGER 21)
                NIL))
        (LIST
            (LIST
                (SYMBOL add)
                (LIST
                    (SYMBOL x)
                    (LIST
                        (INTEGER 21)
                        NIL)))
            NIL)))
```

I think I should rename LIST as CONS cells, or store them as arrays... ;)

as arrays it would give :

```
(LIST 3
    (SYMBOL let)
    (LIST 2
        (SYMBOL x)
        (INTEGER 21))
    (LIST 3
        (SYMBOL add)
        (SYMBOL x)
        (INTEGER 21)))
```

But all that is implementation details :D

As an issue. defining binding as a map doesn't guarantee order of bindings, as values can be any nodes. So it's probably better to define them as array or as list, so evaluation will be ordinated.
