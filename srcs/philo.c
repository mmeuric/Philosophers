/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:31:22 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/13 20:42:27 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_end(t_philo *philo, char *msg, t_init *init)
{
	long	time;

	time = get_current_time();
	pthread_mutex_lock(&init->write_lock);
	if (philo)
		printf("[%ldms] %d %s\n", time, philo->nb, msg);
	else
		printf("%s\n", msg);
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
	if (init->nb_eat == -2)
		return (1);
	while (++i < init->nb_philo)
	{
		pthread_mutex_lock(&init->philos[i]->meal_lock);
		if (init->philos[i]->nb_eat < init->nb_eat)
			return (pthread_mutex_unlock(&init->philos[i]->meal_lock), 1);
		pthread_mutex_unlock(&init->philos[i]->meal_lock);
	}
	pthread_mutex_lock(&init->end);
	init->is_end = 1;
	pthread_mutex_unlock(&init->end);
	print_end(NULL, "\n🎉 All philosophers ate 🎉", init);
	return (0);
}

void	*close_simulation(t_init *init)
{
	int	i;

	while (philo_ate(init))
	{
		i = -1;
		while (++i < init->nb_philo)
		{
			pthread_mutex_lock(&init->philos[i]->meal_lock);
			if (get_current_time() - init->philos[i]->last_eat > init->time_die)
			{
				pthread_mutex_lock(&init->end);
				init->is_end = 1;
				pthread_mutex_unlock(&init->end);
				print_end(init->philos[i], "died 💀", init);
				pthread_mutex_unlock(&init->philos[i]->meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&init->philos[i]->meal_lock);
		}
		usleep(1000);
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	if (philo->nb % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_last_msg(philo, "has taken a fork    🔱");
		pthread_mutex_lock(philo->right_fork);
		ft_last_msg(philo, "has taken a fork    🔱");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_last_msg(philo, "has taken a fork    🔱");
		pthread_mutex_lock(philo->left_fork);
		ft_last_msg(philo, "has taken a fork    🔱");
	}
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_eat = get_current_time();
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_last_msg(philo, "is eating           🍝");
	sleep_ms(philo->init->time_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	int		status;

	philo = (t_philo *)arg;
	status = 0;
	if (philo->init->nb_philo == 1)
		return (ft_last_msg(philo, "has taken a fork    🔱"), NULL);
	while (status == 0)
	{
		ft_eat(philo);
		ft_last_msg(philo, "is sleeping         😴");
		sleep_ms(philo->init->time_sleep);
		ft_last_msg(philo, "is thinking         🤔");
		pthread_mutex_lock(&philo->init->end);
		status = philo->init->is_end;
		pthread_mutex_unlock(&philo->init->end);
	}
	return (NULL);
}
