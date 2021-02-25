/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <3535@3535.3535>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 13:30:14 by corozco           #+#    #+#             */
/*   Updated: 2021/02/25 14:34:42 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include "tools.h"
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>

int					g_status;

typedef struct		s_philo
{
	int				id;
	sem_t			**sem;
	sem_t			**write;
	long long		ttinit;
	long long		lmeal;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				cont_eats;
	int				full;
	int				notepmt;
	int				pid;
}					t_philo;

typedef struct		s_var
{
	int				number_of_philosopher;
	sem_t			*sem;
	sem_t			*write;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				notepmt;

	int				borrar;

	t_philo			*ph;
}					t_var;

int					is_eating(t_philo *philo);
int					is_sleeping(t_philo *philo);
int					parse_arg(t_var *var, int ac, char **av);
int					create_philos(t_var *var);
void				fa(t_philo *philo);

#endif
