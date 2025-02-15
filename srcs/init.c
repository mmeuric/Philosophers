/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:30:27 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/13 20:45:14 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(t_init *init, int nb)
{
	t_philo	*philo;
	int		init_count;

	philo = malloc(sizeof(t_philo));
	philo->nb = nb + 1;
	philo->nb_eat = 0;
	philo->last_eat = get_current_time();
	philo->init = init;
	init_count = philo->init->nb_philo;
	philo->left_fork = &philo->init->fork[nb];
	if (init_count == 1)
		philo->right_fork = NULL;
	else
		philo->right_fork = &philo->init->fork[(nb + 1) % init_count];
	pthread_mutex_init(&philo->meal_lock, NULL);
	pthread_create(&philo->thread, NULL, monitor, philo);
	return (philo);
}

void	ft_init_thread(t_init *init)
{
	int	i;

	pthread_mutex_init(&init->write_lock, NULL);
	pthread_mutex_init(&init->end, NULL);
	init->philos = malloc(init->nb_philo * sizeof(t_philo));
	init->fork = malloc(init->nb_philo * sizeof(pthread_mutex_t));
	i = -1;
	while (++i < init->nb_philo)
		pthread_mutex_init(&init->fork[i], NULL);
	i = -1;
	while (++i < init->nb_philo)
		init->philos[i] = init_philo(init, i);
}

int	ft_init(t_init *init, int argc, char **argv)
{
	init->nb_philo = ft_atoi(argv[1]);
	init->time_die = ft_atoi(argv[2]);
	init->time_eat = ft_atoi(argv[3]);
	init->time_sleep = ft_atoi(argv[4]);
	init->is_end = 0;
	if (argc == 6)
		init->nb_eat = ft_atoi(argv[5]);
	else
		init->nb_eat = -2;
	ft_init_thread(init);
	return (1);
}
