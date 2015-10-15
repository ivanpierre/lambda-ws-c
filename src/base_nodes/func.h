/****
	Function header

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef FUNCTION_H
#define FUNCTION_H

/*
	Functions
*/
typedef struct
{
	WS_BYTE start_arrity;
	WS_BYTE end_arrity;
} Func;

long count_args(va_list args);

#endif
