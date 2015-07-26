/****
	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "types.h"

/*
	global initialization
*/
static bool init_all() {
	return  init_node_list() ||
			init_types();
}

/*
	main entry point
*/
int main(int argc, const char* argv[]) {
	if(!init_all()) {
		error("Can't init language\n");
		return -1;
	}
	print_node_list();
	return 0;
}

