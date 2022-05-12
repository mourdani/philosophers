/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 07:13:25 by mourdani          #+#    #+#             */
/*   Updated: 2022/04/29 20:02:02 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	puterr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		write(2, &str[i++], 1);
}

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
	t_sim	table;

	if (check_args(ac, av) != 0)
		return (1);
	if (init_table(&table, ac, av) == 1)
		return (1);
	init_threads(&table);
	join_threads(&table);
	unlock_and_destroy_mutex(&table);
	free_all(&table);
	return (0);
}
