/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:30:00 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/02/02 15:35:36 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_args(t_program *program, int argc, char **argv)
{
	program->philos_num = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		program->philos_meals = ft_atoi(argv[5]);
	else
		program->philos_meals = -1;
}
