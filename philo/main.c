/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:57:15 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/02/07 10:24:01 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *hack)
{
	int				philo_id;
	t_program		*program;

	philo_id = *((int *)(((t_hack *)hack)->philo_id_ptr));
	program = ((t_program *)(((t_hack *)hack)->program_ptr));
	while (!program->ready)
		;
	if (philo_id % 2 != 0)
		msleep(1);
	while (!pthread_mutex_lock(&program->dead_flag_mutex) && !program->dead_flag
		&& program->philos_meals != program->philo_meals[philo_id]
		&& !pthread_mutex_unlock(&program->dead_flag_mutex))
	{
		if (eating(philo_id, program) == -1)
			return (NULL);
		program->philo_meals[philo_id]++;
		sleeping(philo_id, program);
		thinking(philo_id, program);
	}
	pthread_mutex_unlock(&program->dead_flag_mutex);
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
		while (i < program->philos_num)
		{
			time = get_time();
			pthread_mutex_lock(&program->last_meal_time_mutex[i]);
			if ((time - program->last_meal_time[i]) > program->time_to_die)
			{
				if (program->philos_meals != program->philo_meals[i])
					my_print("%zu %d died\n", i + 1, program, 1);
				pthread_mutex_lock(&program->dead_flag_mutex);
				program->dead_flag = 1;
				pthread_mutex_unlock(&program->dead_flag_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&program->last_meal_time_mutex[i++]);
		}
	}
	return (NULL);
}

int	init(t_program *program, int argc, char **argv)
{
	int	i;

	i = 0;
	if ((argc != 5 && argc != 6) || invalid_args(argc, argv))
		return (print_error());
	parse_args(program, argc, argv);
	program->start_time = get_time();
	while (i < program->philos_num)
	{
		pthread_mutex_init(&program->dead_flag_mutex, NULL);
		pthread_mutex_init(&program->print_mutex, NULL);
		pthread_mutex_init(&program->last_meal_time_mutex[i], NULL);
		pthread_mutex_init(&program->forks[i], NULL);
		program->last_meal_time[i++] = get_time();
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int					i;
	t_program			program;
	t_hack				hack[MAX_PHILOS];

	if (init(&program, argc, argv) == -1)
		return (1);
	i = 0;
	program.ready = 0;
	while (i < program.philos_num)
	{
		program.philos_ids[i] = i;
		hack[i].program_ptr = &program;
		hack[i].philo_id_ptr = &program.philos_ids[i];
		pthread_create(&program.philos[i], NULL, philosopher, &hack[i]);
		i++;
	}
	program.ready = 1;
	pthread_create(&program.waiter, NULL, waiter, &program);
	i = 0;
	while (i < program.philos_num)
		pthread_detach(program.philos[i++]);
	pthread_join(program.waiter, NULL);
	clean(&program);
	return (0);
}
