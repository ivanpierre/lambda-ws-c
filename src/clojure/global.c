/****
    LWC language core functions

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "global.h"
#include "free.h"
#include "number.h"
#include "strings.h"
#include "writer.h"

/*
    Special functions
*/

Node *node = NULL;
Node *node2 = NULL;
Node *node3 = NULL;

/*
    Normal functions
*/
/*
    Normal functions
*/
void test_integer()
{
    print_stack_trace();

    // creation integer
    node = integer(123l);
    print_stack_trace();

    PRINT(node);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();

}

/*
    Normal functions
*/
void test_decimal()
{
    print_stack_trace();

    // creation decimal
    node = decimal(123.345);
    print_stack_trace();

    PRINT(node);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();
}


void test()
{
    test_integer();
    test_decimal();
}

