/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:46:45 by corozco           #+#    #+#             */
/*   Updated: 2021/02/25 13:11:29 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <string.h>

static int		error_sem(t_var *var)
{
	sem_close(var->sem);
	return (1);
}

int				parse_arg(t_var *var, int ac, char **av)
{
	if ((var->number_of_philosopher = ft_atoi(av[1])) < 2)
		return (1);
	sem_unlink("/eat");
	sem_unlink("/write");
	memset(&var->sem, 0, sizeof(var->sem));
	if (SEM_FAILED == (var->sem = sem_open("/eat", O_CREAT, S_IRWXU,
		var->number_of_philosopher / 2)))
		return (2);
	memset(&var->write, 0, sizeof(var->write));
	if (SEM_FAILED == (var->write = sem_open("/write", O_CREAT, S_IRWXU, 1)))
		return (2);
	if ((var->time_to_die = ft_atoi(av[2])) < 1)
		return (error_sem(var));
	if ((var->time_to_eat = ft_atoi(av[3])) < 1)
		return (error_sem(var));
	if ((var->time_to_sleep = ft_atoi(av[4])) < 1)
		return (error_sem(var));
	if (ac == 6)
	{
		if ((var->notepmt = ft_atoi(av[5])) < 0)
			return (error_sem(var));
	}
	else
		var->notepmt = 0;
	return (0);
}
