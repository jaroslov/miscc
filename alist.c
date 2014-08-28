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

#define ALIST_C
#include "alist.h"

#include <stdio.h>
#include <stdlib.h>

void alist_say(unsigned itr, void* ctx)
{
    (void)ctx;
    fprintf(stdout, "   HERE %d\n", itr);
}

int main(int argc, char *argv[])
{
    unsigned next           = 0;
    struct alist_node* pool = (struct alist_node*)calloc(sizeof(struct alist_node), 20);

    alist_append(pool, &next); fprintf(stdout, "ITR: %d\n", next);
    alist_append(pool, &next); fprintf(stdout, "ITR: %d\n", next);
    alist_append(pool, &next); fprintf(stdout, "ITR: %d\n", next);
    alist_append(pool, &next); fprintf(stdout, "ITR: %d\n", next);
    alist_append(pool, &next); fprintf(stdout, "ITR: %d\n", next);
    alist_append(pool, &next); fprintf(stdout, "ITR: %d\n", next);

    alist_erase(pool, 2);
    alist_erase(pool, 4);

    alist_traverse(pool, alist_say, 1, 6, 0);

    return 0;
}
