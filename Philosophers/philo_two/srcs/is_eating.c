/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:09:31 by corozco           #+#    #+#             */
/*   Updated: 2021/02/04 09:04:01 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_two.h"

int			is_eating(t_philo *philo)
{
	sem_wait(*philo->sem);
	if (!philo->status)
	{
		printf("%lldms %d as taken a fork\n", actual_time() - philo->ttinit,
				philo->id);
		printf("%lldms %d as taken a fork\n", actual_time() - philo->ttinit,
				philo->id);
		printf("%lldms %d is eating\n", actual_time() - philo->ttinit, philo->id);
		philo->lmeal = actual_time();
		ft_usleep(philo->tteat * 1000, philo);
		philo->cont_eats++;
	}
	sem_post(*philo->sem);
	return (0);
}
