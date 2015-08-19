/****
    Test numbers

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
#include "global.h"
#include "free.h"
#include "number.h"
#include "strings.h"
#include "writer.h"

void test_integer()
{
    TRACE("-----------------------test_integer()----------------------------------------")
    print_stack_trace();

    Node *node = integer(123l);
    print_stack_trace();

    PRINT(node);
    print_stack_trace();

    // PRINT(node);
    // print_stack_trace();

    unlink_node(node);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();

}

void test_integer2()
{
    TRACE("-----------------------test_integer2()----------------------------------------")
    print_stack_trace();

    // creation integer
    Node *node = integer(123l);
    Node *node2 = integer(4244);
    Node *node3 = integer(0);
    print_stack_trace();

    PRINT(node);
    print_stack_trace();

    PRINT(node);
    print_stack_trace();

    PRINT(node2);
    print_stack_trace();

    PRINT(node3);
    print_stack_trace();

    PRINT(node2);
    print_stack_trace();

    unlink_node(node);
    unlink_node(node2);
    unlink_node(node3);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();

}

void test_integer3()
{
    TRACE("-----------------------test_integer3()----------------------------------------")
    print_stack_trace();

    // creation integer
    Node *node = integer(123l);
    Node *node2 = link_node(node);
    Node *node3 = link_node(node2);
    print_stack_trace();

    PRINT(node2);
    print_stack_trace();

    PRINT(node);
    print_stack_trace();

    PRINT(node2);
    print_stack_trace();

    PRINT(node3);
    print_stack_trace();

    PRINT(node2);
    print_stack_trace();

    unlink_node(node2);
    unlink_node(node3);
    unlink_node(node);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();

}

/*
    Normal functions
*/
void test_decimal()
{
    TRACE("-----------------------test_decimal()----------------------------------------")
    print_stack_trace();

    // creation decimal
    Node *node = decimal(123.345);
    print_stack_trace();

    PRINTLN(node);
    print_stack_trace();

    PRINTLN(node);
    print_stack_trace();

    PRINTLN(node);
    print_stack_trace();

    unlink_node(node);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();
}

/*
    Normal functions
*/
void test_decimal2()
{
    TRACE("-----------------------test_decimal2()----------------------------------------")
    print_stack_trace();

    // creation decimal
    Node *node = decimal(123.345);
    Node *node2 = decimal(111);
    Node *node3 = decimal(0.87877878787);
    print_stack_trace();

    PRINTLN(node2);
    print_stack_trace();

    PRINT(node);
    print_stack_trace();

    PR(node3);
    print_stack_trace();

    PRN(node);
    print_stack_trace();

    PRINTLN(node);
    print_stack_trace();

    PRINT(node3);
    print_stack_trace();

    PR(node2);
    print_stack_trace();

    PRN(node3);
    print_stack_trace();

    unlink_node(node);
    unlink_node(node2);
    unlink_node(node3);

    writer_curr_close();
    print_stack_trace();
}

/*
    Normal functions
*/
void test_decimal3()
{
    TRACE("-----------------------test_decimal3()----------------------------------------")
    print_stack_trace();

    // creation decimal
    Node *node = decimal(123.345);
    Node *node2 = link_node(node);
    Node *node3 = link_node(node2);
    print_stack_trace();

    PRINT(node);
    print_stack_trace();

    PRINTLN(node2);
    print_stack_trace();

    PR(node3);
    print_stack_trace();

    PRN(node);
    print_stack_trace();

    PRINT(node2);
    print_stack_trace();

    PRINTLN(node3);
    print_stack_trace();

    PR(node);
    print_stack_trace();

    PRN(node2);
    print_stack_trace();

    unlink_node(node);
    unlink_node(node2);
    unlink_node(node3);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();
}


void test_number()
{
    test_integer();
    test_integer2();
    test_integer3();
    test_decimal();
    test_decimal2();
    test_decimal3();
}

