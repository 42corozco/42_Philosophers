/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sleeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:44:40 by corozco           #+#    #+#             */
/*   Updated: 2021/02/25 13:10:19 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			is_sleeping(t_philo *philo)
{
	if (!g_status)
	{
		sem_wait(*philo->write);
		printf("%lldms %d is sleeping\n", actual_time() - philo->ttinit,
			philo->id);
		sem_post(*philo->write);
		ft_usleep(philo->ttsleep * 1000);
	}
	return (0);
}
