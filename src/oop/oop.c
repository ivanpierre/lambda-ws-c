/****
    init the OOP library

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "oop.h"

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
	strings_static();
	named_static();
	interface_static();
	method_static();
	set_static();
	key_index_static();
	index_obj_static();
	number_static();
	int_static();

	NIL 	= object();
	FALSE 	= object();
	TRUE 	= object();

	/*
		Complement classes with functions and inheritance
	*/
	object_functions();
	strings_functions();
	error_functions();
	named_functions();
	interface_functions();
	class_functions();
	method_functions();
	set_functions();
	key_index_functions();
	index_obj_functions();
	number_functions();
	int_functions();
}

/*
	Terminate the library
*/
void terminate()
{
	object_finalize(NIL);
	object_finalize(TRUE);
	object_finalize(FALSE);
	class_finalize(CLASS_INT);
	interface_finalize(INTERFACE_NUMBER);
	class_finalize(CLASS_INDEX_OBJ);
	class_finalize(CLASS_KEY_INDEX);
	class_finalize(CLASS_SET);
	class_finalize(CLASS_METHOD);
	class_finalize(CLASS_CLASS);
	class_finalize(CLASS_INTERFACE);
	class_finalize(CLASS_NAMED);
	class_finalize(CLASS_ERROR);
	class_finalize(CLASS_STRINGS);
	class_finalize(CLASS_OBJECT);
}
