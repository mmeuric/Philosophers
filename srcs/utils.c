/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 00:45:20 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/06 03:40:27 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msg_error(char *text, int digit)
{
	if (text)
		write(2, text, ft_strlen(text) + 1);
	exit(digit);
}

void	print_message(t_philo *philo, char *action)
{
	size_t	time;

	pthread_mutex_lock(philo->mutexes.write_lock);
	time = get_current_time() - philo->times.first_time;
	printf("%ld %d %s\n", time, philo->id, action);
	pthread_mutex_unlock(philo->mutexes.write_lock);
}

void	ft_verif(int argc, char **argv)
{
	int		i;
	long	nb;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		write(2, "❌ Error 📖\n✅ Exec format: ./philo [nb_pilos] ", 52);
		msg_error("[time_to_die] [time_to_eat] [time_to_sleep]\n", 1);
	}
	while (++i < argc)
	{
		nb = ft_atoi(argv[i]);
		if (i == 1 && (nb < 1 || nb > MAX_PHILO))
			msg_error("❌ Error 👴\nNumber of philos incorrect !\n", 1);
		else if (i == 2 && (nb < 1 || nb > INT_MAX))
			msg_error("❌ Error 🕚\nTime to die incorrect !\n", 1);
		else if (i == 3 && (nb < 0 || nb > INT_MAX))
			msg_error("❌ Error 🕚\nTime to eat incorrect !\n", 1);
		else if (i == 4 && (nb < 0 || nb > INT_MAX))
			msg_error("❌ Error 🕚\nTime to sleep incorrect !\n", 1);
		else if (i == 5 && (nb < 0 || nb > INT_MAX))
			msg_error("❌ Error 🍝\nNumber of eat incorrect !\n", 1);
	}
}

void	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < ms)
		usleep(1000);
}

void	ft_clean(t_init *init, char *str, int count, int digit)
{
	count--;
	while (count >= 0)
	{
		pthread_mutex_destroy(&init->forks[count]);
		count--;
	}
	pthread_mutex_destroy(&init->write_lock);
	pthread_mutex_destroy(&init->meal_lock);
	msg_error(str, digit);
}