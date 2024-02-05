/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:57:15 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/02/05 11:38:12 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *hack)
{
	int				philo_id;
	t_program		*program;

	philo_id = *((int *)(((t_hack *)hack)->philo_id_ptr));
	program = ((t_program *)(((t_hack *)hack)->program_ptr));
	while (!program->dead_flag)
	{
		pthread_mutex_lock(&program->forks[philo_id]);
		printf("%zu %d has taken a fork\n", get_time() - program->start_time, philo_id + 1);
		if (program->philos_num == 1)
		{
			while (!program->dead_flag)
				;
			return (NULL);
		}
		pthread_mutex_lock(&program->forks[(philo_id + 1)
			% program->philos_num]);
		printf("%zu %d has taken a fork\n", get_time() - program->start_time, philo_id + 1);
		program->last_meal_time[philo_id] = get_time();
		printf("%zu %d is eating\n", get_time() - program->start_time, philo_id + 1);
		msleep(program->time_to_eat);
		pthread_mutex_unlock(&program->forks[(philo_id + 1)
			% program->philos_num]);
		pthread_mutex_unlock(&program->forks[philo_id]);
		printf("%zu %d is sleeping\n", get_time() - program->start_time, philo_id + 1);
		msleep(program->time_to_sleep);
		printf("%zu %d is thinking\n", get_time() - program->start_time, philo_id + 1);
	}
	return (NULL);
}

void	*waiter(void *program_ptr)
{
	int				i;
	size_t			time;
	t_program		*program;

	program = (t_program *)program_ptr;
	while (1)
	{
		i = 0;
		time = get_time();
		while (i < program->philos_num)
		{
			if ((time - program->last_meal_time[i]) > program->time_to_die)
			{
				printf("%zu %d died\n", time - program->start_time - 1, i + 1);
				program->dead_flag = 1;
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int					i;
	t_program			program;
	t_hack				hack;

	i = 0;
	if ((argc != 5 && argc != 6) || invalid_args(argc, argv))
		return (print_error());
	parse_args(&program, argc, argv);
	program.start_time = get_time();
	while (i < program.philos_num)
	{
		pthread_mutex_init(&program.forks[i], NULL);
		program.last_meal_time[i++] = get_time();
	}
	i = 0;
	while (i < program.philos_num)
	{
		program.philos_ids[i] = i;
		hack.program_ptr = &program;
		hack.philo_id_ptr = &program.philos_ids[i];
		pthread_create(&program.philos[i], NULL, philosopher, &hack);
		i++;
	}
	pthread_create(&program.waiter, NULL, waiter, &program);
	i = 0;
	while (i < program.philos_num)
		pthread_join(program.philos[i++], NULL);
	i = 0;
	while (i < program.philos_num)
		pthread_mutex_destroy(&program.forks[i++]);
	return (0);
}
