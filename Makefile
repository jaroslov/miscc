MAKEFLAGS			+=	--no-builtin-rules
.PHONY				= all

all: bt al as vn

CFLAGS	:= -O3

bt: btrie.h btrie.c
	clang $(CFLAGS) -I. btrie.c -o bt -Wall -Werror
	time ./bt abcdefghijklmnoqrstuvwxyz

al: alist.h alist.c
	clang $(CFLAGS) -I. alist.c -o al -Wall -Werror

as: astack.h astack.c
	clang $(CFLAGS) -I. astack.c -o as -Wall -Werror

vn: vnum.h vnum.c
	clang $(CFLAGS) -I. vnum.c -o vn -Wall -Werror

clean:
	rm -rf *.dSYM bt al as vn
