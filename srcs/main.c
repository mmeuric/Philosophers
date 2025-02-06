/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 00:44:49 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/06 03:02:38 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo philos[MAX_PHILO];
	pthread_mutex_t forks[MAX_PHILO];
	t_init init;

	ft_verif(argc, argv);
	ft_init(&init, philos, forks);
	init_forks(&init, forks, ft_atoi(argv[1]));
	init_philos(&init, philos, forks, argv);
	philo(&init, philos[0].philo_count);
	ft_clean(&init, NULL, philos[0].philo_count, 0);
	return (0);
}