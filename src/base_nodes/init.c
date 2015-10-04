// TODO initialize NIL, TRUE, FALSE
#include "nodes.h"
#include "type.h"

void init()
{
	NIL->type = &type_array[INIL];
	TRUE->type = &type_array[ITRUE];
	FALSE->type = &type_array[IFALSE];
}
