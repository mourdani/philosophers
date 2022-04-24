/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <mourdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 01:21:41 by mourdani          #+#    #+#             */
/*   Updated: 2022/04/01 03:30:14 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_philo_threads(t_sim *table)
{
	int	i;

	i = -1;
	while (++i < table->info.nop)
	{
		table->philo[i].last_eat = time_ms();
		if (pthread_create(&table->philo[i].ph_thread, NULL, \
			&routine, (void *)&table->philo[i]) != 0)
			return ;
		usleep(100);
	}
}

void	init_dcheck_threads(t_sim *table)
{
	int	i;

	i = -1;
	while (++i < table->info.nop)
	{
		if (pthread_create(&table->philo[i].dcheck_thread, NULL, \
			&death_checker, (void *)&table->philo[i]) != 0)
			return ;
		usleep(100);
	}
}

void	join_threads(t_sim *table)
{
	int	i;

	i = -1;
	while (++i < table->info.nop)
	{
		pthread_join(table->philo[i].dcheck_thread, NULL);
		pthread_join(table->philo[i].ph_thread, NULL);
	}
}

void	init_threads(t_sim *table)
{
	init_philo_threads(table);
	init_dcheck_threads(table);
	join_threads(table);
	return ;
}
