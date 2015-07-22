/****
	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "segment.h"
#include "chunks.h"

/*
    Struct of segment
*/
typedef struct {
	void    *node;
	void    *chunk;
	long    occurences;
} segment;

/*
	Struct to get the segment address of node
*/
typedef struct {
	TYPES   type;
	segment *segmemt;
} node_segment;

/*
	Create a new segment for node
*/
void *new_segment(void *node) {
	if(!*node) {
		fprintf(err, "new_segment : creating a segment with no node\n");
	}
	segment *seg = malloc(sizeof(segment));
	if(!seg) {
		printf(err, "new_segment : Allocation error : Segment\n");
		return NULL;
	}
	seg->node = node;
	seg->occurences = 0;
	return link_segment(seg);
}

/*
	Decrement nb occurences of node
	Dealloc and init segment if occurences == 0
*/
void *unlink_segment(void *segment) {
	segment *seg = segment;
	if(!seg->node) {
		fprintf(err, "unlink_segment : Segment error : not linked to a node\n");
		return NULL;
	}
	seg->occurences--;
	if(seg->occurences > 0)
		return seg;
	free_node(seg->node);
	seg->node = NULL;
	inc_chunk_disallocation(seg->chunk);
	return NULL;
}

/*
	Increment nb occurences of node
*/
void *link_segment(void *segment) {
	segment *seg = segment;
	if(!seg->node) {
		fprintf(err, "link_segment : Segment error : not linked to a node\n");
	}
	seg->occurences++;
	return seg;
}

/*
	Obtain segment of the node
*/
void *get_node_segment(void *node) {
	return ((node_segment *)node)->segment;
}