#BLOG (just what happens)
##28 juil 2015
Some changes in view.

- [ ] use of glib library for ARRAY, MAP and SET. It will be easier doesn't change the problem a lot. Just unifies the 
management of collection of objects.
- [ ] Suppress the Type type. No real usage, these functions will be in global.c and so will be more managable than 
specific 
data type that can change. They will accept all data types and if not managed give an appropriate error message.
- [ ] Going to unify the structures functions names. So global function will be easier to manage.
- [ ] Create a new node .c and .h. With a structure embedding the whole other structures. SO NODE macro will have no 
sence anymore.

This should greatly simplify the code and enable a better journey.

##Started 28 Juil 2015

CC licence
