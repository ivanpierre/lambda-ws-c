/****
    init, initialize the library

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "interfaces.h"
#include "classes.h"

/*
	Initialize all the stuff
*/
void init()
{
	NIL 	= new_node(CONST);
	TRUE 	= new_node(CONST);
	FALSE 	= new_node(CONST);
}

/*
	Terminate the library
*/
void terminate()
{
	free(NIL);
	free(TRUE);
	free(FALSE);
}
