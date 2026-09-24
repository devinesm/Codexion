#include "codexion.h"

void    print_error()
{
        printf("Usage: ./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>");
}

bool	is_valid_number(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
		i++;
	}
	return true;
}

int	parse_arguments(char **av)
{
	int	i;

	i = 1;
	while (i <= 7)
	{
		if (!is_valid_number(av[i]))
			return (0);
		i++;
	}
}

void	fill_simulation(char **av)
{
	t_simulation->number_of_coders = atoi(av[1]);
	t_simulation->time_to_burnout = atoi(av[2]);
	t_simulation->time_to_compile = atoi(av[3]);
	t_simulation->time_to_debug = atoi(av[4]);
	t_simulation->time_to_refactor = atoi(av[5]);
	t_simulation->number_of_compiles_required = atoi(av[6]);
	t_simulation->dongle_cooldown = atoi(av[7]);
	if (strcmp(av[8], "fifo"))
		t_simulation->scheduler = 1;
	else
		t_simulation->scheduler = 0;
	t_simulation->stop_simultation = false;
	pthread_mutex_init(&simulation->stop_simulation_mutex, NULL);
	pthread_mutex_init(&simulation->print_mutex, NULL);
}

int	main(int ac, char **av)
{
	int	is_parsed;
	if (ac == 9)
		is_parsed = parse_arguments(av);
		if (is_parsed == 0)
		{
			print_error();
			return (1);
		}
		if (atoi(av[1]) > 0 && (strcmp(av[8], "fifo") || strcmp(av[8], "edf"))
			fill_simulation(av);
		else
		{
			printf("Error: Simulation without any coder or not valid scheduler.");
			return (1);
		}
	else
	{
		print_error();
		return (1);
        }
}
