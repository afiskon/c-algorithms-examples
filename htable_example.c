#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "deps/algorithms/include/htable.h"

typedef struct
{
	HTableNode node;
	char expression[128];
	int value;
} ExpressionTableNodeData;

typedef ExpressionTableNodeData *ExpressionTableNode;

bool keyeq_func(const HTableNode a_, const HTableNode b_, void *arg)
{
	ExpressionTableNode a = (ExpressionTableNode)a_;
	ExpressionTableNode b = (ExpressionTableNode)b_;
	return (strcmp(a->expression, b->expression) == 0);
}

uint32_t hash_func(const HTableNode a_, void *arg)
{
	ExpressionTableNode a = (ExpressionTableNode)a_;
	return htable_default_hash(a->expression, strlen(a->expression));
}

void* alloc_func(size_t size, void *arg)
{
	return malloc(size);
}

void free_func(void* mem, void *arg)
{
	free(mem);
}

void before_node_free_func(HTableNode node, void *arg)
{
	/* do nothing */
}

int main()
{
	int i, j;
	HTableData htable;

	htable_create(
			&htable,
			sizeof(ExpressionTableNodeData),
			hash_func,
			keyeq_func,
			alloc_func,
			free_func,
			before_node_free_func,
			NULL
		);

	/* fill table */
	for(i = 1; i <= 100; i++)
	{
		for(j = 1; j <= 100; j++)
		{
			bool isNewNode;
			ExpressionTableNodeData new_node_data;
			sprintf(new_node_data.expression, "%d + %d", i, j);
			new_node_data.value = i + j;
			htable_put(&htable, (HTableNode)&new_node_data, &isNewNode);
			assert(isNewNode);
		}
	}

//	printf("Total number of items: %d\n", htable_nitems(&

	/* check hash table is filled right */

// TODO

	return 0;
}
