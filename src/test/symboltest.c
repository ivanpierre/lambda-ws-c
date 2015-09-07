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
#include "writer.h"
#include "strings.h"
#include "named.h"

void test_symbol1()
{
    TRACE("-----------------------test_symbol1()----------------------------------------");
    print_node_stack();

}

void test_symbol2()
{
    TRACE("-----------------------test_symbol2()----------------------------------------");
}

void test_symbol3()
{
    TRACE("-----------------------test_symbol3()----------------------------------------");
    print_node_stack();

}

void test_symbol()
{
    test_symbol1();
    test_symbol2();
    test_symbol3();
}

