/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <3535@3535.3535>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 02:26:33 by corozco           #+#    #+#             */
/*   Updated: 2021/02/04 09:32:10 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "philo_three.h"
#include <sys/types.h>
#include <unistd.h>

int				ms_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (write(2, "\n", 1));
}

void		fa(t_philo *philo)
{
	while (philo->status != 1 && philo->full != 1)
	{
		if (philo->full > 0 || philo->status || 1 == is_eating(philo))
			break ;
		if (philo->cont_eats == philo->notepmt)
			philo->full = 2;
		if (philo->full > 0 || philo->status || 1 == is_sleeping(philo))
			break ;
		if (philo->full < 1 && !philo->status)
			printf("%lldms %d is thinking\n",
					actual_time() - philo->ttinit, philo->id);
	}
	printf("%lldms %d full\n", actual_time() - philo->ttinit, philo->id);
	exit (1);
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
		var->ph[i].sem = &var->sem;
		var->ph[i].cont_eats = 0;
		var->ph[i].status = 0;
		var->ph[i].full = 0;
		var->ph[i].notepmt = var->notepmt;
		var->ph[i].lmeal = actual_time();
	}
	return (1);
}
/*
   void			monitor(t_var *var)
   {
   int			salida;
   int			k;

   salida = 0;
   while (1)
   {
//ft_usleep(10, NULL);
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
k = -1;
while (++k < var->number_of_philosopher)
var->ph[k].status = 1;
return ;
}
if (salida == var->number_of_philosopher)
return ;
}
}
}
*/
#include <sys/types.h>
#include <sys/wait.h>

int				create_philos(t_var *var)
{
	int			i;
	int			status;
	pid_t		f;

	if (!params_philo(var))
		return (-1);
	i = -1;
	status = 0;
	while (++i < var->number_of_philosopher)
	{
		if ((f = fork()) == 0)
			fa(&var->ph[i]);
	}
	i = 0;
	//	while (1)
	int k = -1;
	while (++k < var->number_of_philosopher)
	{
		if (waitpid(-1, &status, 0) < 0)
			printf("Error new.\n");
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				i++;
				if (i == var->number_of_philosopher)
					printf("todos comieron\n");
			}
			if (WEXITSTATUS(status) == 0)
			{
				printf("muerte");
				exit(1);
			}
		}
	}
	usleep(100000);
	free(var->ph);
	sem_close(var->sem);
	return (0);
}

int				main(int ac, char **av)
{
	t_var		var;
	int			error;

	if (ac < 5 || ac > 6)
		return (ms_error("Error: arguments"));
	if ((error = parse_arg(&var, ac, av)) == 1)
		return (ms_error("Error: parsing"));
	if (error == 2)
		return (ms_error("Error: semaphore"));
	if (create_philos(&var) == -1)
		return (ms_error("Error: malloc"));
	return (0);
}
