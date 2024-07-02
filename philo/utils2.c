/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:52:04 by lferro            #+#    #+#             */
/*   Updated: 2024/07/02 13:38:35 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
