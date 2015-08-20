/****
    Test on string function

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <string.h>
#include "nodes.h"
#include "global.h"
#include "free.h"
#include "number.h"
#include "strings.h"
#include "writer.h"

void test_list1()
{
    TRACE("-----------------------test_list1()----------------------------------------")
    print_stack_trace();


    writer_curr_close();
    print_stack_trace();
}


void test_list()
{
    test_list1();
}

