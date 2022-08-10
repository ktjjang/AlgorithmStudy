#include <stdio.h>
#include "list.h"

#define	MAX_ALLOC (1<<15)
struct list_head head;

struct foo {
	int a;
	int b;
	int c;
	int index;
	struct list_head node;
} foos[MAX_ALLOC];

struct foo *alloc_foo()
{
	static i = 0;
	if (++i == MAX_ALLOC) exit(-1);
	INIT_LIST_HEAD(&foos[i].node);
	foos[i].index = i;
	return &foos[i];
}

int main()
{
	printf("%d %d %d\n", offsetof(struct foo, a), offsetof(struct foo, b), offsetof(struct foo, c));
	printf("%x %x %x %x\n", &foos[0], containerof(&foos[0].a, struct foo, a), containerof(&foos[0].b, struct foo, b), containerof(&foos[0].c, struct foo, c));

	INIT_LIST_HEAD(&head);
	for (int i = 0; i < 20; i++) {
		struct foo *foo = alloc_foo();
		list_add(&head, &foo->node);
	}
		
	for_each_node(iter, &head)
	{
		printf("%d ", containerof(iter, struct foo, node)->index);
	}
	printf("\n");
}
