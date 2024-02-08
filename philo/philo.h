/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:58:12 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/02/08 16:21:52 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>

#define MAX_PHILOS 200

typedef struct s_program
{
	int				philos_num;
	int				dead_flag;
	pthread_mutex_t	dead_flag_mutex;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				ready;
	int				philos_meals;
	int				philo_meals[MAX_PHILOS];
	int				philos_ids[MAX_PHILOS];
	size_t			last_meal_time[MAX_PHILOS];
	pthread_mutex_t	last_meal_time_mutex[MAX_PHILOS];
	pthread_mutex_t	print_mutex;
	pthread_t		waiter;
	pthread_t		philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];
}	t_program;

typedef struct s_hack
{
	int			*philo_id_ptr;
	t_program	*program_ptr;
}	t_hack;

int		ft_atoi(const char *nptr);
int		invalid_args(int argc, char **argv);
int		print_error(void);
void	parse_args(t_program *program, int argc, char **argv);
int		msleep(size_t msec);
size_t	get_time(void);
int		eating(int philo_id, t_program *program);
void	sleeping(int philo_id, t_program *program);
void	thinking(int philo_id, t_program *program);
void	my_print(const char *str, int philo_id,
			t_program *program, int close);
void	clean(t_program *program);
