/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   takeforks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:24:36 by lferro            #+#    #+#             */
/*   Updated: 2024/07/02 16:51:43 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	take_forks_single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->forks[philo->left_fork]);
	if (print_action(philo, "has taken a fork", philo->params->start_time,
			ALIVE))
	{
		pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
		return (1);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	t_params	*param;
	int			first_fork;
	int			second_fork;

	param = philo->params;
	first_fork = min(philo->left_fork, philo->right_fork);
	second_fork = max(philo->left_fork, philo->right_fork);
	pthread_mutex_lock(&param->forks[first_fork]);
	if (print_action(philo, "has taken a fork", param->start_time, ALIVE))
	{
		pthread_mutex_unlock(&param->forks[first_fork]);
		return (1);
	}
	if (first_fork != second_fork)
	{
		pthread_mutex_lock(&param->forks[second_fork]);
		if (print_action(philo, "has taken a fork", param->start_time, ALIVE))
		{
			pthread_mutex_unlock(&param->forks[second_fork]);
			return (1);
		}
	}
	else
		pthread_mutex_unlock(&param->forks[first_fork]);
	return (0);
}
