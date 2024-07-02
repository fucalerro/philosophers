/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:35:43 by lferro            #+#    #+#             */
/*   Updated: 2024/07/02 16:30:54 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor_filled(t_params *param)
{
	int	i;

	i = 0;
	while (i < param->nbr_philo)
	{
		pthread_mutex_lock(&param->filled);
		if (param->filled_philos >= param->nbr_philo)
		{
			pthread_mutex_unlock(&param->filled);
			pthread_mutex_lock(&param->fini);
			param->finished = 1;
			pthread_mutex_unlock(&param->fini);
			return (1);
		}
		pthread_mutex_unlock(&param->filled);
		i++;
	}
	return (0);
}

static int	print_death(t_params *param, int i)
{
	if (param->someone_died == 1)
	{
		printf("%lld %d died\n", (long long)get_time() - param->start_time,
			param->philos[i].id);
		pthread_mutex_unlock(&param->death);
		return (1);
	}
	return (0);
}






int	monitor_death(t_params *param)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (i < param->nbr_philo)
	{
		pthread_mutex_lock(&param->philos[i].mealtime);
		if (get_time() - param->philos[i].last_meal > param->time_to_die)
		{
			pthread_mutex_unlock(&param->philos[i].mealtime);
			pthread_mutex_lock(&param->death);
			param->someone_died++;
			if (print_death(param, i) == 1)
				ret = 1;
			else
				pthread_mutex_unlock(&param->death);
		}
		else
			pthread_mutex_unlock(&param->philos[i].mealtime);
		i++;
	}
	snooze(9000);
	return (ret);
}

void	*monitor_routine(void *params)
{
	t_params	*param;

	param = (t_params *)params;
	while (1)
	{
		if (monitor_death(param))
			break ;
		if (monitor_filled(param))
			break ;
	}
	return (0);
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
