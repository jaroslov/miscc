/*

Copyright (c) 2017, Jacob N. Smith
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

#define VNUM_C
#include "vnum.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef DEFINE_C
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    unsigned long long Out  = 0;

    int nBytes              = layout_vnum(strtoull(argv[1], 0, 0), &Out);

    fprintf(stdout,
        "COUNT: %d\n"
        "    0x%llX\n"
        "%s",
        nBytes,
        Out,
        "");

    int nCount              = 0;

    unsigned long long Rec  = extract_vnum(Out, &nCount);

    fprintf(stdout,
        "COUNT: %d\n"
        "    0x%llX\n"
        "%s",
        nCount,
        Rec,
        "");

    return 0;
}
#endif//DEFINE_C
