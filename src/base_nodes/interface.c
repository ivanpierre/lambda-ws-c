
#include <stdio.h>
#include "object.h"
#include "interface.h"

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
