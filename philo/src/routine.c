/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 07:13:30 by mourdani          #+#    #+#             */
/*   Updated: 2022/05/15 11:30:59 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_forks(t_philo *philo)
{
	if ((philo->pid) % 2 == 0 && philo->pid + 1 != philo->info.nop)
	{
		pthread_mutex_lock(philo->r_f);
		pthread_mutex_lock(philo->l_f);
	}
	else
	{
		pthread_mutex_lock(philo->l_f);
		pthread_mutex_lock(philo->r_f);
	}
	pthread_mutex_lock(&philo->table->write);
	if (philo->stop != 1)
	{
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->st, philo->pid + 1);
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->st, philo->pid + 1);
	}
	pthread_mutex_unlock(&philo->table->write);
}

void	go_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write);
	printf("%ld %d is eating\n", \
		ft_time() - philo->st, philo->pid + 1);
	pthread_mutex_unlock(&philo->table->write);
	philo->nta++;
	if (philo->nta == philo->table->info.ntpme)
	{
		philo->table->total_nta++;
	}
	pthread_mutex_lock(&philo->last_e);
	philo->last_eat = ft_time();
	pthread_mutex_unlock(&philo->last_e);
	ft_usleep(philo->info.teat);
	pthread_mutex_unlock(philo->l_f);
	pthread_mutex_unlock(philo->r_f);
}

void	go_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write);
	printf("%ld %d is sleeping\n", \
		ft_time() - philo->st, philo->pid + 1);
	pthread_mutex_unlock(&philo->table->write);
	ft_usleep(philo->info.tsleep);
}

void	go_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write);
	printf("%ld %d is thinking\n", \
		ft_time() - philo->st, philo->pid + 1);
	pthread_mutex_unlock(&philo->table->write);
}

void	*routine(void *philos)
{
	t_philo		*philo;

	philo = (t_philo *)philos;
	pthread_mutex_lock(&philo->last_e);
	philo->last_eat = ft_time();
	pthread_mutex_unlock(&philo->last_e);
	philo->st = ft_time();
	while (1)
	{
		if (philo->stop || check_nta(philos))
			return (NULL);
		take_forks(philo);
		if (philo->stop || check_nta(philos))
			return (NULL);
		go_eat(philo);
		if (philo->stop || check_nta(philos))
			return (NULL);
		go_sleep(philo);
		if (philo->stop || check_nta(philos))
			return (NULL);
		go_think(philo);
		if (philo->stop || check_nta(philos))
			return (NULL);
	}
	return (NULL);
}
