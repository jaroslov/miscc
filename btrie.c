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

#include <stdio.h>
#include <string.h>

#define BTRIE_C
#include "btrie.h"

volatile uint64_t RDTSC()
{
    uint32_t a;
    uint32_t d;
    asm volatile
        (".byte 0x0f, 0x31 #rdtsc\n" // edx:eax
         :"=a"(a), "=d"(d)::);
    return (((uint64_t) d) << 32) | (uint64_t) a;
}

int main(int argc, char *argv[])
{
    unsigned length     = 1;
    unsigned next       = 0;
    struct btrie* pool  = 0;
    unsigned X          = 0;
    int i = 0, j        = 0;
    char** refs         = 0;

    uint64_t start      = 0;
    uint64_t stop       = 0;
    uint64_t repeats    = 1000000;
    int numchars        = 0;
    uint64_t leninsert  = 0;
    uint64_t lenfetch   = 0;
    uint64_t lenif      = 0;
    uint64_t accumfetch = 0;

    for (i = 1; i < argc; ++i)
    {
        numchars    += strlen(argv[i]);
    }

    length              = numchars * CHAR_BIT * 2;
    pool                = (struct btrie*)malloc(sizeof(struct btrie) * length);
    refs                = (char**)malloc(sizeof(char*) * length);
    memset(pool, 0x0, sizeof(struct btrie) * length);

    start               = RDTSC();
    for (j = 0; j < repeats; ++j)
    {
        for (i = 1; i < argc; ++i)
        {
            X       = btrie_insert(pool, &next, argv[i], strlen(argv[i]) * CHAR_BIT);
            refs[X] = argv[i];
        }
    }
    stop                = RDTSC();
    leninsert           = stop - start;

    start               = RDTSC();
    for (j = 0; j < repeats; ++j)
    {
        for (int i = 1; i < argc; ++i)
        {
            X           = btrie_get(pool, argv[i], strlen(argv[i]) * CHAR_BIT);
            accumfetch  += (uint64_t)X;
        }
    }
    stop                = RDTSC();
    lenfetch            = stop - start;

    start               = RDTSC();
    for (j = 0; j < repeats; ++j)
    {
        for (i = 1; i < argc; ++i)
        {
            X       = btrie_insert(pool, &next, argv[i], strlen(argv[i]) * CHAR_BIT);
            refs[X] = argv[i];
        }

        for (int i = 1; i < argc; ++i)
        {
            X           = btrie_get(pool, argv[i], strlen(argv[i]) * CHAR_BIT);
            accumfetch  += (uint64_t)X;
        }
    }
    stop                = RDTSC();
    lenif               = stop - start;

    fprintf(stdout, "AccumFetch %llX\n", accumfetch);
    for (i = 1; i < argc; ++i)
    {
        X           = btrie_get(pool, argv[i], strlen(argv[i]) * CHAR_BIT);
        fprintf(stdout, "X: %4d %s\n", X, refs[X]);
    }

    fprintf(stdout, "      Insert cycles per char: %f\n", (double)(leninsert) / (repeats * numchars));
    fprintf(stdout, "       Fetch cycles per char: %f\n", (double)(lenfetch) / (repeats * numchars));
    fprintf(stdout, "Insert-Fetch cycles per char: %f\n", (double)(lenif) / (repeats * numchars));

    return 0;
}
