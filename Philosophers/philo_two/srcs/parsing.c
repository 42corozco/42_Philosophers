/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:46:45 by corozco           #+#    #+#             */
/*   Updated: 2021/01/28 13:46:36 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static t_fork	*create_forks(int n)
{
	t_fork		*tmp;
	int			i;

	if (!(tmp = malloc(sizeof(t_fork) * n)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&tmp[i].fork, NULL);
		tmp[i++].id = -35;
	}
	return (tmp);
}

int				parse_arg(t_var *var, int ac, char **av)
{
	if ((var->number_of_philosopher = ft_atoi(av[1])) < 2)
		return (1);
	if (!(var->tforks = create_forks(var->number_of_philosopher)))
		return (-1);
	if ((var->time_to_die = ft_atoi(av[2])) < 1)
		return (1);
	if ((var->time_to_eat = ft_atoi(av[3])) < 1)
		return (1);
	if ((var->time_to_sleep = ft_atoi(av[4])) < 1)
		return (1);
	if (ac == 6)
	{
		if ((var->notepmt = ft_atoi(av[5])) < 0)
			return (1);
	}
	else
		var->notepmt = 0;
	return (0);
}
