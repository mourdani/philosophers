/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 07:13:13 by mourdani          #+#    #+#             */
/*   Updated: 2022/05/15 11:03:13 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_all(t_sim *table)
{
	free(table->tids);
	free(table->philos);
	free(table->forks);
}

void	unlock_and_destroy_mutex(t_sim *table)
{
	int	nop;

	nop = table->info.nop;
	while (nop-- - 1)
	{
		pthread_mutex_unlock(&table->forks[nop]);
		pthread_mutex_destroy(&table->forks[nop]);
	}
	pthread_mutex_unlock(&(*table).write);
	pthread_mutex_destroy(&(*table).write);
}
