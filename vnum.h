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

#ifndef VNUM_H
#define VNUM_H

#ifdef __cpluscplus
extern "C"
{
#endif

int layout_vnum(unsigned long long N, unsigned long long* poN);
unsigned long long extract_vnum(unsigned long long N, int *poN);

#ifdef __cpluscplus
}// end extern "C".
#endif

#endif//VNUM_H

#ifdef  VNUM_C

int layout_vnum(unsigned long long N, unsigned long long* poN)
{
    N   = ((N & 0x00FFFFFFF0000000ULL) << 4)
        | ((N & 0x000000000FFFFFFFULL) << 0)
        ;
    N   = ((N & 0x0FFFC0000FFFC000ULL) << 2)
        | ((N & 0x00003FFF00003FFFULL) << 0)
        ;
    N   = ((N & 0x3F803F803F803F80ULL) << 1)
        | ((N & 0x007F007F007F007FULL) << 0)
        ;

    int clz = __builtin_clzll(N);
    clz     /= 8;
    unsigned long long mask = 0x8080808080808080ULL;
    mask                    >>= (clz * 8);
    mask                    &= ~0x80ULL;

    *poN    = (N | mask);

    return 8 - clz;
}

unsigned long long extract_vnum(unsigned long long N, int *poN)
{
    unsigned long long error    = (0x80 & N) >> 7;
    unsigned codes  = ((N >> (56 + 0)) & 0x80)
                    | ((N >> (48 + 1)) & 0x40)
                    | ((N >> (40 + 2)) & 0x20)
                    | ((N >> (32 + 3)) & 0x10)
                    | ((N >> (24 + 4)) & 0x08)
                    | ((N >> (16 + 5)) & 0x04)
                    | ((N >> ( 8 + 6)) & 0x02)
                    | ((N >> ( 0 + 7)) & 0x01)
                    ;
    codes           >>= 1;
    codes           = ~codes;
    int ctz         = __builtin_ctz(codes);
    ctz             += 1;

    *poN            = (~(0 - error))
                    & ctz
                    ;

    N               &= (0xFFFFFFFFFFFFFFFFULL >> (8 * (8 - ctz)));

    N               = ((N & 0x7F007F007F007F00ULL) >> 1)
                    | ((N & 0x007F007F007F007FULL) >> 0)
                    ;
    N               = ((N & 0x3FFF00003FFF0000ULL) >> 2)
                    | ((N & 0x00003FFF00003FFFULL) >> 0)
                    ;
    N               = ((N & 0x0FFFFFFF00000000ULL) >> 4)
                    | ((N & 0x000000000FFFFFFFULL) >> 0)
                    ;
    return N;
}

#endif//VNUM_C
