/****
	murmur3 : hashing

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef MURMUR3_H
#define MURMUR3_H

#include "nodes.h"

unsigned int hashInt(unsigned int input);
unsigned int hashLong(long input);
unsigned int hashUnencodedChars(char *input, unsigned int size);
unsigned int mixCollHash(unsigned int hash, unsigned int count);
unsigned int hashOrdered(Node xs);
unsigned int hashUnordered(Node xs);

#endif
