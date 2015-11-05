/****
	Init OOP library

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef INIT_H
#define INIT_H

#include "object.h"
#include "gc.h"
  #include "strings.h"
  #include "set.h"
  #include "named.h"
    #include "interface.h"
      #include "class.h"
    #include "method.h"
  #include "number.h"
    // #include "byte.h"
	// #include "short.h"
	#include "int.h"
	// #include "long.h"
	// #include "bigint.h"
	//
	// #include "ratio.h"
	//
	// #include "float.h"
	// #include "double.h"
	// #include "bigdec.h"

extern void init();

extern void *key_def;

#endif
