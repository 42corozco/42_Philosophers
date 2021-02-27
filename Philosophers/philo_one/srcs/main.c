/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <3535@3535.3535>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 02:26:33 by corozco           #+#    #+#             */
/*   Updated: 2021/02/25 15:48:49 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
	if (error == 3)
		return (ms_error("Error: the philosophers aren't happy"));
	if (error == 2 || create_philos(&var) == -1)
		return (ms_error("Error: malloc"));
	return (0);
}
