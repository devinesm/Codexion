#ifndef CODEXION_H
# define CODEXION_H

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

typedef struct s_simulation t_simulation;
typedef struct s_coder t_coder;
typedef struct s_dongle t_dongle;
typedef struct s_heap_node t_heap_node;
typedef struct s_heap t_heap;

struct s_heap_node
{
	int		coder_id;
	size_t		request_time;
	size_t		deadline;
};

struct s_heap
{
	t_heap_node	*info;
	int		capacity;
	int		size;
};

struct s_dongle
{
	pthread_mutex_t	dongle_mutex;
	pthread_cond_t	cond_var;
	bool		in_use;
	size_t		last_released_time;
	t_heap		*waitlist;
};

struct s_coder
{
	int		coder_id;
	pthread_t	thread;
	t_dongle	*left;
	t_dongle	*right;
	t_simulation	*simulation;
	int		amount_of_compilations;
	size_t		start_of_last_compilation;
	pthread_mutex_t	coder_mutex;
};

struct s_simulation
{
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_coders;
	int		dongle_cooldown;
	int		number_of_compiles_required;
	int		scheduler; // 1 if FIFO, 0 if EDF
	size_t		start_time;
	bool		stop_simulation;
	pthread_mutex_t	stop_simulation_mutex;
	pthread_mutex_t	print_mutex;
};

/* Priority Queue Functions */
void		init_heap(t_heap *heap, int capacity);
void		push_heap(t_heap *heap, t_heap_node new_node, int scheduler);
t_heap_node	pop_heap(t_heap *heap, int scheduler);

#endif
