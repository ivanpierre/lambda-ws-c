/****
	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "segment.h"
#include "chunks.h"

typedef struct {
	void    *node;
	void    *chunk;
	long    occurences;
} segment;

void *new_segment(void *node) {
	if(!*node) {
		fprintf(err, "Segment error : creating a segment with no node\n");
	}
	segment *seg = malloc(sizeof(segment));
	if(!seg) {
		printf(err, "Allocation error : Segment\n");
		return NULL;
	}
	seg->node = node;
	seg->occurences = 1;
}

void *unlink_segment(void *segment) {
	segment *seg = segment;
	if(!seg->node) {
		fprintf(err, "Segment error : not linked to a node\n");
	}
	seg->occurences--;
	if(seg->occurences > 0)
		return NULL;
	free_node(seg->node);
	seg->node = NULL;
	inc_chunk_disallocation(seg->chunk);
	return NULL;
}