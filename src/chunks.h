/****
	Garbage collector's memory chuncks

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef CHUNKS_H
#define CHUNKS_H 0

char * create_empty_chunk();
void inc_chunk_disallocation(void *chunk);

#endif
