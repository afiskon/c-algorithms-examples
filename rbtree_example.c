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
	bool isNew;
	TreeItemData item1, item2, item3;
	TreeItem tmp;

	rb_create(&tree, sizeof(TreeItemData), tree_comparator, tree_combiner, tree_allocfunc, tree_freefunc, NULL);

	strcpy(item1.data, "first item");
	strcpy(item2.data, "second item");
	strcpy(item3.data, "third item");

	printf("is empty before: %d\n", rb_leftmost(&tree) == NULL);
	rb_insert(&tree, (RBNode*)&item1, &isNew);
	rb_insert(&tree, (RBNode*)&item2, &isNew);
	rb_insert(&tree, (RBNode*)&item3, &isNew);
	printf("is empty after: %d\n", rb_leftmost(&tree) == NULL);

	rb_begin_iterate(&tree, LeftRightWalk);
	while(tmp = (TreeItem)rb_iterate(&tree))
	{
		printf("tmp->data = %s\n", tmp->data);
	}

	tmp = (TreeItem)rb_find(&tree, (RBNode*)&item2);
	if(tmp)
	{
		printf("item2 found, deleting\n");
		rb_delete(&tree, (RBNode*)tmp);
	}
	else
	{
		printf("item2 not found! :(\n");
	}

	rb_begin_iterate(&tree, LeftRightWalk);
	while(tmp = (TreeItem)rb_iterate(&tree))
	{
		printf("tmp->data = %s\n", tmp->data);
	}
}
