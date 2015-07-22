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
	void *last_chunk;
} GC;

GC  *gc = NULL;

GC  *init_gc(){
	gc = malloc(sizeof(GC));
	if(!gc) {
		printf("Allocation error : garbage collector");
		return gc;
	}
	gc->chunk_list = NULL;
	gc->last_chunk = empty_chunk();
	if(!gc->last_chunk) {
		free(gc);
		gc = NULL;
		return NULL;
	}
	return gc;
}

void *create_node(void *node) {

}