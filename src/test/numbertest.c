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
	TRACE("-----------------------test_integer()----------------------------------------");
	print_node_stack();

	Node *node = integer(123l);
	print_node_stack();
	Node *node2 = NULL;

	link_node(&node2, node);
	print_node_stack();

	PRINT(node);
	print_node_stack();

	PRINT(node2);
	print_node_stack();

	unlink_node(&node2);
	print_node_stack();

	writer_curr_close();
	print_node_stack();

}

void test_integer2()
{
	TRACE("-----------------------test_integer2()----------------------------------------");
	print_node_stack();

	// creation integer
	Node *node = NULL;
	Node *node2 = NULL;
	Node *node3 = NULL;

	// creation integer
	link_node(&node, integer(123l));
	print_node_stack();

	link_node(&node2, integer(4244));
	print_node_stack();

	link_node(&node3, integer(0));
	print_node_stack();

	PRINT(node);
	print_node_stack();

	PRINT(node);
	print_node_stack();

	PRINT(node2);
	print_node_stack();

	PRINT(node3);
	print_node_stack();

	PRINT(node2);
	print_node_stack();

	unlink_node(&node);
	print_node_stack();

	unlink_node(&node2);
	print_node_stack();

	unlink_node(&node3);
	print_node_stack();

	writer_curr_close();
	print_node_stack();

}

void test_integer3()
{
	TRACE("-----------------------test_integer3()----------------------------------------");
	print_node_stack();

	// creation integer
	Node *node = NULL;
	Node *node2 = NULL;
	Node *node3 = NULL;

	link_node(&node, integer(123l));
	print_node_stack();

	link_node(&node2, node);
	print_node_stack();

	link_node(&node3, node2);
	print_node_stack();

	PRINT(node2);
	print_node_stack();

	PRINT(node);
	print_node_stack();

	PRINT(node2);
	print_node_stack();

	PRINT(node3);
	print_node_stack();

	PRINT(node2);
	print_node_stack();

	unlink_node(&node2);
	unlink_node(&node3);
	unlink_node(&node);
	print_node_stack();

	writer_curr_close();
	print_node_stack();

}

/*
	Normal functions
*/
void test_decimal()
{
	TRACE("-----------------------test_decimal()----------------------------------------");
	print_node_stack();

	Node *node = NULL;

	// creation decimal
	link_node(&node, decimal(123.345));
	print_node_stack();

	PRINTLN(decimal(123.345));
	print_node_stack();

	PRINTLN(node);
	print_node_stack();

	PRINTLN(node);
	print_node_stack();

	unlink_node(&node);
	print_node_stack();

	writer_curr_close();
	print_node_stack();
}

/*
	Normal functions
*/
void test_decimal2()
{
	TRACE("-----------------------test_decimal2()----------------------------------------");
	print_node_stack();

	// creation decimal
	Node *node = NULL;
	Node *node2 = NULL;
	Node *node3 = NULL;

	link_node(&node, decimal(123.345));
	print_node_stack();

	link_node(&node2, decimal(111));
	print_node_stack();

	link_node(&node3, decimal(0.87877878787));
	print_node_stack();

	PRINTLN(node2);
	print_node_stack();

	PRINT(node);
	print_node_stack();

	PR(node3);
	print_node_stack();

	PRN(node);
	print_node_stack();

	PRINTLN(node);
	print_node_stack();

	PRINT(node3);
	print_node_stack();

	PR(node2);
	print_node_stack();

	PRN(node3);
	print_node_stack();

	unlink_node(&node);
	unlink_node(&node2);
	unlink_node(&node3);

	writer_curr_close();
	print_node_stack();
}

/*
	Normal functions
*/
void test_decimal3()
{
	TRACE("-----------------------test_decimal3()----------------------------------------");
	print_node_stack();

	// creation decimal
	Node *node = NULL;
	Node *node2 = NULL;
	Node *node3 = NULL;

	// creation decimal
	link_node(&node, decimal(123.345));
	print_node_stack();

	link_node(&node2, node);
	print_node_stack();

	link_node(&node3, node2);
	print_node_stack();

	PRINT(node);
	print_node_stack();

	PRINTLN(node2);
	print_node_stack();

	PR(node3);
	print_node_stack();

	PRN(node);
	print_node_stack();

	PRINT(node2);
	print_node_stack();

	PRINTLN(node3);
	print_node_stack();

	PR(node);
	print_node_stack();

	PRN(node2);
	print_node_stack();

	unlink_node(&node);
	unlink_node(&node2);
	unlink_node(&node3);
	print_node_stack();

	writer_curr_close();
	print_node_stack();
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

