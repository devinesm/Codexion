#ifndef CODEXION_H
# define CODEXION_H

#include <stddef.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct simulation t_simulation;

typedef struct dongle
{
	// NOT DONE YET
} t_dongle;

typedef struct coder
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

typedef struct simulation
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
