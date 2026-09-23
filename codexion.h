#ifndef CODEXION_H
# define CODEXION_H

#include <stddef.h>
#include <stdbool.h>
#include <pthread.h>

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
