/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 02:18:16 by mourdani          #+#    #+#             */
/*   Updated: 2022/02/16 07:33:29 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// = PTHREAD_MUTEX_INITIALIZER;

void	*func()
{
	pthread_mutex_lock( &mutex1 );
	printf("philo n: %ld\t", pthread_self());
	printf("is created\n");
	pthread_mutex_unlock( &mutex1 );
	return (NULL);
}

int	init_threads(int n_of_threads)
{
	pthread_t philo[n_of_threads];
	int	i;

	i = 0;
	while (i < n_of_threads)
	{
//		printf("i = % d\t", i);
		if (pthread_create(&philo[i], NULL, &func, NULL) < 0)
			return (0);
		i++;
	}
	while (--i >= 0)
		pthread_join(philo[i], NULL);
	return (1);
}

void	philosophers(int n_of_philos, int time_to_die, int time_to_eat, int time_to_sleep, int must_eat_n_times)
{
	static pthread_mutex_t mutex1;

	if (!init_threads(n_of_philos))
		printf("pthread error\n");
	(void)must_eat_n_times;
	(void)time_to_die;
	(void)time_to_eat;
	(void)time_to_sleep;
}

int	main(int ac, char **av)
{
	if (ac == 5)
		philosophers(ft_atoi(av[1]), ft_atoi(av[2]), ft_atoi(av[3]), ft_atoi(av[4]), 0);
	else if (ac == 6)
		philosophers(ft_atoi(av[1]), ft_atoi(av[2]), ft_atoi(av[3]), ft_atoi(av[4]), ft_atoi(av[5]));
	else
	{
		printf("USAGE: ./philo 	number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return (0);
	}
	printf("working!!\n");
	return (0);
}






// TESTING
//	printf("number of philosophers: %d \n", n_of_philos);
//	printf("time to die : %d \n", time_to_die);
//	printf("time to eat : %d \n", time_to_eat);
//	printf("time to sleep : %d \n", time_to_sleep);
//	printf("must eat n times: %d \n", must_eat_n_times);
