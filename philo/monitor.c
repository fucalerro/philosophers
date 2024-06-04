/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:35:43 by lferro            #+#    #+#             */
/*   Updated: 2024/06/04 15:56:18 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_filled(t_params *param)
{
	int	i;

	i = 0;
	while (i < param->nbr_philo)
	{
		pthread_mutex_lock(&param->filled);
		if (param->filled_philos >= param->nbr_philo)
		{
			pthread_mutex_unlock(&param->filled);
			param->finished = 1;
			exit(0);
			return ;
		}
		pthread_mutex_unlock(&param->filled);
		i++;
	}
}

void	monitor_death(t_params *param)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&param->death);
	while (i < param->nbr_philo)
	{
		if (get_time() - param->philos[i].last_meal > param->time_to_die)
		{
			print_action(&param->philos[i], "died", param->start_time);
			param->someone_died = true;
			exit(0);
		}
		i++;
	}
	pthread_mutex_unlock(&param->death);
	snooze(1000);
}

void	*monitor_routine(void *params)
{
	t_params	*param;

	param = (t_params *)params;
	while (1)
	{
		monitor_filled(param);
		monitor_death(param);
	}
}

void	check_digit_params(int argc, char const **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error: NaN\n");
				exit(1);
			}
			j++;
		}
		j = 0;
		i++;
	}
}
