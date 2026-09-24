#ifndef CODEXION_H
# define CODEXION_H

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

typedef struct s_simulation t_simulation;
typedef struct s_coder t_coder;

typedef struct s_heap
{
	t_coder		**info;
	int		capacity;
	int		size;
} t_heap;

typedef struct s_dongle
{
	pthread_mutex_t	dongle_mutex;
	pthread_cond_t	cond_var;
	bool		in_use;
	size_t		last_released_time;
	t_heap		*waitlist;
} t_dongle;

typedef struct s_coder
{
	int		coder_id;
	pthread_t	thread;
	t_dongle	*left;
	t_dongle	*right;
	t_simulation	*simulation;
	int		amount_of_compilations;
	size_t		start_of_last_compilation;
	pthread_mutex_t	coder_mutex;
} t_coder;

typedef struct s_simulation
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
} t_simulation;

#endif
