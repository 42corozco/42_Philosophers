/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:15:11 by corozco           #+#    #+#             */
/*   Updated: 2021/02/25 12:55:51 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int		full_or_deat(t_var *var, int *k, int *ret)
{
	if (var->notepmt && var->ph[*k].full == 2)
	{
		printf("%lldms %d full\n", actual_time() - var->ph[*k].ttinit,
			var->ph[*k].id);
		(*ret)++;
		var->ph[*k].full = 1;
	}
	if (actual_time() > var->ph[*k].lmeal + var->ph[*k].ttdie)
		var->ph[*k].status = 1;
	if (var->ph[*k].full != 1 && var->ph[*k].status == 1)
	{
		printf("%lldms %d dead\n", actual_time() - var->ph[*k].ttinit,
			var->ph[*k].id);
		*k = -1;
		while (++(*k) < var->number_of_philosopher)
			var->ph[*k].status = 1;
		return (1);
	}
	return (0);
}

void			monitor(t_var *var)
{
	int			ret;
	int			k;

	ret = 0;
	while (1)
	{
		ft_usleep(10, NULL);
		k = -1;
		while (++k < var->number_of_philosopher)
		{
			if (full_or_deat(var, &k, &ret))
				return ;
			if (ret == var->number_of_philosopher)
				return ;
		}
	}
}
