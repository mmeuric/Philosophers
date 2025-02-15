/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:30:41 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/13 20:44:26 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				nb;
	long			last_eat;
	int				nb_eat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	struct s_init	*init;
}	t_philo;

typedef struct s_init
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				is_end;
	t_philo			**philos;
	pthread_mutex_t	*fork;
	pthread_mutex_t	end;
	pthread_mutex_t	write_lock;
}	t_init;

/*FT_ATOI.C*/
long					ft_atoi(const char *str);
void					putstr_fd(int fd, char *str);
/*INIT.C*/
t_philo					*init_philo(t_init *init, int nb);
void					ft_init_thread(t_init *init);
int						ft_init(t_init *init, int argc, char **argv);
/*UTILS.C*/
int						ft_last_msg(t_philo *philo, char *msg);
void					ft_clean(t_init *init);
long					get_current_time(void);
void					sleep_ms(long duration);
/*PHILO.C*/
void					print_end(t_philo *philo, char *msg, t_init *init);
void					ft_eat(t_philo *philo);
int						philo_ate(t_init *init);
void					*close_simulation(t_init *init);
void					*monitor(void *ptr);
/*MAIN.C*/
int						ft_verif(int argc, char **argv);

#endif