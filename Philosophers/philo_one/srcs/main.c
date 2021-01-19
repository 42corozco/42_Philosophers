/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <3535@3535.3535>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 02:26:33 by corozco           #+#    #+#             */
/*   Updated: 2021/01/12 14:37:04 by corozco          ###   ########.fr       */
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

pthread_mutex_t	*create_forks(int n)
{
	pthread_mutex_t		*tmp;
	int					i;

	if (!(tmp = malloc(sizeof(pthread_mutex_t) * n)))
		return (NULL);
	i = 0;
	while (i < n)
		pthread_mutex_init(&tmp[i++], NULL);
	return (tmp);
}

int				parse_arg(t_var *var, int ac, char **av)
{
	if ((var->number_of_philosopher = ft_atoi(av[1])) < 2)
		return (1);
	if (!(var->forks = create_forks(var->number_of_philosopher)))
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

int			is_eating(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(philo->fr);
	else
		pthread_mutex_lock(philo->fl);
	if (philo->id % 2 == 1)
		pthread_mutex_lock(philo->fl);
	else
		pthread_mutex_lock(philo->fr);
	if (actual_time() > philo->lmeal + philo->ttdie)
	{
		printf("%lld %d dead\n", actual_time() - philo->ttinit, philo->id);
		philo->status = 1;
		return 1 ;
	}
	printf("%lld %d as taken a fork\n", actual_time() - philo->ttinit, philo->id);
	printf("%lld %d as taken a fork\n", actual_time() - philo->ttinit, philo->id);
	printf("%lld %d is eating\n", actual_time() - philo->ttinit, philo->id);
	philo->lmeal = actual_time();
	ft_usleep(philo->tteat * 1000);
	philo->cont_eats++;
	//if (actual_time() + philo->tteat > philo->lmeal+ philo->ttdie)
//	if (actual_time() - philo->lmeal > philo->ttdie)

//	printf("actu %lld\n", actual_time());
//	printf("actu + ttat %lld\n", actual_time() + philo->tteat);
//	printf("llmea %lld\n", philo->lmeal);
//	printf("actu + ttat %lld\n", philo->lmeal + philo->ttdie);
	pthread_mutex_unlock(philo->fl);
	pthread_mutex_unlock(philo->fr);
	return (0);
}

int			is_sleeping(t_philo *philo)
{
	printf("%lld %d is sleeping\n", actual_time() - philo->ttinit, philo->id);
	ft_usleep(philo->ttsleep * 1000);
//	if (actual_time() - philo->lmeal > philo->ttdie)
	if (actual_time() > philo->lmeal + philo->ttdie)
	{
		printf("%lld %d dead\n", actual_time() - philo->ttinit, philo->id);
		philo->status = 1;
		return 1 ;
	}
	return (0);
}

void			*moni(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	while (philo->status != 1)
	{
		if (actual_time() - philo->lmeal > philo->ttdie)
		{
			printf("%lld %d dead\n", actual_time() - philo->ttinit, philo->id);
			philo->status = 1;
			exit(1);
			break;
		}
	}
	return (NULL);
}

void			*fa(void *tmp)
{
	t_philo		*philo;
	pthread_t	sta;

	philo = (t_philo *)tmp;
	while (philo->status != 1)
	{
		//if (actual_time() - philo->lmeal > philo->ttdie)
/*		if (actual_time() + philo->tteat > philo->lmeal+ philo->ttdie)
		{
			ft_usleep(philo->ttdie * 1000);
			printf("%lld %d dead\n", actual_time() - philo->ttinit, philo->id);
			philo->status = 1;
			break ;
		}
		else*/
		if (1 == is_eating(philo))
			break;
//		if (actual_time() - philo->lmeal > philo->ttdie)
/*		if (actual_time() + philo->ttsleep > philo->lmeal+ philo->ttdie)
		{
			ft_usleep(philo->ttdie * 1000);
			printf("%lld %d dead\n", actual_time() - philo->ttinit, philo->id);
			philo->status = 1;
			break ;
		}
		else
		{*/
			if (1 == is_sleeping(philo))
				break;
			printf("%lld %d is thinking\n", actual_time() - philo->ttinit, philo->id);
		//}
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
			var->ph[i].fl = &var->forks[var->number_of_philosopher - 1];
		else
			var->ph[i].fl = &var->forks[i - 1];
		var->ph[i].fr = &var->forks[i];
		var->ph[i].cont_eats = 0;
		var->ph[i].status = 0;
		var->ph[i].lmeal = actual_time();
	}
	return (1);
}

int				create_philos(t_var *var)
{
	pthread_t	*philo_nb;
	int			i;

	if (!(philo_nb = malloc(sizeof(pthread_t) * var->number_of_philosopher)))
		return (-1);
	if (!params_philo(var))
		return (-1);
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
//	while (i < var->number_of_philosopher)
//		pthread_join(philo_nb[i++], NULL);
	while (1)
	{
		ft_usleep(10); // que sea del mismo tiempo de muerte + 5ms
		int k;

		k = 0;
		while (k < var->number_of_philosopher)
		{
			if (var->ph[k].status == 1)
				return (1);
		}
	}
	return (0);
}

int				main(int ac, char **av)
{
	t_var	var;

	(void)ac;
	if (ac < 5 || ac > 6)
		return (ms_error("Error: arguments"));
	if (parse_arg(&var, ac, av))
		return (ms_error("Error: parsing"));
	create_philos(&var);
	return (0);
}
