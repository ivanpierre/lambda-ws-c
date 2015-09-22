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
	TRACE("-----------------------test_string1()----------------------------------------");
	print_node_stack();

	// creation string

	// Dont work: not allocated
	// node = string("hgfjhgfjhgfjhgfjhgfhj"); // The string will be deallocated

	// marche
	Node *node = NULL;
	Node *node2 = NULL;
	Node *node3 = NULL;

	ASSIGN(node, string("hgfjhgfjhgfjhgfjhgfhj"));
	print_node_stack();

	ASSIGN(node2, string("hgfjhgfjhgfjhgfjhgfhj"));
	print_node_stack();

	ASSIGN(node3, string("hgfjhgfjhgfjhgfjhgfhj"));
	print_node_stack();

	PRINTLN(node);
	print_node_stack();

	PRINT(node3);
	print_node_stack();

	PR(node2);
	print_node_stack();

	PRN(node3);
	print_node_stack();

	PRINTLN(node2);
	print_node_stack();

	PRINT(node);
	print_node_stack();

	PR(node3);
	print_node_stack();

	PRN(node);
	print_node_stack();

	unlink_node(node2);
	unlink_node(node);
	unlink_node(node3);
	print_node_stack();

	writer_curr_close();
	print_node_stack();
}

/*
	Multiple linking
	Three instances on the same string object
*/
void test_string2()
{
	TRACE("-----------------------test_string2()----------------------------------------");
	print_node_stack();

	// creation string
	// works
	Node *node = NULL;
	Node *node2 = NULL;
	Node *node3 = NULL;

	ASSIGN(node, string("hgfjhgfjhgfjhgfjhgfhj"));
	print_node_stack();

	ASSIGN(node2, node);
	print_node_stack();

	ASSIGN(node3, node);
	print_node_stack();

	PRINTLN(node3);
	print_node_stack();

	PRINTLN(node);
	print_node_stack();

	PRN(node2);
	print_node_stack();

	PR(node3);
	print_node_stack();

	PRINTLN(node);
	print_node_stack();

	PRINTLN(node2);
	print_node_stack();

	PRN(node3);
	print_node_stack();

	PR(node);
	print_node_stack();

	unlink_node(node3);
	unlink_node(node);
	unlink_node(node2);
	print_node_stack();

	writer_curr_close();
	print_node_stack();
}

/*
	Multiple linking
	Three instances on the same string object
*/
void test_string3()
{
	TRACE("-----------------------test_string3()----------------------------------------");
	print_node_stack();

	// creation string
	// workse
	Node *node = NULL;
	Node *node2 = NULL;
	Node *node3 = NULL;

	ASSIGN(node, string("hgfjhgfjhgfjhgfjhgfhj"));
	ASSIGN(node2, node);
	ASSIGN(node3, node2);

	print_node_stack();

	PRINTLN(node);
	print_node_stack();

	PRN(node2);
	print_node_stack();

	PRN(node3);
	print_node_stack();

	TRACE("we will manage NIL");

	PRINTLN(NIL);

	TRACE("we have managed NIL");

	print_node_stack();

	PRINTLN(FALSE);
	print_node_stack();

	PRINTLN(TRUE);
	print_node_stack();

	unlink_node(node3);
	unlink_node(node);
	unlink_node(node2);
	print_node_stack();

	writer_curr_close();
	print_node_stack();
}

void test_string()
{
	test_string1();
	test_string2();
	test_string3();
}

