/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:30:56 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/13 20:45:33 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	sleep_ms(long duration)
{
	long	start;

	start = get_current_time();
	while (get_current_time() < start + duration)
		usleep(500);
}

int	ft_last_msg(t_philo *philo, char *msg)
{
	int		stop;
	long	time;

	time = get_current_time();
	pthread_mutex_lock(&philo->init->end);
	stop = philo->init->is_end;
	if (stop)
		return (pthread_mutex_unlock(&philo->init->end), 1);
	pthread_mutex_unlock(&philo->init->end);
	pthread_mutex_lock(&philo->init->write_lock);
	printf("[%ldms] %d %s\n", time, philo->nb, msg);
	pthread_mutex_unlock(&philo->init->write_lock);
	return (1);
}

void	ft_clean(t_init *init)
{
	int	i;

	i = 0;
	while (i < init->nb_philo)
	{
		pthread_join(init->philos[i]->thread, NULL);
		pthread_mutex_lock(&init->philos[i]->meal_lock);
		pthread_mutex_unlock(&init->philos[i]->meal_lock);
		pthread_mutex_destroy(&init->philos[i]->meal_lock);
		pthread_mutex_lock(&init->fork[i]);
		pthread_mutex_unlock(&init->fork[i]);
		pthread_mutex_destroy(&init->fork[i]);
		free(init->philos[i]);
		i++;
	}
	free(init->fork);
	free(init->philos);
	pthread_mutex_destroy(&init->end);
	pthread_mutex_destroy(&init->write_lock);
}
