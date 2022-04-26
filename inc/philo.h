/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:23:24 by mourdani          #+#    #+#             */
/*   Updated: 2022/04/26 14:23:27 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
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
	pthread_t		ph_thread;
	pthread_t		dcheck_thread;
	pthread_mutex_t	eating;
	int				pid;
	int				nta;
	int				l_f;
	int				r_f;
	int				is_eating;
	long long		last_eat;
	t_info			info;
	struct s_sim	*table;
	int				end;
	int				cdt;
}				t_philo;

typedef struct s_sim
{
	t_philo			*philo;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
	int				alive;
	int				stop;
	long long		st;
	t_info			info;
}				t_sim;

t_sim			*init_table(char **argv, int argc, t_sim *philo);
void			init_threads(t_sim *table);
void			*routine(void *philo);
void			*death_checker(void *philo);

void			print_action(t_philo *phil, int pid, char *str);
int				ft_atoi(const char *str);
void			*ft_memalloc(size_t size);
void			puterr(char *str);
int				ft_is_number(char *str);
long long		time_ms(void);

#endif
