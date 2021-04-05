#!/usr/bin/env make -f
MAKEFLAGS			+=	--no-builtin-rules
.PHONY				= all

all: bt al as vn wq

CFLAGS	:= -O3

bt: btrie.h btrie.c
	clang $(CFLAGS) -I. $(word 2,$^) -o $@ -Wall -Werror
	time ./bt abcdefghijklmnoqrstuvwxyz

al: alist.h alist.c
	clang $(CFLAGS) -I. $(word 2,$^) -o $@ -Wall -Werror

as: astack.h astack.c
	clang $(CFLAGS) -I. $(word 2,$^) -o $@ -Wall -Werror

vn: vnum.h vnum.c
	clang $(CFLAGS) -I. $(word 2,$^) -o $@ -Wall -Werror

wq: wqupc.h wqupc.c
	clang $(CFLAGS) -I. $(word 2,$^) -o $@ -Wall -Werror

clean:
	rm -rf *.dSYM bt al as vn wq
