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

int			parse_arg(t_philo *var, char **av)
{
	var->number_of_philosopher = 3;
	var->fork = var->number_of_philosopher;
	var->time_to_die = 1000000;
	var->time_to_eat = 20;
	var->time_to_sleep = 20;
	var->notepmt = 10;
	(void)av;
	return (0);
	return (1); //si un erreur
}

void		*fa(void *tmp)
{
		//	usleep(10);
	while (1)
	{

		write(1, (char*)tmp, 5);
		write(1, "\n", 1);
	}
	return (NULL);
}

int			main(int ac, char **av)
{
	t_philo	var;
/* 	pthread_t a;
	pthread_t b;
	pthread_t c; */
	(void)ac;
//	if (ac < 5 || ac > 6)
//		return (ms_error("Error: arguments"));
	if (parse_arg(&var, av))
		return (ms_error("Error: parsing"));
	
	struct timeval te, ta; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
	printf("seconds : [%ld] - micro seconds : [%lld]\n", te.tv_sec, milliseconds);

//	for (int i = 0; i < 100000000; i++)
		;
	gettimeofday(&ta, NULL); // get current time
	long long segundos = (ta.tv_sec*1000LL + ta.tv_usec/1000) - milliseconds;
	printf("seconds : micro seconds : [%lld]\n", segundos);
/*
	pthread_create(&a, NULL, fa, "1");
	pthread_create(&b, NULL, fa, "2");
	pthread_create(&c, NULL, fa, "3");
	pthread_join(a, NULL);
	pthread_join(b, NULL);
	pthread_join(c, NULL);
*/
	return (0);
}
