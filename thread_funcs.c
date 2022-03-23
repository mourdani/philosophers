/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <mourdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:21:59 by mourdani          #+#    #+#             */
/*   Updated: 2022/03/23 22:50:03 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int start_philo_threads(t_sim *table)
{
	int	i;

	i = -1;
	while (++i < table->nop)
	{
		table->philos[i]->last_eat = time_ms();
		if (pthread_create(&table->philos[i]->thread_philo, NULL,
			&routine, (void *)table->philos[i]) != 0)
			return (1);
		usleep(100);
	}
	return (0);
}

int start_dcheck_threads(t_sim *table)
{
	int	i;

	i = -1;
	while (++i < table->nop)
	{
		if (pthread_create(&table->philos[i]->check_death, NULL, &is_death,
		(void *)table->philos[i]) != 0)
			return (1);
		usleep(100);
	}
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (philo->table->death)
	{
		go_eat(philo);
		go_sleep(philo);
		go_think(philo);
		usleep(100);
	}
	return (NULL);
}

void	*is_death(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (philo->table->death)
	{
		if (!philo->is_eating
			&& time_ms() - philo->last_eat >= philo->table->tdie)
		{
			pthread_mutex_lock(&philo->eating);
			print_action(philo->table, philo->pid, "died\n");
			philo->table->death = 0;
			pthread_mutex_unlock(&philo->eating);
		}
		if (philo->table->philos[philo->table->nop - 1]->nta
			== philo->table->ntpme)
			philo->table->death = 0;
		usleep(100);
	}
	return (NULL);
}
