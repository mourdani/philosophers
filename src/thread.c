/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 07:13:36 by mourdani          #+#    #+#             */
/*   Updated: 2022/04/29 08:44:44 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_threads(t_sim *table)
{
	int			nop;
	pthread_t	*threads;
	pthread_t	s_tid;

	nop = table->info.nop;
	threads = malloc(sizeof(pthread_t) * nop);
	while (nop--)
		pthread_create(&threads[nop], \
			NULL, routine, (void *)&table->philos[nop]);
	pthread_create(&s_tid, NULL, death_checker, (void *)table->philos);
	pthread_join(s_tid, NULL);
	table->tids = threads;
}

void	join_threads(t_sim *table)
{
	int	nop;

	nop = table->info.nop;
	if (nop == 1)
		pthread_mutex_unlock(&table->forks[0]);
	while (nop)
	{
		nop--;
		pthread_join(table->tids[nop], NULL);
	}
}

int	count_meals(t_philo *philo)
{
	int	flag_enough;
	int	i;

	if (philo->nta != -1 && philo->nta_1 > 0)
	{
		flag_enough = 1;
		i = -1;
		while (++i < philo->info.nop)
			if (philo[i].nta < philo->nta_1)
				flag_enough = 0;
		if (flag_enough == 1)
		{
			i = -1;
			while (i < philo[i].info.nop)
			{
				philo[i].stop = 1;
				i++;
			}
			return (1);
		}
	}
	return (0);
}

void	print_died(t_philo *philo, int i)
{
	philo->table->dead = 1;
	pthread_mutex_lock(&philo->write);
	printf("%ld %d died\n", ft_time() - philo->st,
		philo[i].pid + 1);
	i = -1;
	while (i < philo[i].info.nop)
	{
		philo[i].stop = 1;
		i++;
	}
}

void	*death_checker(void *table)
{
	t_philo	*philo;
	long	time_now;
	int		i;

	philo = (t_philo *)table;
	i = 0;
	while (philo[i].stop == 0)
	{
		i = -1;
		while (++i < philo->info.nop)
		{
			time_now = ft_time();
			if (time_now - philo[i].last_eat > philo[i].limit_of_life)
			{
				print_died(philo, i);
				pthread_mutex_unlock(&philo->write);
				return (NULL);
			}
		}
		if (count_meals(philo) || philo->stop)
			return (NULL);
	}
	return (NULL);
}
