#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdbool.h>

# define OFLOW		-2

typedef struct s_philo
{
	pthread_mutex_t	eating;
	pthread_t		thread_philo;
	pthread_t		check_death;
	int				pid;
	int				nta;
	int				lf;
	int				rf;
	int				is_eating;
	long long		last_eat;
	struct s_sim	*table;
}				t_philo;

typedef struct s_sim
{
	t_philo			**philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	long long		st;
	int				death;
	int				nop;
	int				tdie;
	int				teat;
	int				tslp;
	int				ntpme;
}	t_sim;


t_sim	*init_table(int ac, char **av);
t_philo	**init_philos(t_sim *table);
pthread_mutex_t							*init_forks(t_sim *table);

void	print_action(t_sim *table, int pid, char *str);
void	go_eat(t_philo *philo);
void	go_sleep(t_philo *philo);
void	go_think(t_philo *philo);

void	puterr(char *str);
int		ft_is_number(char *str);
int		ft_atoi(const char *str);
long long			time_ms(void);

int start_philo_threads(t_sim *table);
int start_dcheck_threads(t_sim *table);
void	*is_death(void *ptr);
void	*routine(void *ptr);


#endif
