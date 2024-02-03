/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:57:15 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/02/03 12:01:32 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *hack)
{
	int			philo_id;
	t_program	program;

	philo_id = *((int *)(((t_hack *)hack)->philo_id_ptr));
	program = *((t_program *)(((t_hack *)hack)->program_ptr));

	return (NULL);
}

int	main(int argc, char **argv)
{
	int					i;
	t_program			program;
	t_hack				hack;

	i = 0;
	if (argc != 5 || argc != 6 || invalid_args(argc, argv))
		return (print_error());
	parse_args(program, argc, argv);
	while (i < program.philos_num)
		(pthread_mutex_init(&program.forks[i], NULL),
			gettimeofday(&program.last_meal_time[i++], NULL));
	i = 0;
	while (i < program.philos_num)
	{
		program.philos_ids[i] = i;
		hack.program_ptr = &program;
		hack.philo_id_ptr = &program.philos_ids[i];
		pthread_create(&program.philos[i], NULL, philosopher, &hack);
		i++;
	}
	i = 0;
	while (i < program.philos_num)
		pthread_join(program.philos[i++], NULL);
	i = 0;
	while (i < program.philos_num)
		pthread_mutex_destroy(&program.forks[i++]);
	return (0);
}
