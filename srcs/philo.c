/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 02:18:01 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/09 00:58:55 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	if (philo->nb_print % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_state(philo, "has taken a fork    🔱");
		pthread_mutex_lock(philo->right_fork);
		ft_print_state(philo, "has taken a fork    🔱");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_print_state(philo, "has taken a fork    🔱");
		pthread_mutex_lock(philo->left_fork);
		ft_print_state(philo, "has taken a fork    🔱");
	}
	pthread_mutex_lock(&philo->meal_lock);
	philo->times.last_eat = get_current_time();
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_print_state(philo, "is eating           🍝");
	ft_usleep(philo->init->times.eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	ft_last_msg(t_philo *philo, char *str, t_init *init, int count)
{
	long	time;
	t_philo	*philo2;

	philo2 = init->philos[0];
	time = get_current_time() - philo2->times.first_time;
	pthread_mutex_lock(&init->write_lock);
	if (philo)
		printf("[%ldms] %d %s\n", time, philo->nb_print, str);
	else
		printf("%s %d times 🎉\n", str, count);
	pthread_mutex_unlock(&init->write_lock);
}

int	philo_ate(t_init *init)
{
	int	i;
	int	end;

	pthread_mutex_lock(&init->end);
	end = init->is_end;
	pthread_mutex_unlock(&init->end);
	if (end)
		return (0);
	i = -1;
	if (init->must_eat == -1)
		return (1);
	while (++i < init->philo_count)
	{
		pthread_mutex_lock(&init->philos[i]->meal_lock);
		if (init->philos[i]->nb_eat < init->must_eat)
			return (pthread_mutex_unlock(&init->philos[i]->meal_lock), 1);
		pthread_mutex_unlock(&init->philos[i]->meal_lock);
	}
	pthread_mutex_lock(&init->end);
	init->is_end = 1;
	pthread_mutex_unlock(&init->end);
	ft_last_msg(NULL, "\n🎉 All philosophers ate", init, init->must_eat);
	return (0);
}

void	*close_simulation(t_init *init)
{
	int	i;

	init->times.die += init->count_ms;
	while (philo_ate(init))
	{
		i = -1;
		while (++i < init->philo_count)
		{
			pthread_mutex_lock(&init->philos[i]->meal_lock);
			if (get_current_time()
				- init->philos[i]->times.last_eat > init->times.die)
			{
				pthread_mutex_lock(&init->end);
				init->is_end = 1;
				pthread_mutex_unlock(&init->end);
				ft_last_msg(init->philos[i], "died 💀", init, 0);
				pthread_mutex_unlock(&init->philos[i]->meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&init->philos[i]->meal_lock);
		}
		usleep(500);
	}
	return (NULL);
}

void	*monitor(void *ptr)
{
	int		flag;
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->init->philo_count == 1)
		return (ft_print_state(philo, "has taken a fork    🔱"), NULL);
	flag = 0;
	while (flag == 0)
	{
		ft_eat(philo);
		ft_print_state(philo, "is sleeping         😴");
		ft_usleep(philo->init->times.sleep);
		ft_print_state(philo, "is thinking         🤔");
		pthread_mutex_lock(&philo->init->end);
		flag = philo->init->is_end;
		pthread_mutex_unlock(&philo->init->end);
	}
	return (NULL);
}
