/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <mourdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:36:31 by mourdani          #+#    #+#             */
/*   Updated: 2022/04/01 03:30:47 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_philos(t_sim *table)
{
	int	i;

	i = -1;
	while (++i < table->info.nop)
	{
		table->philo[i].nta = 0;
		table->philo[i].is_eating = 0;
		table->philo[i].r_f = i;
		table->philo[i].l_f = (i + 1) % table->info.nop;
		table->philo[i].pid = i + 1;
		table->philo[i].info = table->info;
		table->philo[i].table = table;
		table->philo[i].end = 1;
		table->philo[i].cdt = 1;
		pthread_mutex_init(&table->forks[i], NULL);
		pthread_mutex_init(&table->philo[i].eating, NULL);
	}
}

t_sim	*init_table(char **av, int ac, t_sim *table)
{
	table->philo = ft_memalloc(sizeof(t_philo) * (ft_atoi(av[1]) + 1));
	if (table->philo == NULL)
		return (NULL);
	table->forks = ft_memalloc(sizeof(pthread_mutex_t) \
		* (ft_atoi(av[1]) + 1));
	if (table->forks == NULL)
		return (NULL);
	pthread_mutex_init(&table->write, NULL);
	table->alive = 1;
	table->stop = 1;
	table->st = time_ms();
	table->info.nop = ft_atoi(av[1]);
	table->info.tdie = ft_atoi(av[2]);
	table->info.teat = ft_atoi(av[3]);
	table->info.tsleep = ft_atoi(av[4]);
	table->info.ntpme = -1;
	if (ac == 6)
		table->info.ntpme = ft_atoi(av[5]);
	init_philos(table);
	return (table);
}
