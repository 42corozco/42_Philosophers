/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <3535@3535.3535>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 02:26:33 by corozco           #+#    #+#             */
/*   Updated: 2021/01/26 11:54:37 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "philo_one.h"

int				ms_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (write(2, "\n", 1));
}

void			*fa(void *tmp)
{
	t_philo		*philo;

	philo = (t_philo *)tmp;
	while (philo->status != 1 && philo->full != 1)
	{
		if (philo->full > 0 || 1 == is_eating(philo))
			break ;
		if (philo->cont_eats == philo->notepmt)
			philo->full = 2;
		if (philo->full > 0 || 1 == is_sleeping(philo))
			break ;
		if (philo->full < 1)
			printf("%lldms %d is thinking\n",
				actual_time() - philo->ttinit, philo->id);
	}
	return (NULL);
}

int				params_philo(t_var *var)
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
		if (i == 0)
			var->ph[i].fl = &var->tforks[var->number_of_philosopher - 1];
		else
			var->ph[i].fl = &var->tforks[i - 1];
		var->ph[i].fr = &var->tforks[i];
		var->ph[i].cont_eats = 0;
		var->ph[i].status = 0;
		var->ph[i].full = 0;
		var->ph[i].notepmt = var->notepmt;
		var->ph[i].lmeal = actual_time();
	}
	return (1);
}

void			monitor(t_var *var)
{
	int			salida;
	int			k;

	salida = 0;
	while (1)
	{
		ft_usleep(10);
		k = -1;
		while (++k < var->number_of_philosopher)
		{
			if (var->notepmt && var->ph[k].full == 2)
			{
				printf("%lldms %d full\n", actual_time() - var->ph[k].ttinit, var->ph[k].id);
				salida++;
				var->ph[k].full = 1;
			}
			if (actual_time() > var->ph[k].lmeal + var->ph[k].ttdie)
				var->ph[k].status = 1;
			if (var->ph[k].full != 1 && var->ph[k].status == 1)
			{
				printf("%lldms %d dead\n", actual_time() - var->ph[k].ttinit, var->ph[k].id);
				return ;
			}
			if (salida == var->number_of_philosopher)
				return ;
		}
	}
}

int				create_philos(t_var *var)
{
	pthread_t	*philo_nb;
	int			i;

	if (!(philo_nb = malloc(sizeof(pthread_t) * var->number_of_philosopher)))
		return (-1);
	if (!params_philo(var))
	{
		free(philo_nb);
		return (-1);
	}
	i = 0;
	while (i < var->number_of_philosopher)
	{
		pthread_create(&philo_nb[i], NULL, fa, &var->ph[i]);
		i += 2;
	}
	ft_usleep(2);
	i = 1;
	while (i < var->number_of_philosopher)
	{
		pthread_create(&philo_nb[i], NULL, fa, &var->ph[i]);
		i += 2;
	}
	i = 0;
	monitor(var);
	free(philo_nb);
	return (0);
}

int				main(int ac, char **av)
{
	t_var		var;

	(void)ac;
	if (ac < 5 || ac > 6)
		return (ms_error("Error: arguments"));
	if (parse_arg(&var, ac, av))
		return (ms_error("Error: parsing"));
	if (create_philos(&var) == -1)
		return (ms_error("Error: malloc"));
	free(var.tforks);
	system("leaks philo_one");
	return (0);
}

/*
** hay 3 malloc
** main.c:	if (!(var->ph = malloc(sizeof(t_philo) * var->number_of_philosopher)))
** main.c:	if (!(philo_nb = malloc(sizeof(pthread_t) * var->number_of_philosopher))) ->free(philo) x2 c'est ok
** parsing.c:	if (!(tmp = malloc(sizeof(t_fork) * n))) -> free(var.tforks) main.c c'est ok
**/
