/*
 * Copyright (C) 2011 The Guava Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 */

/*
 * MurmurHash3 was written by Austin Appleby, and is placed in the public
 * domain. The author hereby disclaims copyright to this source code.
 */

/*
 * Source:
 * http://code.google.com/p/smhasher/source/browse/trunk/MurmurHash3.cpp
 * (Modified to adapt to Guava coding conventions and to use the HashFunction interface)
 */

/**
 * Modified to remove stuff Clojure doesn't need, placed under clojure.lang namespace,
 * all fns made static, added hashOrdered/Unordered
 */

/**
 * Adapted to C by Ivan Pierre <ivan@kilroysoft.ch>
*/

/**
 * See http://smhasher.googlecode.com/svn/trunk/MurmurHash3.cpp
 * MurmurHash3_x86_32
 *
 * @author Austin Appleby
 * @author Dimitris Andreou
 * @author Kurt Alfred Kluever
 */

#include <stdio.h>
#include "murmur3.h"

const WS_INT seed = 0;
const WS_INT C1 = 0xcc9e2d51;
const WS_INT C2 = 0x1b873593;
const WS_INT C3 = 0xe6546b64;
const WS_INT C4 = 0x85ebca6b;
const WS_INT C5 = 0xc2b2ae35;

static WS_INT rotateLeft(WS_INT x, WS_INT n)
{
  return (x << n) | (x >> (sizeof(WS_INT) - n));
}

static WS_INT mixK1(WS_INT k1)
{
	k1 *= C1;
	k1 = rotateLeft(k1, 15);
	k1 *= C2;
	return k1;
}

static WS_INT mixH1(WS_INT h1, WS_INT k1)
{
	h1 ^= k1;
	h1 = rotateLeft(h1, 13);
	h1 = h1 * 5 + C3;
	return h1;
}

// Finalization mix - force all bits of a hash block to avalanche
static WS_INT fmix(WS_INT h1, WS_INT length)
{
	h1 ^= length;
	h1 ^= h1 >> sizeof(WS_SHORT);
	h1 *= C4;
	h1 ^= h1 >> 13;
	h1 *= C5;
	h1 ^= h1 >> sizeof(WS_SHORT);
	return h1;
}

WS_INT hashInt(WS_INT input)
{
	if(input == 0) return 0;
	WS_INT k1 = mixK1(input);
	WS_INT h1 = mixH1(seed, k1);

	return fmix(h1, 4);
}

WS_INT hashLong(WS_LONG input)
{
	if(input == 0) return 0;
	WS_INT low = (WS_INT) input;
	WS_INT high = (WS_INT) (input >> sizeof(WS_INT));

	WS_INT k1 = mixK1(low);
	WS_INT h1 = mixH1(seed, k1);

	k1 = mixK1(high);
	h1 = mixH1(h1, k1);

	return fmix(h1, 8);
}

WS_INT hashUnencodedChars(char *input, WS_INT size)
{
	WS_INT h1 = seed;

	// step through the CharSequence 2 chars at a time
	for(long i = 1; i < size; i += 2)
		{
		WS_INT k1 = input[i - 1] | (input[i] << sizeof(WS_SHORT));
		k1 = mixK1(k1);
		h1 = mixH1(h1, k1);
		}

	// deal with any remaining characters
	if((size & 1) == 1)
		{
		WS_INT k1 = input[size - 1];
		k1 = mixK1(k1);
		h1 ^= k1;
		}

	return fmix(h1, 2 * size);
}

WS_INT mixCollHash(WS_INT hash, WS_INT count)
{
	WS_INT h1 = seed;
	WS_INT k1 = mixK1(hash);
	h1 = mixH1(h1, k1);
	return fmix(h1, count);
}

/* TODO implement when we have iterators
WS_INT hashOrdered(Object *xs)
{
	WS_INT n = 0;
	WS_INT hash = 1;

	for(Object x : xs)
		{
		hash = 31 * hash + Util.hasheq(x);
		++n;
		}

	return mixCollHash(hash, n);
}

WS_INT hashUnordered(Object *xs)
{
	WS_INT hash = 0;
	WS_INT n = 0;
	for(Object x : xs)
		{
		hash += Util.hasheq(x);
		++n;
		}

	return mixCollHash(hash, n);
}
*/
