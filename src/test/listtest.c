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

	Node *elist = NULL;
	Node *earray = NULL;
	Node *emap = NULL;
	Node *eset = NULL;

	Node *tlist = NULL;
	Node *tarray = NULL;
	Node *tmap = NULL;
	Node *tset = NULL;

	Node *rlist = NULL;
	Node *rarray = NULL;
	Node *rmap = NULL;
	Node *rset = NULL;

	link_node(&elist, empty_list());
	print_node_stack();

	link_node(&earray, empty_array());
	print_node_stack();

	link_node(&emap, empty_map());
	print_node_stack();

	link_node(&eset, empty_set());
	print_node_stack();

	link_node(&tlist, empty_transient_list());
	print_node_stack();

	link_node(&tarray, empty_transient_array());
	print_node_stack();

	link_node(&tmap, empty_transient_map());
	print_node_stack();

	link_node(&tset, empty_transient_set());
	print_node_stack();

	link_node(&rlist, list(elist, earray, eset, emap, NULL));
	print_node_stack();

	link_node(&rarray, array(elist, earray, eset, emap, NULL));
	print_node_stack();

	link_node(&rmap, map(elist, earray, eset, emap, NULL));
	print_node_stack();

	link_node(&rset, set(elist, earray, eset, emap, NULL));
	print_node_stack();

	PRINTLN(elist);
	PRINTLN(earray);
	PRINTLN(emap);
	PRINTLN(eset);

	PRINTLN(tlist);
	PRINTLN(tarray);
	PRINTLN(tmap);
	PRINTLN(tset);

	PRINTLN(rlist);
	PRINTLN(rarray);
	PRINTLN(rmap);
	PRINTLN(rset);

	PRINTLN(collection_mut_Q_(elist));
	PRINTLN(collection_mut_Q_(earray));
	PRINTLN(collection_mut_Q_(emap));
	PRINTLN(collection_mut_Q_(eset));
	PRINTLN(collection_mut_Q_(tlist));
	PRINTLN(collection_mut_Q_(tarray));
	PRINTLN(collection_mut_Q_(tmap));
	PRINTLN(collection_mut_Q_(tset));
	PRINTLN(collection_mut_Q_(rlist));
	PRINTLN(collection_mut_Q_(rarray));
	PRINTLN(collection_mut_Q_(rmap));
	PRINTLN(collection_mut_Q_(rset));

	PRINTLN(collection_first(elist));
	PRINTLN(collection_first(earray));
	PRINTLN(collection_first(emap));
	PRINTLN(collection_first(eset));
	PRINTLN(collection_first(tlist));
	PRINTLN(collection_first(tarray));
	PRINTLN(collection_first(tmap));
	PRINTLN(collection_first(tset));
	PRINTLN(collection_first(rlist));
	PRINTLN(collection_first(rarray));
	PRINTLN(collection_first(rmap));
	PRINTLN(collection_first(rset));

	PRINTLN(collection_last(elist));
	PRINTLN(collection_last(earray));
	PRINTLN(collection_last(emap));
	PRINTLN(collection_last(eset));
	PRINTLN(collection_last(tlist));
	PRINTLN(collection_last(tarray));
	PRINTLN(collection_last(tmap));
	PRINTLN(collection_last(tset));
	PRINTLN(collection_last(rlist));
	PRINTLN(collection_last(rarray));
	PRINTLN(collection_last(rmap));
	PRINTLN(collection_last(rset));

	PRINTLN(collection_count(elist));
	PRINTLN(collection_count(earray));
	PRINTLN(collection_count(emap));
	PRINTLN(collection_count(eset));
	PRINTLN(collection_count(tlist));
	PRINTLN(collection_count(tarray));
	PRINTLN(collection_count(tmap));
	PRINTLN(collection_count(tset));
	PRINTLN(collection_count(rlist));
	PRINTLN(collection_count(rarray));
	PRINTLN(collection_count(rmap));
	PRINTLN(collection_count(rset));

	PRINTLN(collection_max(elist));
	PRINTLN(collection_max(earray));
	PRINTLN(collection_max(emap));
	PRINTLN(collection_max(eset));
	PRINTLN(collection_max(tlist));
	PRINTLN(collection_max(tarray));
	PRINTLN(collection_max(tmap));
	PRINTLN(collection_max(tset));
	PRINTLN(collection_max(rlist));
	PRINTLN(collection_max(rarray));
	PRINTLN(collection_max(rmap));
	PRINTLN(collection_max(rset));

	dealloc:
	unlink_node(&elist);
	print_node_stack();

	unlink_node(&earray);
	print_node_stack();

	unlink_node(&emap);
	print_node_stack();

	unlink_node(&eset);
	print_node_stack();

	unlink_node(&tlist);
	print_node_stack();

	unlink_node(&tarray);
	print_node_stack();

	unlink_node(&tmap);
	print_node_stack();

	unlink_node(&tset);
	print_node_stack();

	unlink_node(&rlist);
	print_node_stack();

	unlink_node(&rarray);
	print_node_stack();

	unlink_node(&rmap);
	print_node_stack();

	unlink_node(&rset);
	print_node_stack();

	writer_curr_close();
	print_node_stack();
}


void test_list()
{
	test_list1();
}

