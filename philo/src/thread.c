/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 07:13:36 by mourdani          #+#    #+#             */
/*   Updated: 2022/05/15 11:29:18 by mourdani         ###   ########.fr       */
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

void	print_died(t_philo *philo, int i)
{
	int	total_nta;

	pthread_mutex_lock(&philo->table->write);
	total_nta = philo->table->info.ntpme * philo->table->info.nop;
	if ((philo->info.nop) != philo->table->total_nta)
		printf("%ld %d died\n", ft_time() - philo->st,
			philo[i].pid + 1);
	i = -1;
	while (i < philo[i].info.nop)
	{
		philo[i].stop = 1;
		i++;
	}
}

int	check_nta(void *philos)
{
	t_philo		*philo;

	philo = (t_philo *)philos;
	if ((philo->info.nop) == philo->table->total_nta)
		return (1);
	return (0);
}

void	*death_checker(void *philos)
{
	t_philo	*philo;
	long	time_now;
	int		i;

	philo = (t_philo *)philos;
	i = 0;
	while (philo[i].stop == 0)
	{
		i = -1;
		while (++i < philo->info.nop)
		{
			pthread_mutex_lock(&philo[i].last_e);
			time_now = ft_time() - philo[i].last_eat;
			if (time_now > philo[i].limit_of_life)
			{
				print_died(philo, i);
				pthread_mutex_unlock(&philo->table->write);
				return (NULL);
			}
			pthread_mutex_unlock(&philo[i].last_e);
		}
	}
	return (NULL);
}
