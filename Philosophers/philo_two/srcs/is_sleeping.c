/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sleeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:44:40 by corozco           #+#    #+#             */
/*   Updated: 2021/02/25 12:59:56 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			is_sleeping(t_philo *philo)
{
	if (!philo->status)
	{
		printf("%lldms %d is sleeping\n", actual_time() - philo->ttinit,
			philo->id);
		ft_usleep(philo->ttsleep * 1000, philo);
	}
	return (0);
}
