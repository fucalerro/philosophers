/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:05:56 by lferro            #+#    #+#             */
/*   Updated: 2024/06/04 15:49:35 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	t_params	*param;

	param = philo->params;
	if (philo->id % 2 == 0)
		snooze((param->time_to_eat) / 2);
	pthread_mutex_lock(&param->forks[philo->left_fork]);
	print_action(philo, "has taken a fork", param->start_time);
	pthread_mutex_lock(&param->forks[philo->right_fork]);
	print_action(philo, "has taken a fork", param->start_time);
}

int	put_forks(t_philo *philo)
{
	t_params	*param;

	param = philo->params;
	if (param->someone_died == true)
	{
		pthread_mutex_unlock(&param->forks[philo->right_fork]);
		pthread_mutex_unlock(&param->forks[philo->left_fork]);
		return (1);
	}
	pthread_mutex_unlock(&param->death);
	philo->times_eaten++;
	pthread_mutex_unlock(&param->forks[philo->right_fork]);
	pthread_mutex_unlock(&param->forks[philo->left_fork]);
	return (0);
}

int	check_death(t_params *param)
{
	pthread_mutex_lock(&param->death);
	if (param->someone_died)
	{
		pthread_mutex_unlock(&param->death);
		return (1);
	}
	pthread_mutex_unlock(&param->death);
	return (0);
}

int	eating(t_params *param, t_philo *philo)
{
	pthread_mutex_lock(&param->death);
	if (param->someone_died)
	{
		pthread_mutex_unlock(&param->death);
		return (1);
	}
	pthread_mutex_unlock(&param->death);
	take_forks(philo);
	print_action(philo, "is eating", param->start_time);
	snooze(param->time_to_eat * 1000);
	philo->last_meal = get_time();
	if (put_forks(philo) == 1)
		return (1);
	return (0);
}

void	*philo_routine(void *philos)
{
	t_philo		*philo;
	t_params	*param;

	philo = (t_philo *)philos;
	param = philo->params;
	while (1)
	{
		if (eating(param, philo) == 1)
			break ;
		pthread_mutex_lock(&param->filled);
		if (param->meals_nbr != -1 && philo->times_eaten >= param->meals_nbr)
			param->filled_philos++;
		pthread_mutex_unlock(&param->filled);
		print_action(philo, "is sleeping", param->start_time);
		snooze(param->time_to_sleep * 1000);
		print_action(philo, "is thinking", param->start_time);
		pthread_mutex_lock(&param->fini);
		if (param->finished == 1)
		{
			pthread_mutex_unlock(&param->fini);
			break ;
		}
		pthread_mutex_unlock(&param->fini);
	}
	return (NULL);
}
