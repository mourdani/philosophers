/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <mourdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:22:12 by mourdani          #+#    #+#             */
/*   Updated: 2022/03/24 22:46:47 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)b)[i] = c;
		i++;
	}
	return (b);
}

void	*ft_memalloc(size_t size)
{
	void	*s;

	s = malloc(size);
	if (s == NULL)
		return (NULL);
	ft_memset(s, 0, size);
	return (s);
}

long long	time_ms(void)
{
	struct timeval	te;
	long long		ms;

	gettimeofday(&te, NULL);
	ms = (te.tv_sec * 1000) + (te.tv_usec / 1000);
	return (ms);
}

void	print_action(t_philo *philo, int pid, char *str)
{
	pthread_mutex_lock(&philo->table->write);
	if (philo->table->alive == 0)
	{
		pthread_mutex_unlock(&philo->table->write);
		return ;
	}
	printf("%lld %d %s", time_ms() - philo->table->st, \
			pid, str);
	if (str[0] != 'd')
	{
		pthread_mutex_unlock(&philo->table->write);
	}
	else
	{
		philo->table->alive = 0;
		pthread_mutex_unlock(&philo->table->write);
	}
}
