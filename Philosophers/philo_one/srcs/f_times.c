/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_times.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:56:06 by corozco           #+#    #+#             */
/*   Updated: 2021/02/25 12:56:16 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			ms_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (write(2, "\n", 1));
}

long long	actual_time(void)
{
	struct timeval	te;
	long long		mili;

	gettimeofday(&te, NULL);
	mili = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (mili);
}

void		ft_usleep(unsigned int n, t_philo *th)
{
	struct timeval	start;
	struct timeval	step;
	int				no_null;

	no_null = 0;
	if (th)
		no_null = 1;
	gettimeofday(&start, NULL);
	while (1)
	{
		if (no_null && th->status)
			break ;
		usleep(10);
		gettimeofday(&step, NULL);
		if ((size_t)(((size_t)(step.tv_sec - start.tv_sec)) * 1000000 +
					((size_t)(step.tv_usec - start.tv_usec))) > n)
			break ;
	}
}
