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

const unsigned int seed = 0;
const unsigned int C1 = 0xcc9e2d51;
const unsigned int C2 = 0x1b873593;

static unsigned int rotateLeft(unsigned int x, unsigned int n)
{
  return (x << n) | (x >> (32 - n));
}

static unsigned int mixK1(unsigned int k1)
{
	k1 *= C1;
	k1 = rotateLeft(k1, 15);
	k1 *= C2;
	return k1;
}

static unsigned int mixH1(unsigned int h1, unsigned int k1)
{
	h1 ^= k1;
	h1 = rotateLeft(h1, 13);
	h1 = h1 * 5 + 0xe6546b64;
	return h1;
}

// Finalization mix - force all bits of a hash block to avalanche
static unsigned int fmix(unsigned int h1, unsigned int length)
{
	h1 ^= length;
	h1 ^= h1 >> 16;
	h1 *= 0x85ebca6b;
	h1 ^= h1 >> 13;
	h1 *= 0xc2b2ae35;
	h1 ^= h1 >> 16;
	return h1;
}

unsigned int hashInt(unsigned int input)
{
	if(input == 0) return 0;
	unsigned int k1 = mixK1(input);
	unsigned int h1 = mixH1(seed, k1);

	return fmix(h1, 4);
}

unsigned int hashLong(long input)
{
	if(input == 0) return 0;
	unsigned int low = (unsigned int) input;
	unsigned int high = (unsigned int) (input >> 32);

	unsigned int k1 = mixK1(low);
	unsigned int h1 = mixH1(seed, k1);

	k1 = mixK1(high);
	h1 = mixH1(h1, k1);

	return fmix(h1, 8);
}

unsigned int hashUnencodedChars(char *input, unsigned int size)
{
	unsigned int h1 = seed;

	// step through the CharSequence 2 chars at a time
	for(long i = 1; i < size; i += 2)
		{
		unsigned int k1 = input[i - 1] | (input[i] << 16);
		k1 = mixK1(k1);
		h1 = mixH1(h1, k1);
		}

	// deal with any remaining characters
	if(size & 1) == 1)
		{
		unsigned int k1 = input[size - 1];
		k1 = mixK1(k1);
		h1 ^= k1;
		}

	return fmix(h1, 2 * size);
}

unsigned int mixCollHash(unsigned int hash, unsigned int count)
{
	unsigned int h1 = seed;
	unsigned int k1 = mixK1(hash);
	h1 = mixH1(h1, k1);
	return fmix(h1, count);
}

unsigned int hashOrdered(Node *xs)
{
	unsigned int n = 0;
	unsigned int hash = 1;

	for(Object x : xs)
		{
		hash = 31 * hash + Util.hasheq(x);
		++n;
		}

	return mixCollHash(hash, n);
}

unsigned int hashUnordered(Node *xs)
{
	unsigned int hash = 0;
	unsigned int n = 0;
	for(Object x : xs)
		{
		hash += Util.hasheq(x);
		++n;
		}

	return mixCollHash(hash, n);
}

