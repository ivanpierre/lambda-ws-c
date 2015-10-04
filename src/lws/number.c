/****
    Integer : manage 32 bits Integers

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef INTEGER_H
#define INTEGER_H

// Integers
typedef int_8_t 		WS_BYTE;
#define WS_BYTE_MIN		INT8_MIN
#define WS_BYTE_MAX		INT8_MAX

typedef int_16_t 		WS_SHORT;
#define WS_SHORT_MIN	SHORT16_MIN
#define WS_SHORT_MAX	SHORT16_MAX

typedef int_32_t 		WS_INT;
#define WS_INT_MIN		INT32_MIN
#define WS_BYTE_MAX		INT32_MAX

typedef int_64_t 		WS_LONG;
#define WS_LONG_MIN		INT64_MIN
#define WS_LONG_MAX		INT64_MAX

// Decimal
typedef float 			WS_FLOAT;
#define WS_LONG_MIN		FLT_MIN
#define WS_LONG_MAX		FLT_MAX
