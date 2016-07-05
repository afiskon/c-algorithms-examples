#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include "deps/algorithms/include/rbtree.h"

#define NUM_TESTS 256

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

static void
tree_sprintfunc(RBNode* node, char* buff)
{
	strcpy(buff, ((TreeItemData*)node)->data);
}

static void
general_test()
{
	RBTree tree;
	bool isNew;
	TreeItemData item;
	TreeItem tmp;

	printf("\n=== GENERAL TEST ===\n\n");

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

static void
left_right_walk_test()
{
	RBTree tree1, tree2;
	TreeItem temp1, temp2;
	TreeItemData item;
	RBTreeLeftRightWalk lrw;
	bool isNew;
	int i, j;

	printf("\n=== LEFT RIGHT WALK TEST ===\n\n");

	rb_create(&tree1, sizeof(TreeItemData), tree_comparator, tree_combiner, tree_allocfunc, tree_freefunc, NULL);
	rb_create(&tree2, sizeof(TreeItemData), tree_comparator, tree_combiner, tree_allocfunc, tree_freefunc, NULL);

	for(i = 0; i < NUM_TESTS; i++)
	{
		printf("--- i = %d ---\n", i);

		rb_begin_iterate(&tree1, LeftRightWalk);
		rb_begin_left_right_walk(&tree2, &lrw);

		for(;;)
		{
			temp1 = (TreeItem)rb_iterate(&tree1);
			temp2 = (TreeItem)rb_left_right_walk(&lrw);
			if(!temp1)
			{
				assert(!temp2);
				break;
			}

			assert(temp2);
			printf("temp1->data = %s, temp2->data = %s\n", temp1->data, temp2->data);
			assert(strcmp(temp1->data, temp2->data) == 0);
		}

		j = rand() % 1000;
		sprintf(item.data, "val%d", j);
		rb_insert(&tree1, (RBNode*)&item, &isNew);
		rb_insert(&tree2, (RBNode*)&item, &isNew);
	}

	/* rb_begin_iterate + rb_iterate doesn't work here! */
	while(temp1 = (TreeItem)rb_leftmost(&tree1))
		rb_delete(&tree1, (RBNode*)temp1);
	while(temp2 = (TreeItem)rb_leftmost(&tree2))
		rb_delete(&tree2, (RBNode*)temp2);

	printf("\n=== LEFT RIGHT WALK TEST PASSED! ===\n\n");
	sleep(1);
}

static void
right_left_walk_test()
{
	RBTree tree1, tree2;
	TreeItem temp1, temp2;
	TreeItemData item;
	RBTreeRightLeftWalk rlw;
	bool isNew;
	int i, j;

	printf("\n=== RIGHT LEFT WALK TEST ===\n\n");

	rb_create(&tree1, sizeof(TreeItemData), tree_comparator, tree_combiner, tree_allocfunc, tree_freefunc, NULL);
	rb_create(&tree2, sizeof(TreeItemData), tree_comparator, tree_combiner, tree_allocfunc, tree_freefunc, NULL);

	for(i = 0; i < NUM_TESTS; i++)
	{
		printf("--- i = %d ---\n", i);

		rb_begin_iterate(&tree1, RightLeftWalk);
		rb_begin_right_left_walk(&tree2, &rlw);

		for(;;)
		{
			temp1 = (TreeItem)rb_iterate(&tree1);
			temp2 = (TreeItem)rb_right_left_walk(&rlw);
			if(!temp1)
			{
				assert(!temp2);
				break;
			}

			assert(temp2);
			printf("temp1->data = %s, temp2->data = %s\n", temp1->data, temp2->data);
			assert(strcmp(temp1->data, temp2->data) == 0);
		}

		j = rand() % 1000;
		sprintf(item.data, "val%d", j);
		rb_insert(&tree1, (RBNode*)&item, &isNew);
		rb_insert(&tree2, (RBNode*)&item, &isNew);
	}

	/* rb_begin_iterate + rb_iterate doesn't work here! */
	while(temp1 = (TreeItem)rb_leftmost(&tree1))
		rb_delete(&tree1, (RBNode*)temp1);
	while(temp2 = (TreeItem)rb_leftmost(&tree2))
		rb_delete(&tree2, (RBNode*)temp2);

	printf("\n=== RIGHT LEFT WALK TEST PASSED! ===\n\n");
	sleep(1);
}


static void
direct_walk_test()
{
	RBTree tree1, tree2;
	TreeItem temp1, temp2;
	TreeItemData item;
	RBTreeDirectWalk dw;
	bool isNew;
	int i, j;

	printf("\n=== DIRECT WALK TEST ===\n\n");

	rb_create(&tree1, sizeof(TreeItemData), tree_comparator, tree_combiner, tree_allocfunc, tree_freefunc, NULL);
	rb_create(&tree2, sizeof(TreeItemData), tree_comparator, tree_combiner, tree_allocfunc, tree_freefunc, NULL);

	for(i = 0; i < NUM_TESTS; i++)
	{
		printf("--- i = %d ---\n", i);

		rb_begin_iterate(&tree1, DirectWalk);
		rb_begin_direct_walk(&tree2, &dw);

		for(;;)
		{
			temp1 = (TreeItem)rb_iterate(&tree1);
			temp2 = (TreeItem)rb_direct_walk(&dw);
			if(!temp1)
			{
				assert(!temp2);
				break;
			}

			assert(temp2);
			printf("temp1->data = %s, temp2->data = %s\n", temp1->data, temp2->data);
			assert(strcmp(temp1->data, temp2->data) == 0);
		}

		j = rand() % 1000;
		sprintf(item.data, "val%d", j);
		rb_insert(&tree1, (RBNode*)&item, &isNew);
		rb_insert(&tree2, (RBNode*)&item, &isNew);
	}

	/* rb_begin_iterate + rb_iterate doesn't work here! */
	while(temp1 = (TreeItem)rb_leftmost(&tree1))
		rb_delete(&tree1, (RBNode*)temp1);
	while(temp2 = (TreeItem)rb_leftmost(&tree2))
		rb_delete(&tree2, (RBNode*)temp2);

	printf("\n=== DIRECT WALK TEST PASSED! ===\n\n");
	sleep(1);
}

static void
inverted_walk_test()
{
	RBTree tree1, tree2;
	TreeItem temp1, temp2;
	TreeItemData item;
	RBTreeInvertedWalk iw;
	bool isNew;
	int i, j;

	printf("\n=== INVERTED WALK TEST ===\n\n");

	rb_create(&tree1, sizeof(TreeItemData), tree_comparator, tree_combiner, tree_allocfunc, tree_freefunc, NULL);
	rb_create(&tree2, sizeof(TreeItemData), tree_comparator, tree_combiner, tree_allocfunc, tree_freefunc, NULL);

	for(i = 0; i < NUM_TESTS; i++)
	{
		printf("--- i = %d ---\n", i);

		rb_begin_iterate(&tree1, InvertedWalk);
		rb_begin_inverted_walk(&tree2, &iw);

		for(;;)
		{
			temp1 = (TreeItem)rb_iterate(&tree1);
			temp2 = (TreeItem)rb_inverted_walk(&iw);
			if(!temp1)
			{
				assert(!temp2);
				break;
			}

			assert(temp2);
			printf("temp1->data = %s, temp2->data = %s\n", temp1->data, temp2->data);
			assert(strcmp(temp1->data, temp2->data) == 0);
		}

		j = rand() % 1000;
		sprintf(item.data, "val%d", j);
		rb_insert(&tree1, (RBNode*)&item, &isNew);
		rb_insert(&tree2, (RBNode*)&item, &isNew);
	}

	/* rb_begin_iterate + rb_iterate doesn't work here! */
	while(temp1 = (TreeItem)rb_leftmost(&tree1))
		rb_delete(&tree1, (RBNode*)temp1);
	while(temp2 = (TreeItem)rb_leftmost(&tree2))
		rb_delete(&tree2, (RBNode*)temp2);

	printf("\n=== INVERTED WALK TEST PASSED! ===\n\n");
	sleep(1);
}


int main()
{
	struct timeval  tv;
	gettimeofday(&tv, NULL);
	srand(tv.tv_sec ^ tv.tv_usec);

	general_test();
	left_right_walk_test();
	right_left_walk_test();
	direct_walk_test();
	inverted_walk_test();
	return 0;
}
