/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 02:18:16 by mourdani          #+#    #+#             */
/*   Updated: 2022/03/16 03:24:58 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// = PTHREAD_MUTEX_INITIALIZER;
int	check_args(int ac, char **av)
{
	int i;

	i = 0;
	if (ac > 6 || ac < 5)
		return (ERROR);
	printf("%s \n", av[0]);
	while (i++ < ac - 1)
	{
		if (av[i][0] == '-' && ft_is_number(av[i]) != OK)
			return (ERROR);
	}
	return (OK);
}

pthread_mutex_t	*init_forks(t_table table)
{
	pthread_mutex_t	*forks;
	int	i;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table.np);
	if (forks == NULL)
		return (NULL);
	while (i < table.np)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

t_philo	**init_philos(t_table table)
{
	t_philo **philos;
	int i;

	i = 0;
	philos = (t_philo **)malloc(sizeof(t_philo **) * table.np);
	if (philos == NULL)
		return (NULL);
	while (i < table.np)
	{
		philos[i]->id = i;
		philos[i]->nta = 0;
		philos[i]->lf = i;
		philos[i]->rf = (i + 1) % philos[i]->table->np;

	}
}

t_table	fill_table(int ac, char **av)
{
	t_table table;
	int i;

	i = 1;
	table.np = ft_atoi(av[i++]);
	table.ttd = ft_atoi(av[i++]);
	table.tte = ft_atoi(av[i++]);
	table.tts = ft_atoi(av[i++]);
	if (ac == 6)
		table.ntpe = ft_atoi(av[i]);
	else 
		table.ntpe = -1;
	table.forks = init_forks(table);
	if (table.forks == NULL)
		return (NULL);
	table.philo = init_philos(table);
	if (table.philo == NULL)
		return (NULL);

	return (table);
}

int	main(int ac, char **av)
{
	t_table table;

	if (check_args(ac, av) != OK)
	{
		puterr("Error: Invalid Argument\n");
		puterr("USAGE: ./philo 	number_of_philosopers ");
		puterr("time_to_die time_to_eat time_to_sleep ");
		puterr("[number_of_times_each_philosopher_must_eat]");
		return (ERROR);
	}
	table = fill_table(ac, av);
	printf("working!!\n");
	printf("------------------------------------------------------\n");
	printf("number of philosophers: %d \n", table.np);
	printf("time to die : %d \n", table.ttd);
	printf("time to eat : %d \n", table.tte);
	printf("time to sleep : %d \n", table.tts);
	printf("must eat n times: %d \n", table.ntpe);
	return (0);
}






// TESTING
//	printf("working!!\n");
//	printf("------------------------------------------------------\n");
//	printf("number of philosophers: %d \n", table.np);
//	printf("time to die : %d \n", table.ttd);
//	printf("time to eat : %d \n", table.tte);
//	printf("time to sleep : %d \n", table.tts);
//	printf("must eat n times: %d \n", table.ntpe);
