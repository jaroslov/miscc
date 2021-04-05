/*

Copyright (c) 2021, Jacob N. Smith
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

#ifndef WQUPC_H
#define WQUPC_H

struct wqupc
{
    int    *id;
    int    *sz;
};

int wqupc_init(struct wqupc* w, int n, int* id, int* sz);
int wqupc_root(struct wqupc* w, int i);
int wqupc_connected(struct wqupc* w, int i, int j);
int wqupc_union(struct wqupc* w, int i, int j);

#endif//WQUPC_H

#ifdef  WQUPC_C

int wqupc_init(struct wqupc* w, int n, int* id, int* sz)
{
    w->id       = id;
    w->sz       = sz;

    for (int II = 0; II < n; ++II)
    {
        w->id[II]   = II;
        w->sz[II]   = 1;
    }

    return 0;
}

int wqupc_root(struct wqupc* w, int i)
{
    while (i != w->id[i])
    {
        i   = w->id[i];
    }
    return i;
}

int wqupc_connected(struct wqupc* w, int i, int j)
{
    return wqupc_root(w, i) == wqupc_root(w, j);
}

int wqupc_union(struct wqupc* w, int i, int j)
{
    i   = wqupc_root(w, i);
    j   = wqupc_root(w, j);

    if (i == j) return 0;
    if (w->sz[i] < w->sz[j])
    {
        w->id[i]    = j;
        w->sz[j]    += w->sz[i];
    }
    else
    {
        w->id[j]    = i;
        w->sz[i]    += w->sz[j];
    }

    return 0;
}

#endif//WQUPC_C