#define offsetof(type, member) ((int)&(((type *)0)->member))
#define containerof(ptr, type, member) ((type *)((char *)ptr - offsetof(type, member)))
#define for_each_node(iter, head) for(struct list_head *iter = (head)->next; iter != head; iter = iter->next)

struct list_head {
	struct list_head *prev, *next;
};

inline void INIT_LIST_HEAD(struct list_head *head)
{
	head->prev = head;
	head->next = head;
}

void __list_add(struct list_head *prev, struct list_head *entry, struct list_head *next)
{
	next->prev = entry;
	entry->next = next;
	entry->prev = prev;
	prev->next = entry;
}

void list_add(struct list_head *head, struct list_head *entry)
{
	__list_add(head, entry, head->next);
}

void list_add_tail(struct list_head *head, struct list_head *entry)
{
	__list_add(head->prev, entry, head);
}

void __list_del(struct list_head *prev, struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}

void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->prev = 0;
	entry->next = 0;
}