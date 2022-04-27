/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 07:15:00 by mourdani          #+#    #+#             */
/*   Updated: 2022/04/27 07:15:07 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	int	nop;
	int	tdie;
	int	teat;
	int	tsleep;
	int	ntpme;
}				t_info;

typedef struct s_philo
{
	pthread_mutex_t	write;
	pthread_mutex_t	*l_f;
	pthread_mutex_t	*r_f;
	int				pid;
	int				nta;
	int				nta_1;
	time_t			last_eat;

	time_t			limit_of_life;
	int				stop;
	time_t			st;
	t_info	info;
	struct s_sim	*table;
}					t_philo;

typedef struct s_sim
{
	pthread_t		*tids;
	t_philo			*philos;
	int				pid;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
	int				dead;
	time_t			st;
	t_info	info;
}					t_sim;

void	take_forks(t_philo *philo);
void	go_eat(t_philo *philo);
void	go_sleep(t_philo *philo);
void	go_think(t_philo *philo);

long	ft_time(void);
void	ft_usleep(int ms);
int		ft_atoi(const char *str);
int		count_meals(t_philo *philo);

void	init_threads(t_sim *table);
void	join_threads(t_sim *table);
void	*death_checker(void *table);
void	*routine(void *table);

void	init_philos(t_sim *table);
void	ft_init_mutex(t_sim *table);
int		init_table(t_sim *table, int ac, char **av);

void	ft_check_args(void);
void	free_all(t_sim *table);
void	unlock_and_destroy_mutex(t_sim *table);
void	puterr(char *str);
int	ft_is_number(char *n);

#endif
