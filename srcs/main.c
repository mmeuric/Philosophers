/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeuric <mmeuric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 01:57:44 by mmeuric           #+#    #+#             */
/*   Updated: 2025/02/08 22:45:35 by mmeuric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_init	init;

	ft_verif(argc, argv);
	ft_init(&init, argv);
	close_simulation(&init);
	ft_clean(&init);
	return (0);
}
