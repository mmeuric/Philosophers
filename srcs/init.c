/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 00:44:39 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/06 02:51:30 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_init *init, t_philo *philos, pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].times.die = ft_atoi(argv[2]);
		philos[i].times.eat = ft_atoi(argv[3]);
		philos[i].times.sleep = ft_atoi(argv[4]);
		philos[i].times.last_meal = get_current_time();
		philos[i].times.first_time = get_current_time();
		philos[i].must_eat = -1;
		if (argv[5])
			philos[i].must_eat = ft_atoi(argv[5]);
		philos[i].meals_eaten = 0;
		philos[i].philo_count = ft_atoi(argv[1]);
		philos[i].mutexes.l_fork = &forks[i];
		if (i == 0)
			philos[i].mutexes.r_fork = &forks[philos[i].philo_count - 1];
		else
			philos[i].mutexes.r_fork = &forks[i - 1];
		philos[i].mutexes.write_lock = &init->write_lock;
		philos[i].mutexes.meal_lock = &init->meal_lock;
	}
}

size_t	get_current_time(void)
{
	t_timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		msg_error("gettimeofday error\n", 1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	init_forks(t_init *init, pthread_mutex_t *forks, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			ft_clean(init, "Error Mutex Init\n", i, 1);
	}
}

void	ft_init(t_init *init, t_philo *philos, pthread_mutex_t *forks)
{
	init->forks = forks;
	init->philos = philos;
	if (pthread_mutex_init(&init->write_lock, NULL) != 0
		|| pthread_mutex_init(&init->meal_lock, NULL) != 0)
		ft_clean(init, "Error Mutex Init\n", -1, 1);
}
