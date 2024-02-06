/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:57:15 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/02/06 11:20:11 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(int philo_id, t_program *program)
{
	pthread_mutex_lock(&program->forks[philo_id]);
	if (!program->dead_flag)
		printf("%zu %d has taken a fork\n", get_time()
			- program->start_time, philo_id + 1);
	if (program->philos_num == 1)
	{
		while (!program->dead_flag)
			;
		pthread_mutex_unlock(&program->forks[philo_id]);
		return (-1);
	}
	pthread_mutex_lock(&program->forks[(philo_id + 1)
		% program->philos_num]);
	if (!program->dead_flag)
		printf("%zu %d has taken a fork\n", get_time()
			- program->start_time, philo_id + 1);
	program->last_meal_time[philo_id] = get_time();
	if (!program->dead_flag)
		printf("%zu %d is eating\n", get_time()
			- program->start_time, philo_id + 1);
	msleep(program->time_to_eat);
	pthread_mutex_unlock(&program->forks[(philo_id + 1)
		% program->philos_num]);
	pthread_mutex_unlock(&program->forks[philo_id]);
	return (0);
}

void	sleeping(int philo_id, t_program *program)
{
	if (!program->dead_flag)
		printf("%zu %d is sleeping\n", get_time()
			- program->start_time, philo_id + 1);
	msleep(program->time_to_sleep);
}

void	thinking(int philo_id, t_program *program)
{
	if (!program->dead_flag)
		printf("%zu %d is thinking\n", get_time()
			- program->start_time, philo_id + 1);
}

// the while for handling 
// any interruptions and retry
int	msleep(size_t msec)
{
	size_t	time;

	time = get_time();
	while (get_time() - time < msec)
		usleep(500);
	return (0);
}
