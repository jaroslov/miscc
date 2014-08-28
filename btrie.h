/*

Copyright (c) 2014, Jacob N. Smith
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1.  Redistributions of source code must retain the above copyright notice,
        this list of conditions and the following disclaimer.

    2.  Redistributions in binary form must reproduce the above copyright notice,
        this list of conditions and the following disclaimer in the documentation
        and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef BTRIE_H
#define BTRIE_H

#include <limits.h>
#include <stdlib.h>

struct btrie
{
    unsigned    branch[2];
};

unsigned btrie_get(struct btrie* pool, void* key, unsigned keylen);
unsigned btrie_insert(struct btrie* pool, unsigned* next, void* key, unsigned keylen);
int btrie_estimate(unsigned length, unsigned next, unsigned keylen);

#endif/*BTRIE_H*/

#ifdef  BTRIE_C

#include <assert.h>

#define BTRIE_RADIX         uint64_t
#define BTRIE_RADIX_BITS    (sizeof(BTRIE_RADIX) * CHAR_BIT)
#define BTRIE_RADIX_ROLL    (BTRIE_RADIX_BITS - 1)
#define BTRIE_RADIX_MASK    (BTRIE_RADIX_ROLL)

/*

    XXX: Unrolling these loops are tricky and not likely to improve things.

*/

unsigned btrie_get(struct btrie* pool, void* key, unsigned keylen)
{
    unsigned index  = 0, m = 0, i = 0;
    BTRIE_RADIX* radix  = (BTRIE_RADIX*)key;
    for (i = 0, m = (radix[0] & 0x1); i < keylen; ++i, m = ((radix[0] >> (i & BTRIE_RADIX_MASK)) & 0x1))
    {
        if (!pool[index].branch[m]) return 0;
        index       = pool[index].branch[m];
        if ((i % BTRIE_RADIX_BITS) == BTRIE_RADIX_ROLL) ++radix;
    }
    return index;
}

unsigned btrie_insert(struct btrie* pool, unsigned* next, void* key, unsigned keylen)
{
    unsigned index  = 0, m = 0, i = 0;
    BTRIE_RADIX* radix  = (BTRIE_RADIX*)key;
    for (i = 0, m = (radix[0] & 0x1); i < keylen; ++i, m = ((radix[0] >> (i & BTRIE_RADIX_MASK)) & 0x1))
    {
        if (!pool[index].branch[m])
        {
            ++*next;
            pool[index].branch[m] = *next;
            memset(pool + *next, 0x0, sizeof(struct btrie));
        }
        index       = pool[index].branch[m];
        if ((i % BTRIE_RADIX_BITS) == BTRIE_RADIX_ROLL) ++radix;
    }
    return index;
}

int btrie_estimate(unsigned length, unsigned next, unsigned keylen)
{
    return (int)keylen + 1 - (int)(length - next);
}

#endif/*BTRIE_C*/
