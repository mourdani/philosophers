/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 07:13:20 by mourdani          #+#    #+#             */
/*   Updated: 2022/04/28 20:28:37 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_table(t_sim *table, int ac, char **av)
{
	table->info.nop = ft_atoi(av[1]);
	table->info.tdie = ft_atoi(av[2]);
	table->info.teat = ft_atoi(av[3]);
	table->info.tsleep = ft_atoi(av[4]);
	table->dead = 0;
	table->info.ntpme = -1;
	if (ac == 6)
		table->info.ntpme = ft_atoi(av[5]);
	if (table->info.ntpme == 0)
		return (1);
	else if (table->info.nop == 1)
	{
		usleep(table->info.tdie);
		printf("%ld %d died\n", (long int)table->info.tdie, 1);
		return (1);
	}
	init_philos(table);
	return (0);
}

void	init_philos(t_sim *table)
{
	int				i;
	int				nop;
	t_philo			*philos;
	pthread_mutex_t	*mutex;

	i = 0;
	nop = table->info.nop;
	mutex = malloc(sizeof(pthread_mutex_t) * nop);
	while (nop--)
		pthread_mutex_init(&mutex[nop], NULL);
	pthread_mutex_init(&table->write, NULL);
	table->forks = mutex;
	philos = malloc(sizeof(t_philo) * table->info.nop);
	while (i < table->info.nop)
	{
		philos[i].pid = i;
		philos[i].nta = 0;
		philos[i].nta_1 = table->info.ntpme;
		philos[i].info.nop = table->info.nop;
		philos[i].info.teat = table->info.teat;
		philos[i].info.tsleep = table->info.tsleep;
		philos[i].info.tdie = table->info.tdie;
		philos[i].last_eat = ft_time();
		philos[i].limit_of_life = table->info.tdie;
		philos[i].stop = 0;
		philos[i].l_f = \
			&table->forks[philos[i].pid];
		philos[i].r_f = \
			&table->forks[(philos[i].pid + 1) % table->info.nop];
		philos[i].table = table;
		i++;
	}
	table->philos = philos;
}
