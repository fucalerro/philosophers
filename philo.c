/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:05:58 by lferro            #+#    #+#             */
/*   Updated: 2024/06/04 15:56:12 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosophers(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->nbr_philo)
	{
		params->philos[i].id = i + 1;
		params->philos[i].times_eaten = 0;
		params->philos[i].left_fork = i;
		params->philos[i].right_fork = (i + 1) % params->nbr_philo;
		params->philos[i].last_meal = get_time();
		params->philos[i].params = params;
		params->philos[i].dead = false;
		i++;
	}
}

void	init_params(int argc, char const **argv, t_params *params)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		exit(1);
	}
	check_digit_params(argc, argv);
	params->someone_died = false;
	params->nbr_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->meals_nbr = ft_atoi(argv[5]);
	else
		params->meals_nbr = -1;
	params->filled_philos = 0;
	params->finished = 0;
}

void	init_mutexes(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->nbr_philo)
	{
		pthread_mutex_init(&params->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&params->output, NULL);
	pthread_mutex_init(&params->death, NULL);
	pthread_mutex_init(&params->filled, NULL);
	pthread_mutex_init(&params->fini, NULL);
}

void	dinner(t_params *params, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < params->nbr_philo)
	{
		pthread_create(&params->philos[i].thread, NULL, &philo_routine,
			&params->philos[i]);
		i++;
	}
	pthread_create(monitor, NULL, &monitor_routine, params);
	i = 0;
	while (i < params->nbr_philo)
		pthread_join(params->philos[i++].thread, NULL);
	pthread_join(*monitor, NULL);
}

int	main(int argc, char const **argv)
{
	t_params	params;
	pthread_t	monitor;
	int			i;

	params.start_time = get_time();
	init_params(argc, argv, &params);
	init_mutexes(&params);
	init_philosophers(&params);
	dinner(&params, &monitor);
	i = 0;
	while (i < params.nbr_philo)
		pthread_mutex_destroy(&params.forks[i++]);
	pthread_mutex_destroy(&params.output);
	pthread_mutex_destroy(&params.death);
	pthread_mutex_destroy(&params.filled);
	pthread_mutex_destroy(&params.fini);
	return (0);
}

// int k;
// k = 0;
// while (k < params.nbr_philo)
// 	printf("id: %d has eaten: %d\n", params.philos[k].id,
//	params.philos[k++].times_eaten);
