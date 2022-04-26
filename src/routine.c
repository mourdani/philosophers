/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <mourdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 22:46:42 by mourdani          #+#    #+#             */
/*   Updated: 2022/04/26 14:44:20 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	go_eat(t_philo *philo)
{
	if (philo->info.nop == 1)
		return (0);
	pthread_mutex_lock(&philo->table->forks[philo->r_f]);
	print_action(philo, philo->pid, "Has taken a right fork\n");
	pthread_mutex_lock(&philo->table->forks[philo->l_f]);
	print_action(philo, philo->pid, "Has taken a left fork\n");
	pthread_mutex_lock(&philo->eating);
	print_action(philo, philo->pid, "is eating\n");
	philo->last_eat = time_ms();
	philo->is_eating = 1;
	usleep(philo->info.teat * 1000 - 16000);
	while (time_ms() - philo->last_eat < philo->info.teat)
		continue ;
	philo->nta++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(&philo->table->forks[philo->r_f]);
	pthread_mutex_unlock(&philo->table->forks[philo->l_f]);
	return (0);
}

int	go_sleep(t_philo *philo)
{
	long long	time;

	if (philo->info.nop == 1)
		return (0);
	print_action(philo, philo->pid, "is sleeping\n");
	time = time_ms();
	usleep(philo->info.tsleep * 1000 - 16000);
	while (time_ms() - time < philo->info.tsleep)
		continue ;
	return (0);
}

int	go_think(t_philo *philo)
{
	if (philo->info.nop == 1)
		return (0);
	print_action(philo, philo->pid, "is thinking\n");
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*r_philo;

	r_philo = (t_philo *)philo;
	while (r_philo->table->alive)
	{
		if (r_philo->end == 0)
			r_philo->table->alive = 0;
		go_eat(r_philo);
		go_sleep(r_philo);
		go_think(r_philo);
		usleep(100);
		if (r_philo->end == 0)
			r_philo->table->alive = 0;
	}
	return (NULL);
}

void	*death_checker(void *r_philo)
{
	t_philo	*philo;

	philo = (t_philo *)r_philo;
	while (philo->table->alive)
	{
		if (!philo->is_eating
			&& time_ms() - philo->last_eat >= philo->info.tdie)
		{
			pthread_mutex_lock(&philo->eating);
			print_action(philo, philo->pid, "died\n");
			philo->table->alive = 0;
			pthread_mutex_unlock(&philo->eating);
		}
		if ((philo->nta == philo->info.ntpme) && (philo->cdt == 1))
		{
			philo->cdt = 0;
			philo->table->stop++;
		}
		if (philo->table->stop == philo->info.nop)
			philo->table->alive = 0;
		usleep(100);
	}
	philo->end = 0;
	pthread_mutex_unlock(&philo->table->write);
	return (NULL);
}
