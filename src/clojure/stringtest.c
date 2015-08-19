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

void test_string1()
{
    TRACE("-----------------------test_string1()----------------------------------------")
    print_stack_trace();

    // creation string

    // Dont work: not allocated
    // node = string("hgfjhgfjhgfjhgfjhgfhj"); // The string will be deallocated

    // marche
    Node *node = string_allocate(("hgfjhgfjhgfjhgfjhgfhj"));        // this do the strdup internally
    Node *node2 = string(strdup("hgfjhgfjhgfjhgfjhgfhj"));          // ok nice
    Node *node3 = string_allocate(strdup("hgfjhgfjhgfjhgfjhgfhj")); // Two time allocated
    print_stack_trace();

    PRINTLN(node);
    print_stack_trace();

    PRINT(node3);
    print_stack_trace();

    PR(node2);
    print_stack_trace();

    PRN(node3);
    print_stack_trace();

    PRINTLN(node2);
    print_stack_trace();

    PRINT(node);
    print_stack_trace();

    PR(node3);
    print_stack_trace();

    PRN(node);
    print_stack_trace();

    unlink_node(node2);
    unlink_node(node);
    unlink_node(node3);
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
    TRACE("-----------------------test_string2()----------------------------------------")
    print_stack_trace();

    // creation string
    // workse
    Node *node = string_allocate(("hgfjhgfjhgfjhgfjhgfhj"));
    Node *node2 = link_node(node);
    Node *node3 = link_node(node);
    print_stack_trace();

    PRINTLN(node3);
    print_stack_trace();

    PRINTLN(node);
    print_stack_trace();

    PRN(node2);
    print_stack_trace();

    PR(node3);
    print_stack_trace();

    PRINTLN(node);
    print_stack_trace();

    PRINTLN(node2);
    print_stack_trace();

    PRN(node3);
    print_stack_trace();

    PR(node);
    print_stack_trace();

    unlink_node(node3);
    unlink_node(node);
    unlink_node(node2);
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
    TRACE("-----------------------test_string3()----------------------------------------")
    print_stack_trace();

    // creation string
    // workse
    Node *node = string_allocate(("hgfjhgfjhgfjhgfjhgfhj"));
    Node *node2 = link_node(node);
    Node *node3 = link_node(node2);

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
    test_string1();
    test_string2();
    test_string3();
}

