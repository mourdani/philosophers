/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <mourdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:01:59 by mourdani          #+#    #+#             */
/*   Updated: 2022/03/23 22:49:22 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	int	i;

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
		if (av[i][0] == '-' && ft_is_number(av[i]) != 0)
		{
			puterr("Error: Invalid Argument\n");
			return (1);
		}
	}
	return (0);
}

int	simulation(t_sim *table)
{
	if (start_philo_threads(table) == 1)
		return (1);
	if (start_dcheck_threads(table) == 1)
		return (1);
	while (table->death)
		continue ;
	return (0);
}

int	main(int ac, char **av)
{
	t_sim	*table;

	table = NULL;
	if (check_args(ac, av) != 0)
		return (1);
	table = init_table(ac, av);
	if (table == NULL)
		return (1);
	if (simulation(table) != 0)
		return (1);
	return (0);
}
