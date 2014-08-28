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

#ifndef ALIST_H
#define ALIST_H

struct alist_node
{
    unsigned prev;
    unsigned next;
};

typedef void(*alist_traverse_fn)(unsigned, void*);

void alist_append(struct alist_node* pool, unsigned* next);
void alist_insert(struct alist_node* pool, unsigned* next, unsigned itr);
void alist_erase(struct alist_node* pool, unsigned itr);
void alist_traverse(struct alist_node* pool, alist_traverse_fn, unsigned fst, unsigned lst, void* ctx);

#endif/*ALIST_H*/

#ifdef  ALIST_C

void alist_append(struct alist_node* pool, unsigned* next)
{
    unsigned itr    = 0;
    for (itr = 0; pool[itr].next; itr = pool[itr].next)
        ;
    pool[itr].next              = ++*next;
    pool[pool[itr].next].prev   = itr;
    pool[pool[itr].next].next   = 0;
}

void alist_insert(struct alist_node* pool, unsigned* next, unsigned itr)
{
    ++*next;
    pool[*next].next            = pool[itr].next;
    pool[*next].prev            = itr;
    pool[pool[itr].next].prev   = *next;
    pool[itr].next              = *next;
}

void alist_erase(struct alist_node* pool, unsigned itr)
{
    pool[pool[itr].next].prev   = pool[itr].prev;
    pool[pool[itr].prev].next   = pool[itr].next;
    pool[itr].next              = 0;
    pool[itr].prev              = 0;
}

void alist_traverse(struct alist_node* pool, alist_traverse_fn fn, unsigned fst, unsigned lst, void* ctx)
{
    for ( ; fst != lst; fst = pool[fst].next)
        fn(fst, ctx);
}

#endif/*ALIST_C*/
