/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <mourdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:36:31 by mourdani          #+#    #+#             */
/*   Updated: 2022/03/23 22:48:03 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_sim	*init_table(int ac, char **av)
{
	t_sim	*table;

	table = (t_sim *) malloc(sizeof(t_sim));
	if (table == NULL)
		return (NULL);
	table->nop = ft_atoi(av[1]);
	table->tdie = ft_atoi(av[2]);
	table->teat = ft_atoi(av[3]);
	table->tslp = ft_atoi(av[4]);
	table->ntpme = -1;
	table->death = 1;
	if (ac - 1 == 5)
		table->ntpme = ft_atoi(av[5]);
  if (table->nop == OFLOW || table->tdie == OFLOW
  	|| table->teat == OFLOW || table->tslp == OFLOW
  	|| table->ntpme == OFLOW)
  {
  	puterr("ERR: Invalid Argument\n");
  	return (NULL);
  }
	table->forks = init_forks(table);
	if (table->forks == NULL)
		return (NULL);
	table->philos = init_philos(table);
	if (table->philos == NULL || table->nop == 0)
		return (NULL);
	if (pthread_mutex_init(&table->write, 0) != 0)
		return (NULL);
	table->st = time_ms();
	return (table);
}

t_philo	**init_philos(t_sim *table)
{
	t_philo	**philos;
	int		i;

	i = -1;
	philos = (t_philo **)malloc(sizeof(t_philo *) * table->nop + 1);
	if (philos == NULL)
		return (NULL);
	while (++i < table->nop)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (philos[i] == NULL)
			return (NULL);
		if (pthread_mutex_init(&philos[i]->eating, 0) != 0)
			return (NULL);
		philos[i]->table = table;
		philos[i]->pid = i;
		philos[i]->is_eating = 0;
		philos[i]->nta = 0;
		philos[i]->lf = i;
		philos[i]->rf = (i + 1) % philos[i]->table->nop;
	}
	return (philos);
}

pthread_mutex_t	*init_forks(t_sim *table)
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->nop);
	if (forks == NULL)
		return (NULL);
	while (++i < table->nop)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (NULL);
	}
	return (forks);
}
