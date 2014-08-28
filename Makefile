all: btrie alist astack

btrie: btrie.h btrie.c
	clang -O3 -I. btrie.c -o bt -Wall -Werror
	time ./bt abcdefghijklmnoqrstuvwxyz

alist: alist.h alist.c
	clang -O3 -I. alist.c -o al -Wall -Werror

astack: astack.h astack.c
	clang -O3 -I. astack.c -o as -Wall -Werror

clean:
	rm -rf *.dSYM bt
