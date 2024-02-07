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
	my_print("%zu %d has taken a fork\n", philo_id + 1, program, 0);
	if (program->philos_num == 1)
	{
		while (!pthread_mutex_lock(&program->dead_flag_mutex)
			&& !program->dead_flag
			&& !pthread_mutex_unlock(&program->dead_flag_mutex))
			;
		pthread_mutex_unlock(&program->dead_flag_mutex);
		pthread_mutex_unlock(&program->forks[philo_id]);
		return (-1);
	}
	pthread_mutex_lock(&program->forks[(philo_id + 1)
		% program->philos_num]);
	my_print("%zu %d has taken a fork\n", philo_id + 1, program, 0);
	pthread_mutex_lock(&program->last_meal_time_mutex[philo_id]);
	program->last_meal_time[philo_id] = get_time();
	program->philo_meals[philo_id]++;
	pthread_mutex_unlock(&program->last_meal_time_mutex[philo_id]);
	my_print("%zu %d is eating\n", philo_id + 1, program, 0);
	msleep(program->time_to_eat);
	pthread_mutex_unlock(&program->forks[(philo_id + 1)
		% program->philos_num]);
	pthread_mutex_unlock(&program->forks[philo_id]);
	return (0);
}

void	sleeping(int philo_id, t_program *program)
{
	my_print("%zu %d is sleeping\n", philo_id + 1, program, 0);
	msleep(program->time_to_sleep);
}

void	thinking(int philo_id, t_program *program)
{
	my_print("%zu %d is thinking\n", philo_id + 1, program, 0);
}

void	my_print(const char *str, int philo_id,
		t_program *program, int close)
{
	if (!pthread_mutex_lock(&program->dead_flag_mutex)
		&& program->dead_flag
		&& !pthread_mutex_unlock(&program->dead_flag_mutex))
		return ;
	pthread_mutex_unlock(&program->dead_flag_mutex);
	pthread_mutex_lock(&program->print_mutex);
	printf(str, get_time()
		- program->start_time, philo_id + 1);
	if (!close)
		pthread_mutex_unlock(&program->print_mutex);
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
