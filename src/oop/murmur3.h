/****
	murmur3 : hashing

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef MURMUR3_H
#define MURMUR3_H

WS_INT hashInt(WS_INT input);
WS_INT hashLong(WS_LONG input);
WS_INT hashUnencodedChars(char *input, WS_INT size);
WS_INT mixCollHash(WS_INT hash, WS_INT count);
WS_INT hashOrdered(Object *xs);
WS_INT hashUnordered(Object *xs);

#endif
