#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deps/algorithms/include/ilist.h"

typedef struct
{
	slist_node node;
	char data[128];
} ListItemData;

typedef ListItemData *ListItem;

void main()
{
	slist_iter iter;
	ListItemData item1, item2, item3;

	slist_head head;
	slist_init(&head);

	strcpy(item1.data, "first item");
	strcpy(item2.data, "second item");
	strcpy(item3.data, "third item");

	slist_push_head(&head, (slist_node*)&item1);
	slist_push_head(&head, (slist_node*)&item2);
	slist_push_head(&head, (slist_node*)&item3);

	slist_foreach(iter, &head)
	{
		ListItem item = (ListItem) iter.cur;
		printf("item->data = %s\n", item->data);
	}
}
