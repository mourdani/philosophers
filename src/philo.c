/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <mourdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:01:59 by mourdani          #+#    #+#             */
/*   Updated: 2022/03/27 23:48:59 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_args(int ac, char **av)
{
	int		i;

	i = 0;
	if (ac - 1 < 4 || ac - 1 > 5)
	{
		puterr("Error: Invalid Argument\n");
		puterr("Usage: ./philo 	number_of_philosopers ");
		puterr("time_to_die time_to_eat time_to_sleep ");
		puterr("[number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	while (++i < ac)
	{
		if (av[i][0] == '-' || ft_is_number(av[i]) == 1)
		{
			puterr("Error: Invalid Argument\n");
			return (1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_sim	*table;

	table = ft_memalloc(sizeof(t_sim));
	if (check_args(ac, av) != 0)
		return (1);
	table = init_table(av, ac, table);
	if (table->philo == NULL)
		return (1);
	init_threads(table);
	usleep(1000);
	free(table->philo);
	free(table->forks);
	free(table);
	return (0);
}
