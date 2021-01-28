/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:09:31 by corozco           #+#    #+#             */
/*   Updated: 2021/01/28 13:46:17 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_two.h"

static void	check_fork(int *id, int philo, pthread_mutex_t *fork)
{
	while (*id == philo)
		ft_usleep(2);
	pthread_mutex_lock(fork);
	*id = philo;
}

int			is_eating(t_philo *philo)
{
	if (philo->id % 2 == 1)
		check_fork(&philo->fr->id, philo->id, &philo->fr->fork);
	else
		check_fork(&philo->fl->id, philo->id, &philo->fl->fork);
	if (philo->id % 2 == 1)
		check_fork(&philo->fl->id, philo->id, &philo->fl->fork);
	else
		check_fork(&philo->fr->id, philo->id, &philo->fr->fork);
	printf("%lldms %d as taken a fork\n", actual_time() - philo->ttinit,
		philo->id);
	printf("%lldms %d as taken a fork\n", actual_time() - philo->ttinit,
		philo->id);
	printf("%lldms %d is eating\n", actual_time() - philo->ttinit, philo->id);
	philo->lmeal = actual_time();
	ft_usleep(philo->tteat * 1000);
	philo->cont_eats++;
	pthread_mutex_unlock(&philo->fl->fork);
	pthread_mutex_unlock(&philo->fr->fork);
	return (0);
}
