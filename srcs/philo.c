/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 00:45:01 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/06 03:10:21 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_eat(t_philo *philos)
{
	int		count_ate;
	int		i;

	i = -1;
	count_ate = 0;
	if (philos[0].must_eat == -1)
		return (false);
	while (++i < philos[0].philo_count)
	{
		pthread_mutex_lock(philos->mutexes.meal_lock);
		if (philos[i].meals_eaten >= philos[i].must_eat)
			count_ate++;
		pthread_mutex_unlock(philos->mutexes.meal_lock);
	}
	if (count_ate == philos[0].philo_count)
	{
		pthread_mutex_lock(philos->mutexes.write_lock);
		printf("All philosophers ate %d times\n", philos->must_eat);
		return (true);
	}
	return (false);
}

void	*monitor(void *ptr)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)ptr;
	while (true)
	{
		i = -1;
		while (++i < philos[0].philo_count)
		{
			pthread_mutex_lock(philos->mutexes.meal_lock);
			if (get_current_time() - philos[i].times.last_meal
				> philos[i].times.die)
			{
				pthread_mutex_unlock(philos->mutexes.meal_lock);
				print_message(&philos[i],"died");
				return (NULL);
			}
			pthread_mutex_unlock(philos->mutexes.meal_lock);
		}
		if (ft_eat(philos))
			return (NULL);
	}
	return (NULL);
}

void	routine_philos(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexes.l_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->mutexes.r_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->mutexes.meal_lock);
	print_message(philo, "is eating");
	philo->times.last_meal = get_current_time();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(philo->mutexes.meal_lock);
	ft_usleep(philo->times.eat);
	pthread_mutex_unlock(philo->mutexes.l_fork);
	pthread_mutex_unlock(philo->mutexes.r_fork);
	print_message(philo, "is sleeping");
	ft_usleep(philo->times.sleep);
	print_message(philo, "is thinking");
}

void	*start_simulation(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	pthread_mutex_lock(philo->mutexes.meal_lock);
	philo->times.first_time = get_current_time();
	philo->times.last_meal = get_current_time();
	pthread_mutex_unlock(philo->mutexes.meal_lock);
	while (true)
		routine_philos(philo);
	return (NULL);
}

void	philo(t_init *init, int count)
{
	pthread_t	monitor_id;
	int		i;

	i = -1;
	if (pthread_create(&monitor_id, NULL, &monitor, init->philos) != 0)
		ft_clean(init, "Error creation thread\n", count, 1);
	while (++i < count)
	{
		if (pthread_create(&init->philos[i].pthread_id, NULL,
				start_simulation, &init->philos[i]) != 0)
			ft_clean(init, "Error creation thread\n", count, 1);
	}
	i = -1;
	if (pthread_join(monitor_id, NULL) != 0)
		ft_clean(init, "Error join thread\n", count, 1);
	while (++i < count)
	{
		if (pthread_detach(init->philos[i].pthread_id) != 0)
			ft_clean(init, "Error detach thread\n", count, 1);
	}
}
