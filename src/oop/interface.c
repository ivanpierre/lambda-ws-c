/****
	Init OOP library

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "oop.h"

static WS_BOOL is_init = WS_FALSE;

bool isa(Object *type, Object *isa)
{
	return true;
}

bool InterfaceInit()
{
	if(is_init)
		return true;

	is_init = WS_TRUE;
	return true;
}
