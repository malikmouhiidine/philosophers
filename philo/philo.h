/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:58:12 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/02/02 20:09:30 by mmouhiid         ###   ########.fr       */
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
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				philos_meals;
	int				philos_ids[MAX_PHILOS];
	pthread_t		philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];
}	t_program;

int		msleep(size_t msec);
int		ft_atoi(const char *nptr);
int		invalid_args(int argc, char **argv);
int		print_error(void);
void	parse_args(t_program program, int argc, char **argv);