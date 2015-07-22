/****
	Garbage collector's memory chuncks

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "chunks.h"

#define CHUNK_SIZE 1000

deftype struct chunk_s {
	long            next_free;
	long            disallocated;
	void            *segments[CHUNK_SIZE];
	struct chunk_s  *next;
} chunk;

void *create_empty_chunk(){
	chunk *c = malloc(sizeof(chunk));
	if(!c){
		printf(err, "create_empty_chunk : Allocation error : Chunk\n");
		return NULL;
	}
	c->next_free = 0;
	c->disallocated = 0;
	c->next = NULL;
	for(int i=0; i < CHUNK_SIZE; i++){
		c->segments[i] = NULL;
	}
	return c;
}

void *add_to_chunk(void *chunk, *void *segment) {

}

void *del_from_chunk(void *chunk, *void *segment) {

}

void *inc_chunk_disallocation(void *chunk) {
	if(!chunk) {
		fprintf(err, "inc_chunc_disallocation : no chunk");
		return NULL;
	}
	((chunk *)chunk)->disallocated++;
}

void *get_next_chunk(void *chunk) {

}