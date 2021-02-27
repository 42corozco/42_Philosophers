/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <3535@3535.3535>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 02:26:33 by corozco           #+#    #+#             */
/*   Updated: 2021/02/25 14:34:24 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void		*monitor(void *tmp)
{
	t_philo		*philo;

	philo = (t_philo *)tmp;
	while (1)
	{
		if (philo->full == 2)
			break ;
		if (philo->full != 2 && actual_time() > philo->lmeal + philo->ttdie)
		{
			g_status = 1;
			sem_wait(*philo->write);
			printf("%lldms %d dead\n", actual_time() - philo->ttinit,
				philo->id);
			break ;
		}
	}
	return (NULL);
}

void			fa(t_philo *philo)
{
	pthread_t	philo_thread;

	pthread_create(&philo_thread, NULL, monitor, philo);
	while (g_status != 1 && philo->full != 1)
	{
		if (philo->full > 0 || g_status || 1 == is_eating(philo))
			break ;
		if (philo->cont_eats == philo->notepmt)
			philo->full = 2;
		if (philo->full > 0 || g_status || 1 == is_sleeping(philo))
			break ;
		if (philo->full < 1 && !g_status)
		{
			sem_wait(*philo->write);
			printf("%lldms %d is thinking\n",
					actual_time() - philo->ttinit, philo->id);
			sem_post(*philo->write);
		}
	}
	pthread_join(philo_thread, NULL);
	sem_close(*philo->write);
	sem_close(*philo->sem);
	if (g_status)
		return ;
	printf("%lldms %d full\n", actual_time() - philo->ttinit, philo->id);
}

int				main(int ac, char **av)
{
	t_var		var;
	int			error;

	if (ac < 5 || ac > 6)
		return (ms_error("Error: arguments"));
	g_status = 0;
	if ((error = parse_arg(&var, ac, av)) == 1)
		return (ms_error("Error: parsing"));
	if (error == 3)
		return (ms_error("Error: the philosophers aren't happy"));
	if (error == 2)
		return (ms_error("Error: semaphore"));
	if (create_philos(&var) == -1)
		return (ms_error("Error: malloc"));
	return (0);
}
