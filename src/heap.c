#include "codexion.h"

void            init_heap(t_heap *heap, int capacity)
{
	heap->info = malloc(capacity * sizeof(t_heap_node));
	if (!heap->info)
	{
		printf("[ERROR] Malloc failed to allocate memory for the heap in init_heap.\n");
		return ;
	}
	heap->capacity = capacity;
	heap->size = 0;
}

static bool	is_higher_priority(t_heap_node a, t_heap_node b, int scheduler)
{
	if (scheduler == 1)
	{
		if (a.request_time < b.request_time)
			return (true);
	}
	else
	{
		if (a.deadline < b.deadline)
			return (true);
		else if (a.dealine == b.deadline)
		{
			if (a.request_time < b.request_time)
				return (true);
		}
	}
	return (false);
}

void            push_heap(t_heap *heap, t_heap_node new_node, int scheduler)
{
	int		i;
	int		parent;
	t_heap_node	tmp;

	if (heap->size == heap->capacity)
		return ;
	i = heap->size;
	heap->info[i] = new_node;
	heap->size++;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (is_higher_priority(heap->info[i], heap->info[parent], scheduler))
		{
			tmp = heap->info[parent];
			heap->info[parent] = heap->info[i];
			heap->info[i] = tmp;
			i = parent;
		}
		else
			break;
	}
}

t_heap_node     pop_heap(t_heap *heap, int scheduler)
{
	t_heap_node	root;
	t_heap_node	tmp;
	int		i;
	int		left;
	int		right;
	int		winner;

	if (heap->size <= 0)
	{
		root.coder_id = -1;
		return (root);
	}
	root = heap->info[0];
	heap->size--;
	if (heap->size > 0)
	{
		heap->info[0] = heap->info[heap->size];
		i = 0;
		while (true)
		{
			left = 2 * i + 1;
			right = 2 * i + 2;
			winner = i;
			if (left < heap->size && is_higher_priority(heap->info[left], heap->info[winner], scheduler))
				winner = left;
			if (right < heap->size && is_higher_priority(heap->info[right], heap->info[winner], scheduler))
                                winner = right;
			if (winner == i)
				break;
			tmp = heap->info[i];
			heap->info[i] = heap->info[winner];
			heap->info[winner] = tmp;
			i = winner;
		}
	}
	return (root);
}
