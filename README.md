BTRIE
=====

Implements a 'pure' binary trie. The 'purity' means that the btrie
data structure contains no data other than trie nodes. Using btrie
simply means including 'btrie.h' as a header file; the source
code can be imported by declaring 'BTRIE_C' and then including the
header file, again.

The API is:

    unsigned btrie_get(struct btrie* pool, void* key, unsigned keylen);
    unsigned btrie_insert(struct btrie* pool, unsigned* next, void* key, unsigned keylen);
    int btrie_estimate(unsigned length, unsigned next, unsigned keylen);

The _pool_ is an array of btrie nodes. The client is responsible for
properly sizing the pool. Calls to `btrie_get` are always well-defined,
given that the _pool_ hasn't been messed with. Calls to `btrie_insert`
are only well-defined if the _pool_ is large enough. The size of the
_pool_'s array can be estimated by making a call to `btrie_estimate`
and passing in the current length of the _pool_, the last used pool
element, and the size of the key to be inserted.

Note that 'keylen' is the size of the key in **bits**.

ALIST
=====

Implements a 'pure' doubly-linked list. The 'purity' means that the
list data structure contains no data other than list nodes. Using
the list means including 'alist.h' as a header file; the source code
can be imported by declaring 'ALIST_C', and then including the
header file, again.

The API is:

    typedef void(*alist_traverse_fn)(unsigned, void*);
    void alist_append(struct alist_node* pool, unsigned* next);
    void alist_insert(struct alist_node* pool, unsigned* next, unsigned itr);
    void alist_erase(struct alist_node* pool, unsigned itr);
    void alist_traverse(struct alist_node* pool, alist_traverse_fn, unsigned fst, unsigned lst, void* ctx);

The function `alist_append` adds a new node to the end of the list.
The function `alist_insert` inserts a node just before the iterator.
The function `alist_erase` erases the node referred to by the
iterator. The function `alist_travserse` traverses the list from
`fst` up to, but not including, `lst`; at each node, the
callback function is called with the current iterator, and the user's
context.

There are a few invariants that must be maintained:

  1. Do not erase pool[0]; this is the head-word and has different
     semantics from the rest of the list;
  2. The first iterator in the list is always pool[0].next; and,
  3. The last iterator in the list is always '0'.

ASTACK
======

Implments a 'pure' stack, implemented as a singly-linked list.
The 'purity' means that the underlying singly-linked list data
structure contains no data other than stack nodes. Using the stack
means include 'astack.h' as a header file; the source code can
be imported by declaring 'ASTACK_C', and then including the
header file, again.

The API is:

    void astack_push(struct astack_node* pool, unsigned next);
    unsigned astack_pop(struct astack_node* pool);

The function `astack_push` pushes the pool item referred to by
'next' onto the stack. The function `astack_pop` pops the top
element off the stack and returns its iterator.

Note that the ASTACK is designed in such a way that by scaling
the iterator references, it can be used as an integrated free-list.
For instance, by multiplying the iterator by '2', it can be
integrated into an ALIST pool as a free-stack for the location
of free nodes.
