/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <3535@3535.3535>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 02:26:33 by corozco           #+#    #+#             */
/*   Updated: 2020/12/05 04:21:42 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include "philo_one.h"

long long	actual_time()
{
	struct timeval	te;
	long long		mili;

	gettimeofday(&te, NULL);
	mili = te.tv_sec*1000LL + te.tv_usec/1000;
	return (mili);
}

void    ft_usleep(unsigned int n)
{
	struct timeval    start;
	struct timeval    step;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(10);
		gettimeofday(&step, NULL);
		if ((size_t)(((size_t)(step.tv_sec - start.tv_sec)) * 1000000 +
					((size_t)(step.tv_usec - start.tv_usec))) > n)
			break ;
	}
}

void			printfphilo(t_var *var)
{
	int i;

	i = -1;
	while (++i < var->number_of_philosopher)
	{
		printf("philo->id[%d]\n", var->ph[i].id);
		//	ft_usleep(10 * 1000);
		printf("actual_time [%lld] ultima comida[%lld]\n", actual_time(), var->ph[i].u_comida);
	}
}


int			ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str && *str++)
		i++;
	return (i);
}

int			ms_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (write(2, "\n", 1));
}

pthread_mutex_t		*create_forks(int n)
{
	pthread_mutex_t		*tmp;
	int					i;

	if (!(tmp = malloc(sizeof(pthread_mutex_t) * n)))
		return (NULL);
	i = 0;
	while (i < n)
		pthread_mutex_init (&tmp[i++], NULL);
	return (tmp);
}

int			parse_arg(t_var *var, int ac, char **av)
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
	printf("philos = [%d]\n", var->number_of_philosopher);
	printf("die = [%d]\n", var->time_to_die);
	printf("eat = [%d]\n", var->time_to_eat);
	printf("sleep = [%d]\n", var->time_to_sleep);
	printf("notepmt = [%d]\n", var->notepmt);
	return (0);
}

void		*fa(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	while (1)
	{
		printf("%lld %d is eating\n", actual_time() - philo->ttinit, philo->id);
		ft_usleep(philo->tteat * 1000);
		printf("%lld %d is sleeping\n", actual_time() - philo->ttinit, philo->id);
		ft_usleep(philo->ttsleep* 1000);
		printf("%lld %d is thinking\n", actual_time() - philo->ttinit, philo->id);
		ft_usleep(400* 1000);
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
		var->ph[i].u_comida = actual_time();
	}
	printfphilo(var);
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
	char *tab[7]= {"lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi", "dimanche"};
	while (i < var->number_of_philosopher)
	{
		pthread_create(&philo_nb[i], NULL, fa, &var->ph[i]);
		//pthread_create(&philo_nb[i], NULL, fa, var);
		i++;
	}
	i = 0;
	while (i < var->number_of_philosopher)
	{
		pthread_join(philo_nb[i], NULL);
		i++;
	}

	return (0);
}

int			main(int ac, char **av)
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
