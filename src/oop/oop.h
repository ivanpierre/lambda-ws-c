/****
	Init OOP library

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef INIT_H
#define INIT_H

/*
	Used type definitions
*/
// Integers
typedef int8_t			WS_BYTE;
typedef int16_t			WS_SHORT;
typedef int32_t			WS_INT;
typedef int64_t			WS_LONG;
typedef int8_t			WS_BOOL;

// Decimal
typedef float			WS_FLOAT;
typedef double			WS_DOUBLE;

#define BOOL_FALSE 0

/*
	Define in case of allocation debugging
*/
#define DEBUG_ALLOC

/*
	To display debugging trace of allocation and unallocation
*/
// #define DEBUG_FREE


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

#endif
