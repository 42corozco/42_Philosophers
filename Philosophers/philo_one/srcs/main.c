/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <3535@3535.3535>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 02:26:33 by corozco           #+#    #+#             */
/*   Updated: 2021/02/24 11:29:12 by corozco          ###   ########.fr       */
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
		if (philo->status || philo->full > 0 || 1 == is_sleeping(philo))
			break ;
		if (philo->full < 1 && !philo->status)
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

int				full_or_deat(t_var *var, int *k, int *ret)
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

void			create_phread_philo(t_var *var, pthread_t *philo_nb)
{
	int			i;

	i = 0;
	while (i < var->number_of_philosopher)
	{
		pthread_create(&philo_nb[i], NULL, fa, &var->ph[i]);
		i += 2;
	}
	ft_usleep(2, NULL);
	i = 1;
	while (i < var->number_of_philosopher)
	{
		pthread_create(&philo_nb[i], NULL, fa, &var->ph[i]);
		i += 2;
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
	create_phread_philo(var, philo_nb);
	monitor(var);
	ft_usleep(50, NULL);
	i = -1;
	while (++i < var->number_of_philosopher)
		pthread_join(philo_nb[i], NULL);
	free(philo_nb);
	free(var->ph);
	free(var->tforks);
	return (0);
}

int				main(int ac, char **av)
{
	t_var		var;
	int			error;

	(void)ac;
	if (ac < 5 || ac > 6)
		return (ms_error("Error: arguments"));
	if ((error = parse_arg(&var, ac, av)) == 1)
		return (ms_error("Error: parsing"));
	if (error == 2 || create_philos(&var) == -1)
		return (ms_error("Error: malloc"));
	return (0);
}
