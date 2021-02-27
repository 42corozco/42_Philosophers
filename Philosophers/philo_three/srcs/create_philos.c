/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 14:32:11 by corozco           #+#    #+#             */
/*   Updated: 2021/02/25 14:35:07 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int		params_philo(t_var *var)
{
	int			i;

	i = -1;
	if (!(var->ph = malloc(sizeof(t_philo) * var->number_of_philosopher)))
		return (0);
	while (++i < var->number_of_philosopher)
	{
		var->ph[i].id = i + 1;
		var->ph[i].ttinit = actual_time();
		var->ph[i].ttdie = var->time_to_die;
		var->ph[i].ttsleep = var->time_to_sleep;
		var->ph[i].tteat = var->time_to_eat;
		var->ph[i].sem = &var->sem;
		var->ph[i].write = &var->write;
		var->ph[i].cont_eats = 0;
		var->ph[i].full = 0;
		var->ph[i].notepmt = var->notepmt;
		var->ph[i].lmeal = actual_time();
	}
	return (1);
}

static void		proc_philo(t_var *var, int k, int status)
{
	int			i;

	i = 0;
	while (!g_status && ++k < var->number_of_philosopher)
	{
		if (waitpid(-1, &status, 0) < 0)
			printf("Error waitpid.\n");
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
				if (++i == var->number_of_philosopher)
					printf("Bye\n");
			if (WEXITSTATUS(status) == 0)
			{
				k = -1;
				while (++k < var->number_of_philosopher)
					kill(var->ph[k].pid, SIGINT);
				free(var->ph);
				sem_unlink("/eat");
				sem_unlink("/write");
				exit(0);
			}
		}
	}
}

int				create_philos(t_var *var)
{
	int			i;

	if (!params_philo(var))
		return (-1);
	i = -1;
	while (++i < var->number_of_philosopher)
	{
		if ((var->ph[i].pid = fork()) == 0)
		{
			fa(&var->ph[i]);
			free(var->ph);
			if (g_status)
				exit(0);
			exit(1);
		}
	}
	proc_philo(var, -1, 0);
	free(var->ph);
	sem_unlink("/eat");
	sem_unlink("/write");
	return (0);
}
