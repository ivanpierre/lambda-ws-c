/****
	Class class

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "oop.h"

Class *CLASS_CLASS = NULL;

WS_INT METH_GET_SUPERCLASS = -1;

static  MethodDesc	class_func_def[] =
	{
		{"getObjSize",		1, &class_get_obj_size},
		{"getSuperclass",	1, &class_get_superclass},
		{"toString",		1, &class_to_string}, // override
		{"finalize",		1, &class_finalize}, // overrides
		METHOD_DESC_END
	};

/**
	Create Class as a Class and init values
	We have to create all the classes and interface first and only after
	define all the heritances and function with the correct values.
	Class `class` has to be first created as all classes have the class type ;)
	Afterward only we will be able to create other objects to be able
	to define functions, sets, ..., and correct heritance and interfaces.
*/
void class_static()
{
	CLASS_CLASS = class("Class");

	// It's the first Class defined we have to define the class as itself...
	CLASS_CLASS->class = CLASS_CLASS;
}

/**
	Init all functions of class class
*/
void class_functions()
{
	CLASS_CLASS = class_functions_init(CLASS_CLASS, CLASS_INTERFACE,
										(void *[]){NULL}, class_func_def);
	METH_GET_SUPERCLASS = key("getSuperclass");
	METH_GET_OBJ_SIZE = key("getObjSize");
}

/**
	Create new class object
*/
void *class(char *name)
{
	void *class = object_alloc(sizeof(Class));
	class = class_init(class, name);
	return class;
}

/**
	Init values of new class object
*/
void *class_init(void *class, char *name)
{
	Class *cl = interface_init(class, name);

	cl->super = NULL;
	cl->class = CLASS_CLASS;

	return cl;
}

/**
	Init functions of new class object
*/
void *class_functions_init(void *class, void *super,
							void *interfaces[], MethodDesc *methods)
{
	if(!super)
		super = NIL;
	((Class *)class)->super = super;

	// get all interface functions
	class = interface_interface_init(class, interfaces);

	// Imports superclass functions
	class = interface_function_inherit(class, ((Class *)class)->super);

	// define implementation methods and add undefined function names in set
	class = interface_function_init(class, methods);
	return class;
}

/****************************************
	METHODS
*/
/**
	Release allocated values of class object to be released
	@overrides
*/
void *class_finalize(void *class)
{
	// first finalize sub class
	class = interface_finalize(class);
	return class;
}

/*
	Return size of class
*/
void *class_get_obj_class(void *class)
{
	return ((Class *)class)->size;
}

/*
	Return superclass of class
*/
void *class_get_superclass(void *class)
{
	return ((Class *)class)->super;
}

/*
	return string value of object
	@overrides
*/
void *class_to_string(void *class)
{
	return ((Class *)class)->name;
}
