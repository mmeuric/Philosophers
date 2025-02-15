/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:05:32 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/13 20:49:20 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_verif(int argc, char **argv)
{
	int		i;
	long	nb;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		write(2, "❌ Error 📖\n✅ Exec format: ./philo [nb_pilos] ", 52);
		return (putstr_fd(2, "[t_to_die] [t_to_eat] [t_to_sleep]\n"), 1);
	}
	while (++i < argc)
	{
		nb = ft_atoi(argv[i]);
		if (i == 1 && (nb < 1 || nb > 200))
			return (putstr_fd(2, "❌ Error 👴\nNb philos incorrect !\n"), 1);
		else if (i == 2 && (nb < 60 || nb > 2147483647))
			return (putstr_fd(2, "❌ Error 🕚\nTime to die incorrect !\n"), 1);
		else if (i == 3 && (nb < 60 || nb > 2147483647))
			return (putstr_fd(2, "❌ Error 🕚\nTime to eat incorrect !\n"), 1);
		else if (i == 4 && (nb < 60 || nb > 2147483647))
			return (putstr_fd(2, "❌ Error 🕚\nTime to sleep incorrect !\n"), 1);
		else if (i == 5 && (nb < 0 || nb > 2147483647))
			return (putstr_fd(2, "❌ Error 🍝\nNumber of eat incorrect !\n"), 1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_init	init;

	if (ft_verif(argc, argv) == 1)
		return (0);
	if (argc == 6)
		if (ft_atoi(argv[5]) == 0)
			return (write(1, "🎉 All philosophers ate 0 times 🎉\n", 39));
	if (ft_init(&init, argc, argv) == 0)
		return (0);
	close_simulation(&init);
	ft_clean(&init);
	return (0);
}
