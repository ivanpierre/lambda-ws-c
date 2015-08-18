/****
    Test on string function

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


void banner()
{
    PRINTLN(string_allocate("====================================================================="));
}


/*
    Allocation of functions
*/
void test_string1()
{
    banner();
    print_stack_trace();

    // creation string

    // Dont work: not allocated
    // node = string("hgfjhgfjhgfjhgfjhgfhj"); // The string will be deallocated

    // marche
    node = string_allocate(("hgfjhgfjhgfjhgfjhgfhj"));        // this do the strdup internally
    node2 = string(strdup("hgfjhgfjhgfjhgfjhgfhj"));          // ok nice
    node3 = string_allocate(strdup("hgfjhgfjhgfjhgfjhgfhj")); // Two time allocated
    // node2 = string_allocate("hgfjhgfjhgfjhgfjhgfhj");

    print_stack_trace();

    PRINTLN(node);
    print_stack_trace();

    PR(node2);
    print_stack_trace();

    PRN(node3);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();
}

/*
    Multiple linking
    Three instances on the same string object
*/
void test_string2()
{
    banner();
    print_stack_trace();

    // creation string
    // workse
    node = string_allocate(("hgfjhgfjhgfjhgfjhgfhj"));
    node2 = link_node(node);
    node3 = link_node(node);

    print_stack_trace();

    PRINTLN(node);
    print_stack_trace();

    PRN(node2);
    print_stack_trace();

    PRN(node3);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();
}

/*
    Multiple linking
    Three instances on the same string object
*/
void test_string3()
{
    ERROR("Essai d'erreur en tout sens %d\n", 123);

    banner();
    print_stack_trace();

    // creation string
    // workse
    node = string_allocate(("hgfjhgfjhgfjhgfjhgfhj"));
    node2 = link_node(node);
    node3 = link_node(node2);

    print_stack_trace();

    PRINTLN(node);
    print_stack_trace();

    PRN(node2);
    print_stack_trace();

    PRN(node3);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();
}

void test_string()
{
    // test_string1();
    // test_string2();
    test_string3();
}

