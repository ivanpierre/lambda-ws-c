/****
	Garbage collector

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "chunks.h"

typedef struct {
	void *chunk_list;
} GC;

GC  *gc = NULL;

/*
	initialize garbage collector
*/
void *init_gc(){
	gc = malloc(sizeof(GC));
	if(!gc) {
		printf("init_gc :Allocation error : garbage collector\n");
		return gc;
	}
	gc->chunk_list = empty_chunk();
	if(!gc->last_chunk) {
		free(gc);
		gc = NULL;
		return NULL;
	}
	return gc;
}

/*
	Add a link to the node, creating the segment if needed
*/
void *link_gc(void *node) {

}

/*
	Suppress link to the node, un allocating it if no more link
*/
void *unlink_gc(void *node) {

}
