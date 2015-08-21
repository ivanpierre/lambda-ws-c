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
#include "collection.h"

void test_list1()
{
    TRACE("-----------------------test_list1()----------------------------------------")
    print_stack_trace();

    Node *list = NULL;
    Node *array = NULL;
    Node *map = NULL;
    Node *set = NULL;

    ASSERT_ALLOC(collection(list, ILIST, 0));
    print_stack_trace();

    ASSERT_ALLOC(collection(array, IARRAY, 0));
    print_stack_trace();

    ASSERT_ALLOC(collection(map, IMAP, 0));
    print_stack_trace();

    ASSERT_ALLOC(collection(set, ISET, 0));
    print_stack_trace();

    PRINT(list);
    PRINT(array);
    PRINT(map);
    PRINT(set);

dealloc:
    unlink_node(list);
    print_stack_trace();

    unlink_node(array);
    print_stack_trace();

    unlink_node(map);
    print_stack_trace();

    unlink_node(set);
    print_stack_trace();

    writer_curr_close();
    print_stack_trace();
}


void test_list()
{
    test_list1();
}

