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
    TRACE("-----------------------test_symbol1()----------------------------------------")
    print_stack_trace();

    // creation symbol
    Node *s_name = string_allocate("symbol1");
    Node *node = symbol(nil, s_name);

    print_stack_trace();
    unlink_node(s_name);
    print_stack_trace();

    s_name = string_allocate("symbol2");
    Node *node2 = symbol(nil, s_name);

    print_stack_trace();
    unlink_node(s_name);
    print_stack_trace();

    s_name = string_allocate("symbol3");
    Node *node3 = symbol(nil, s_name);

    print_stack_trace();
    unlink_node(s_name);
    print_stack_trace();

    PRINTLN(node);
    print_stack_trace();

    PRN(node2);
    print_stack_trace();

    PRN(node3);
    print_stack_trace();

    unlink_node(node3);
    unlink_node(node);
    unlink_node(node2);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();

}

void test_symbol2()
{
    TRACE("-----------------------test_symbol2()----------------------------------------")
    print_stack_trace();

    // creation symbol
    Node *s_name = string_allocate("symbol1");
    Node *node = symbol(nil, s_name);

    print_stack_trace();
    unlink_node(s_name);
    print_stack_trace();

    Node *node2 = link_node(node);
    print_stack_trace();

    Node *node3 = link_node(node2);
    print_stack_trace();

    PRINT(node3);
    print_stack_trace();

    PRINTLN(node);
    print_stack_trace();

    PR(node2);
    print_stack_trace();

    PRN(node3);
    print_stack_trace();

    unlink_node(node3);
    print_stack_trace();

    unlink_node(node);
    print_stack_trace();

    unlink_node(node2);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();
}

void test_symbol3()
{
    TRACE("-----------------------test_symbol3()----------------------------------------")
    print_stack_trace();

    // creation symbol
    Node *s_name = string_allocate("symbol1");
    print_stack_trace();

    Node *node = symbol(nil, s_name);
    print_stack_trace();

    unlink_node(s_name);
    print_stack_trace();

    s_name = string_allocate("symbol2");
    print_stack_trace();

    Node *node2 = symbol(nil, s_name);
    print_stack_trace();

    unlink_node(s_name);
    print_stack_trace();

    Node *node3 = link_node(node2);
    print_stack_trace();

    PRINT(node3);
    print_stack_trace();

    PRINTLN(node);
    print_stack_trace();

    PR(node2);
    print_stack_trace();

    PRN(node3);
    print_stack_trace();

    unlink_node(node3);
    print_stack_trace();

    unlink_node(node);
    print_stack_trace();

    unlink_node(node2);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();
}

void test_symbol()
{
    test_symbol1();
    test_symbol2();
    test_symbol3();
}

