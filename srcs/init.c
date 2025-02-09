/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 02:17:19 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/09 01:04:16 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_init_philo(t_init *init, int count)
{
	t_philo	*philo;
	int		init_count;

	philo = malloc(sizeof(t_philo));
	philo->nb_print = count + 1;
	philo->nb_eat = 0;
	philo->times.first_time = get_current_time();
	philo->times.last_eat = get_current_time();
	philo->init = init;
	init_count = philo->init->philo_count;
	philo->left_fork = &philo->init->fork[count];
	if (init_count == 1)
		philo->right_fork = NULL;
	else
		philo->right_fork = &philo->init->fork[(count + 1) % init_count];
	pthread_mutex_init(&philo->meal_lock, NULL);
	pthread_create(&philo->thread, NULL, monitor, philo);
	return (philo);
}

void	ft_init_thread(t_init *init)
{
	int	i;

	i = 0;
	pthread_mutex_init(&init->write_lock, NULL);
	pthread_mutex_init(&init->end, NULL);
	init->philos = malloc(init->philo_count * sizeof(t_philo *));
	init->fork = malloc(init->philo_count * sizeof(pthread_mutex_t));
	while (i < init->philo_count)
	{
		pthread_mutex_init(&init->fork[i], NULL);
		init->philos[i] = ft_init_philo(init, i);
		i++;
	}
}

void	ft_init(t_init *init, char **argv)
{
	init->philo_count = ft_atoi(argv[1]);
	init->times.die = ft_atoi(argv[2]);
	init->times.eat = ft_atoi(argv[3]);
	init->times.sleep = ft_atoi(argv[4]);
	init->is_end = 0;
	init->count_ms = 50;
	if (argv[5])
		init->must_eat = ft_atoi(argv[5]);
	else
		init->must_eat = -1;
	ft_init_thread(init);
}

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
