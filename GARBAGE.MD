# Garbage collector
This part has been completely reworked. The previous version of GC was completely overwhelming and didn't resolve the
segmentation of allocated data problem. So get rid of a separated garbage collector. This one should have an 
addressing indirection to the data segments, witch should be managed in a contiguous memory allocation with free 
continuous segments lists and so on... so keep that as implementation details.

## Nodes
Now nodes contains the number of links it manages. There is an option to manage an allocated node list witch is 
updated when allocation or deallocation occurs. This process is for debugging purposes only, so the program can be 
compiled with or without it with no more convenient problems than change of a constant definition. The debugging 
implementation only add a previous and next link to every nodes and call to appropriate management for allocation 
and desallocation.

Identity of pointers is when two nodes have the same address. Equality is managed by the types through the `equals` 
function pointer.

## linking and unlinking
Every node that is used in some process should be linked to avoid it to be deallocated, and unlinked when no more in 
use. Link and unlink should be done in a same function to avoid memory leaks of bad memory management. The only way 
not to unlink it is when the node is linked to a persistent value, generally to an environment interning or if used 
by another node (i.e. lists, array, map, ...) Types manage the release of memory through the `free` function pointer.

The allocation is done by the constructor of each types, arguments for it depends on the type.

There is only three values that are never linked or unlinked : NIL, TRUE and FALSE. They are equal to themselves.
NIL and FALSE are false boolean values, FALSE is here for disambiguating NIL values than can be pertinent return 
values. 

