/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:42:26 by lferro            #+#    #+#             */
/*   Updated: 2024/06/11 16:30:33 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static int	ft_isspace(const char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\r'
		|| c == '\f')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 1;
	j = 0;
	k = 0;
	while (ft_isspace(nptr[j]) == 1)
		j++;
	if (nptr[j] == '+')
		j++;
	else if (nptr[j] == '-')
	{
		i = -1;
		j++;
	}
	while (nptr[j] >= '0' && nptr[j] <= '9')
		k = k * 10 + nptr[j++] - 48;
	return (k * i);
}

void	snooze(int microseconds)
{
	struct timeval	start;
	struct timeval	current;
	long long		elapsed;

	gettimeofday(&start, NULL);
	elapsed = 0;
	while (elapsed < microseconds)
	{
		usleep(100);
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) * 1000000LL + (current.tv_usec
				- start.tv_usec);
	}
}

void	print_action(t_philo *philo, char *action, long long start_time,
		int dead)
{
	int	i;

	if (dead)
		printf("%lld %d died\n", (long long)get_time() - start_time, philo->id);
	if (dead)
		exit(0);
	i = 0;
	while (i < philo->params->nbr_philo)
	{
		if (philo->params->philos[i].dead)
			return ;
		i++;
	}
	pthread_mutex_lock(&philo->params->output);
	pthread_mutex_lock(&philo->params->death);
	if (philo->params->someone_died)
	{
		pthread_mutex_unlock(&philo->params->death);
		pthread_mutex_unlock(&philo->params->output);
		return ;
	}
	printf("%lld %d %s\n", (long long)get_time() - start_time, philo->id,
		action);
	pthread_mutex_unlock(&philo->params->death);
	pthread_mutex_unlock(&philo->params->output);
}
