/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 08:16:06 by mourdani          #+#    #+#             */
/*   Updated: 2022/02/16 04:56:11 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h> 

#define _UNIX03_THREADS
# include <pthread.h>
int pthread_create(pthread_t * __restrict__thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine) (void *arg),
                   void * __restrict__arg);

int	ft_atoi(const char *number_pointer);

# endif
