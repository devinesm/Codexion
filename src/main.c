#include "codexion.h"

void    print_error(void)
{
        printf("Usage: ./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>\n");
}

bool    is_valid_number(char *str)
{
        int     i;

        i = 0;
        while (str[i])
        {
                if (str[i] < '0' || str[i] > '9')
                        return (false);
                i++;
        }
        return (true);
}

int     parse_arguments(char **av)
{
        int     i;

        i = 1;
        while (i <= 7)
        {
                if (!is_valid_number(av[i]))
                        return (0);
                i++;
        }
        return (1);
}

void    fill_simulation(t_simulation *sim, char **av)
{
        sim->number_of_coders = atoi(av[1]);
        sim->time_to_burnout = atoi(av[2]);
        sim->time_to_compile = atoi(av[3]);
        sim->time_to_debug = atoi(av[4]);
        sim->time_to_refactor = atoi(av[5]);
        sim->number_of_compiles_required = atoi(av[6]);
        sim->dongle_cooldown = atoi(av[7]);
        
        if (strcmp(av[8], "fifo") == 0)
                sim->scheduler = 1;
        else
                sim->scheduler = 0;
                
        sim->stop_simulation = false;
        pthread_mutex_init(&sim->stop_simulation_mutex, NULL);
        pthread_mutex_init(&sim->print_mutex, NULL);
}

int     main(int ac, char **av)
{
        int             is_parsed;
        t_simulation    sim;

        if (ac == 9)
        {
                is_parsed = parse_arguments(av);
                if (is_parsed == 0)
                {
                        print_error();
                        return (1);
                }
                
                if (atoi(av[1]) > 0 && (strcmp(av[8], "fifo") == 0 || strcmp(av[8], "edf") == 0))
                {
                        fill_simulation(&sim, av);
                }
                else
                {
                        printf("Error: Simulation without any coder or not valid scheduler.\n");
                        return (1);
                }
        }
        else
        {
                print_error();
                return (1);
        }
        return (0);
}
