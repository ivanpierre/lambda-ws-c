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
	TRACE("-----------------------test_list1()----------------------------------------");
	print_node_stack();

	Node *list = NULL;
	Node *array = NULL;
	Node *map = NULL;
	Node *set = NULL;

	link_node(&list, empty_list());
	print_node_stack();

	link_node(&array, empty_array());
	print_node_stack();

	link_node(&map, empty_map());
	print_node_stack();

	link_node(&set, empty_set());
	print_node_stack();

	PRINT(list);
	PRINT(array);
	PRINT(map);
	PRINT(set);

dealloc:
	unlink_node(&list);
	print_node_stack();

	unlink_node(&array);
	print_node_stack();

	unlink_node(&map);
	print_node_stack();

	unlink_node(&set);
	print_node_stack();

	writer_curr_close();
	print_node_stack();
}


void test_list()
{
	test_list1();
}

