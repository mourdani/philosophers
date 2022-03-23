/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <mourdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:46:42 by mourdani          #+#    #+#             */
/*   Updated: 2022/03/23 22:47:15 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_sim *table, int pid, char *str)
{
	pthread_mutex_lock(&table->write);
	printf("%lld %d %s", time_ms() - table->st, pid + 1, str);
	if (str[0] != 'd')
		pthread_mutex_unlock(&table->write);
}

void	go_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->lf]);
	pthread_mutex_lock(&philo->table->forks[philo->rf]);
	pthread_mutex_lock(&philo->eating);
	print_action(philo->table, philo->pid, "taken left fork\n");
	print_action(philo->table, philo->pid, "taken right fork\n");
	print_action(philo->table, philo->pid, "is eating\n");
	philo->last_eat = time_ms();
	philo->is_eating = 1;
	usleep(philo->table->teat * 1000);
	while (time_ms() - philo->last_eat < philo->table->teat)
		continue ;
	philo->nta++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(&philo->table->forks[philo->lf]);
	pthread_mutex_unlock(&philo->table->forks[philo->rf]);
	return ;
}

void	go_sleep(t_philo *philo)
{
	long long	time;

	print_action(philo->table, philo->pid, "is sleeping\n");
	time = time_ms();
	usleep(philo->table->tslp * 1000);
	while (time_ms() - time < philo->table->tslp)
		continue ;
	return ;
}

void	go_think(t_philo *philo)
{
	print_action(philo->table, philo->pid, "is thinking\n");
	return ;
}
