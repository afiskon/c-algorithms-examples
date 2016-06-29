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

static int
tree_comparator(const RBNode* a, const RBNode* b, void* arg)
{
	return strcmp(((const TreeItem)a)->data, ((const TreeItem)b)->data);
}

static void
tree_combiner(RBNode* existing, const RBNode* newdata, void* arg)
{
	/* do nothing */
}

static RBNode*
tree_allocfunc(void* arg)
{
	return malloc(sizeof(TreeItemData));
}

static void
tree_freefunc(RBNode* node, void* arg)
{
	free(node);
}

void main()
{
	RBTree tree;
	bool isNew;
	TreeItemData item;
	TreeItem tmp;

	rb_create(&tree, sizeof(TreeItemData), tree_comparator, tree_combiner, tree_allocfunc, tree_freefunc, NULL);

	printf("is empty before: %d\n", rb_leftmost(&tree) == NULL);

	strcpy(item.data, "first item");
	rb_insert(&tree, (RBNode*)&item, &isNew);

	strcpy(item.data, "second item");
	rb_insert(&tree, (RBNode*)&item, &isNew);

	strcpy(item.data, "third item");
	rb_insert(&tree, (RBNode*)&item, &isNew);

	printf("is empty after: %d\n", rb_leftmost(&tree) == NULL);

	rb_begin_iterate(&tree, LeftRightWalk);
	while(tmp = (TreeItem)rb_iterate(&tree))
	{
		printf("tmp->data = %s\n", tmp->data);
	}

	strcpy(item.data, "second item");
	tmp = (TreeItem)rb_find(&tree, (RBNode*)&item);
	if(tmp)
	{
		printf("second item found, deleting\n");
		rb_delete(&tree, (RBNode*)tmp);
	}
	else
	{
		printf("second item not found! :(\n");
	}

	printf("is empty before: %d\n", rb_leftmost(&tree) == NULL);

	/* rb_begin_iterate + rb_iterate doesn't work here! */
	while(tmp = (TreeItem)rb_leftmost(&tree))
	{
		printf("tmp->data = %s\n", tmp->data);
		rb_delete(&tree, (RBNode*)tmp);
	}

	printf("is empty after: %d\n", rb_leftmost(&tree) == NULL);
}
