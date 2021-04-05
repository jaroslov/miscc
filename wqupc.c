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

#define WQUPC_C
#include "wqupc.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int id[49]      = { };
    int sz[49]      = { };

    struct wqupc w  = { };

    wqupc_init(&w, 49, &id[0], &sz[0]);

    wqupc_union(&w, 2, 3);
    wqupc_union(&w, 3, 5);
    wqupc_union(&w, 3, 7);
    wqupc_union(&w, 7, 11);
    wqupc_union(&w, 41, 43);
    wqupc_union(&w, 29, 31);
    wqupc_union(&w, 37, 13);
    wqupc_union(&w, 17, 19);
    wqupc_union(&w, 23, 29);
    wqupc_union(&w, 29, 47);
    wqupc_union(&w, 43, 47);
    wqupc_union(&w, 41, 47);
    wqupc_union(&w, 13, 47);
    wqupc_union(&w, 3, 47);

    fprintf(stdout, "connected? %d %d\n",
        wqupc_connected(&w, 2, 4),
        wqupc_connected(&w, 2, 41));

    return 0;
}
