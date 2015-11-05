/****
    init the OOP library

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "oop.h"

void *key_def = NULL;

/*
	Initialize all the stuff
*/
void init()
{
	/**
		Create all classes with the class `class` first.
		This only create the class objects, the second part will
		define functional and inheritance elements.
	*/
	class_static();
	error_static();
	object_static();
	named_static();
	interface_static();
	method_static();
	set_static();
	strings_static();
	number_static();
	int_static();

	NIL 	= object();
	FALSE 	= object();
	TRUE 	= object();
	ASSIGN(key_def, empty_keymap());

	/*
		Complement classes
	*/
	object_functions();
	strings_functions();
	error_functions();
	named_functions();
	interface_functions();
	class_functions();
	method_functions();
	set_functions();
	number_functions();
	int_functions();
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
