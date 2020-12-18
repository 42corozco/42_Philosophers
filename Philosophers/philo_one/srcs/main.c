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

int			p_len(char *str)
{
	int i;

	i = 0;
	while (str && *str++)
		i++;
	return (i);
}

int			ms_error(char *str)
{
	write(2, str, p_len(str));
	return (write(2, "\n", 1));
}

int			*create_forks(int n)
{
	int		*tmp;
	int		i;

	if (!(tmp = malloc(sizeof(int) * n)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		tmp[i++] = 0;
//		printf("[%d]\n", tmp[i - 1]);
	}
	return (tmp);
}

int			parse_arg(t_var *var, char **av)
{
	var->number_of_philosopher = 4;
	if (!(var->forks = create_forks(var->number_of_philosopher)))
		return (1);
	var->time_to_die = 1000;
	var->time_to_eat = 100;
	var->time_to_sleep = 100;
	var->notepmt = 10;
	(void)av;
	return (0);
	return (1); //si un erreur
}

void		*fa(void *tmp)
{
	while (1)
	{
		printf("comer %s\n", tmp);
		usleep(3000000);
		printf("pensar %s\n", tmp);
		usleep(3000000);
		printf("dormir %s\n", tmp);
		usleep(3000000);
	}
	return (NULL);
}

int				create_philos(t_var *var)
{
	pthread_t	*philo_nb;
	int			i;

	if (!(philo_nb = malloc(sizeof(pthread_t) * var->number_of_philosopher)))
		return (-1);
//	pthread_t b;
//	pthread_t c;
//	pthread_t d;

	i = 0;
	char *tab[7]= {"lundi", "mardi", "mercredi",
                     "jeudi", "vendredi", "samedi",
                     "dimanche"};

	while (i < var->number_of_philosopher)
	{
		pthread_create(&philo_nb[i], NULL, fa, tab[i]);
		i++;
	}
	i = 0;
	while (i < var->number_of_philosopher)
	{
		pthread_join(philo_nb[i], NULL);
		i++;
	}
//	pthread_create(&b, NULL, fa, "2");
//	pthread_create(&c, NULL, fa, "3");
//	pthread_create(&d, NULL, fa, "4");
//	pthread_join(b, NULL);
//	pthread_join(c, NULL);
//	pthread_join(d, NULL);
	return (0);
}

int			main(int ac, char **av)
{
	t_var	var;
	(void)ac;
//	if (ac < 5 || ac > 6)
//		return (ms_error("Error: arguments"));
	if (parse_arg(&var, av))
		return (ms_error("Error: parsing"));
/*
	struct timeval te, ta; 
	gettimeofday(&te, NULL); // get current time
	long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
	printf("seconds : [%ld] - milliseconds : [%lld]\n", te.tv_sec, milliseconds);
	gettimeofday(&ta, NULL); // get current time
	long long segundos = (ta.tv_sec*1000LL + ta.tv_usec/1000) - milliseconds;
	printf("seconds : micro seconds : [%lld]\n", segundos);
*/
	create_philos(&var);
	return (0);
}
