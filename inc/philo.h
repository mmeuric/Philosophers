/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:18:17 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/06 03:01:52 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define MAX_PHILO 50

typedef struct timeval	t_timeval;

typedef struct s_main
{
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_main;

typedef struct s_times
{
	size_t	eat;
	size_t	sleep;
	size_t	last_meal;
	size_t	first_time;
	size_t	die;
}	t_times;

typedef struct s_philo
{
	t_times		times;
	t_main	mutexes;
	pthread_t		pthread_id;
	int			id;
	int			must_eat;
	int			meals_eaten;
	int			philo_count;
}	t_philo;

typedef struct s_init
{
	pthread_mutex_t	*forks;
	t_philo	*philos;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}	t_init;

/*FT_ATOI.C*/
size_t	ft_strlen(const char *str);
long	ft_atoi(const char *str);
/*INIT.C*/
void	init_philos(t_init *init, t_philo *philo, pthread_mutex_t *forks, char **argv);
void	init_forks(t_init *init, pthread_mutex_t *forks, int count);
void	ft_init(t_init *init, t_philo *philo, pthread_mutex_t *forks);
size_t	get_current_time(void);
/*PHILO.C*/
bool	ft_eat(t_philo *philo);
void	*monitor(void *ptr);
void	routine_philos(t_philo *philo);
void	*start_simulation(void *ptr);
void	philo(t_init *init, int count);
/*UTILS.C*/
void	msg_error(char *text, int digit);
void	ft_clean(t_init *init, char *str, int count, int digit);
void	print_message(t_philo *philo, char *action);
void	ft_usleep(size_t ms);
void	ft_verif(int argc, char **argv);

#endif
