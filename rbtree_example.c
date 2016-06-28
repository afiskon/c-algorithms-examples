#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deps/algorithms/include/rbtree.h"

typedef struct
{
	RBNode node;
	char data[128];
} TreeItemData;

typedef TreeItemData *TreeItem;

int tree_comparator(const RBNode* a, const RBNode* b, void* arg)
{
	return strcmp(((const TreeItem)a)->data, ((const TreeItem)b)->data);
}

void tree_combiner(RBNode* existing, const RBNode* newdata, void* arg)
{
	/* do nothing */
}

RBNode* tree_allocfunc(void* arg)
{
	return malloc(sizeof(TreeItemData));
}

void tree_freefunc(RBNode* node, void* arg)
{
	free(node);
}

void main()
{
	RBTree tree;
	TreeItemData item1, item2, item3;

	rb_create(&tree, sizeof(TreeItemData), tree_comparator, tree_combiner, tree_allocfunc, tree_freefunc, NULL);

	strcpy(item1.data, "first item");
	strcpy(item2.data, "second item");
	strcpy(item3.data, "third item");

	printf("is empty before: %d\n", rb_leftmost(&tree) == NULL);

//	slist_push_head(&head, (slist_node*)&item1);
//	slist_push_head(&head, (slist_node*)&item2);
//	slist_push_head(&head, (slist_node*)&item3);

	printf("is empty after: %d\n", rb_leftmost(&tree) == NULL);

/*
	slist_foreach(iter, &head)
	{
		tmp = (ListItem) iter.cur;
		printf("tmp->data = %s\n", tmp->data);
	}

	tmp = (ListItem) slist_pop_head_node(&head);
	printf("After slist_pop_head_node call tmp->data = %s\n", tmp->data);

	slist_foreach(iter, &head)
	{
		tmp = (ListItem) iter.cur;
		printf("tmp->data = %s\n", tmp->data);
	}
*/
}
