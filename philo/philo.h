/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:29:05 by lferro            #+#    #+#             */
/*   Updated: 2024/06/11 16:31:35 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define DEAD 		1
# define ALIVE 		0

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	int				left_fork;
	int				right_fork;
	long			last_meal;
	int				dead;
	pthread_t		thread;
	pthread_mutex_t	mealtime;
	struct s_params	*params;

}					t_philo;

typedef struct s_params
{
	t_philo			philos[200];
	int				nbr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_nbr;

	int				filled_philos;
	int				someone_died;
	long long		start_time;

	int				finished;

	pthread_mutex_t	forks[200];
	pthread_mutex_t	death;
	pthread_mutex_t	output;
	pthread_mutex_t	filled;
	pthread_mutex_t	fini;
}					t_params;

void				check_digit_params(int argc, char const **argv);
void				snooze(int microseconds);
void				print_action(t_philo *philo, char *action,
						long long start_time, int dead);
long				get_time(void);
void				*monitor_routine(void *params);
void				*philo_routine(void *philos);
int					ft_atoi(const char *nptr);

// #define PL printf("Line: %d File: %s\n", __LINE__, __FILE__);

#endif
