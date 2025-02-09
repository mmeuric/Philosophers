/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 02:16:28 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/09 00:59:08 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 50

typedef struct timeval	t_timeval;

typedef struct s_times
{
	long				eat;
	int					sleep;
	int					last_meal;
	long				first_time;
	long				last_eat;
	int					die;
}						t_times;

typedef struct s_philo
{
	int					nb_print;
	int					nb_eat;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_lock;
	struct s_init		*init;
	t_times				times;
}						t_philo;

typedef struct s_init
{
	int					philo_count;
	int					must_eat;
	int					is_end;
	int					count_ms;
	t_philo				**philos;
	t_times				times;
	pthread_mutex_t		*fork;
	pthread_mutex_t		end;
	pthread_mutex_t		write_lock;
}						t_init;

/*FT_ATOI.C*/
long					ft_atoi(const char *str);
size_t					ft_strlen(const char *s);
void					putstr_fd(int fd, char *str);
/*INIT.C*/
t_philo					*ft_init_philo(t_init *init, int count);
void					ft_init_thread(t_init *init);
void					ft_init(t_init *init, char **argv);
void					ft_clean(t_init *init);
long					get_current_time(void);
/*UTILS.C*/
void					ft_verif(int argc, char **argv);
void					ft_usleep(long ms);
int						ft_print_state(t_philo *philo, char *str);
void					msg_error(char *text, int digit);
void					ft_clean(t_init *init);
/*PHILO.C*/
void					ft_eat(t_philo *philo);
int						philo_ate(t_init *init);
void					ft_last_msg(t_philo *philo, char *str, t_init *init,
							int count);
void					*close_simulation(t_init *init);
void					*monitor(void *ptr);

#endif