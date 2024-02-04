/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:57:15 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/02/04 09:13:32 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *hack)
{
	int				philo_id;
	struct timeval	current_time;
	long			time_since_last_meal;
	t_program		*program;

	philo_id = *((int *)(((t_hack *)hack)->philo_id_ptr));
	program = ((t_program *)(((t_hack *)hack)->program_ptr));
	while (!program->dead_flag)
	{
		gettimeofday(&current_time, NULL);
		time_since_last_meal = (current_time.tv_sec * 1000
				+ current_time.tv_usec / 1000)
			- (program->last_meal_time[philo_id].tv_sec * 1000
				+ program->last_meal_time[philo_id].tv_usec / 1000);
		if (time_since_last_meal > program->time_to_die)
		{
			printf("%d died\n", philo_id + 1);
			program->dead_flag = 1;
			break ;
		}
		pthread_mutex_lock(&program->forks[philo_id]);
		printf("%d has taken a fork\n", philo_id + 1);
		pthread_mutex_lock(&program->forks[(philo_id + 1)
			% program->philos_num]);
		printf("%d has taken a fork\n", philo_id + 1);
		printf("%d is eating\n", philo_id + 1);
		gettimeofday(&program->last_meal_time[philo_id], NULL);
		msleep(program->time_to_eat);
		pthread_mutex_unlock(&program->forks[philo_id]);
		pthread_mutex_unlock(&program->forks[(philo_id + 1)
			% program->philos_num]);
		printf("%d is sleeping\n", philo_id + 1);
		msleep(program->time_to_sleep);
		printf("%d is thinking\n", philo_id + 1);
	}
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
