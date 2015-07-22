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

void *empty_chunk(){
	chunk *c = malloc(sizeof(chunk));
	if(!c){
		printf(err, "Allocation error : Chunk");
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