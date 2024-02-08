/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:00:40 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/02/08 16:39:02 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((size_t)(current_time.tv_sec * 1000 + current_time.tv_usec / 1000));
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (result > INT_MAX)
			return (-1);
		result = (result * 10) + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}

int	valid_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	invalid_args(int argc, char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200 || !valid_arg(argv[1])
		|| ft_atoi(argv[2]) <= 0 || !valid_arg(argv[2])
		|| ft_atoi(argv[3]) <= 0 || !valid_arg(argv[3])
		|| ft_atoi(argv[4]) <= 0 || !valid_arg(argv[4])
		|| (argc == 6 && (ft_atoi(argv[5]) <= 0 || !valid_arg(argv[5]))))
		return (1);
	return (0);
}

int	print_error(void)
{
	printf("Invalid argument(s)\n");
	return (-1);
}
