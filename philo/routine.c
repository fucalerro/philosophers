	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   routine.c                                          :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2024/05/30 14:05:56 by lferro            #+#    #+#             */
	/*   Updated: 2024/06/18 15:02:49 by lferro           ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#include "philo.h"

	int	take_forks(t_philo *philo)
	{
		t_params	*param;

		param = philo->params;
		if (philo->id % 2 == 0)
			snooze((param->time_to_eat) / 2);
		pthread_mutex_lock(&param->forks[philo->left_fork]);
		if (print_action(philo, "has taken a fork", param->start_time, ALIVE))
			return (1);
		if (param->nbr_philo > 1)
		{
			pthread_mutex_lock(&param->forks[philo->right_fork]);
			if (print_action(philo, "has taken a fork", param->start_time, ALIVE))
				return (1);
		}
		return (0);
	}

	int	put_forks(t_philo *philo)
	{
		t_params	*param;
		int			ret;

		ret = 0;
		param = philo->params;
		pthread_mutex_lock(&param->death);
		if (param->someone_died == true)
			ret = 1;
		pthread_mutex_unlock(&param->death);
		pthread_mutex_lock(&philo->mealtime);
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->mealtime);
		pthread_mutex_unlock(&param->forks[philo->right_fork]);
		pthread_mutex_unlock(&param->forks[philo->left_fork]);
		return (ret);
	}

	int	eating(t_params *param, t_philo *philo)
	{
		take_forks(philo);
		print_action(philo, "is eating", param->start_time, ALIVE);
		snooze(param->time_to_eat * 1000);
		pthread_mutex_lock(&philo->mealtime);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->mealtime);
		if (put_forks(philo) == 1)
			return (1);
		return (0);
	}

	int	philo_loop(t_params *param, t_philo *philo)
	{
		if (check_death(param) == 1)
			return (1);
		if (eating(param, philo) == 1)
			return (1);
		pthread_mutex_lock(&param->filled);
		if (param->meals_nbr != -1 && philo->times_eaten >= param->meals_nbr)
			param->filled_philos++;
		pthread_mutex_unlock(&param->filled);
		print_action(philo, "is sleeping", param->start_time, ALIVE);
		snooze(param->time_to_sleep * 1000);
		print_action(philo, "is thinking", param->start_time, ALIVE);
		pthread_mutex_lock(&param->fini);
		if (param->finished == 1)
		{
			pthread_mutex_unlock(&param->fini);
			return (1);
		}
		pthread_mutex_unlock(&param->fini);
		return (0);
	}

	void	*philo_routine(void *philos)
	{
		t_philo		*philo;
		t_params	*param;

		philo = (t_philo *)philos;
		param = philo->params;
		if (param->nbr_philo == 1)
			take_forks(philo);
		else
		{
			while (1)
			{
				if (philo_loop(param, philo) == 1)
					break ;
			}
		}
		return (NULL);
	}
