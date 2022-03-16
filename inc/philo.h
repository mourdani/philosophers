/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 08:16:06 by mourdani          #+#    #+#             */
/*   Updated: 2022/03/16 03:08:06 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h> 

#define _UNIX03_THREADS
# define ERROR			-1
# define OK			1
# define EOL			'\0'

# include <pthread.h>
int pthread_create(pthread_t * __restrict__thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine) (void *arg),
                   void * __restrict__arg);

int	ft_atoi(const char *number_pointer);
int	ft_is_number(char *string);
int	puterr(char *str);


/* np = number of philosophers
 * ttd = time to die
 * tte = time to eat
 * tts = time to sleep
 * ntpe = number of time philospher eats
 * st = starting time
*/
typedef struct s_table{
	pthread_mutex_t *forks;
	t_philo **philos;
	int	np;
	int	ttd;
	int	tte;
	int	tts;
	int	ntpe;
	long long	st;
}	t_table;


/* id = philosopher id
 * nta = number of times to eat
 * lf / rf = lifet / right fortk
 * lta = last time ate
*/
typedef struct s_philo{
	int	id;
	int	nta;
	int	lf;
	int	rf;
	long long	lta;
		
}	t_philo;
# endif
