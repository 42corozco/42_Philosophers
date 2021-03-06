/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <3535@3535.3535>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 13:30:14 by corozco           #+#    #+#             */
/*   Updated: 2021/02/25 12:59:44 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include "tools.h"
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct		s_philo
{
	int				id;
	sem_t			**sem;
	long long		ttinit;
	long long		lmeal;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				cont_eats;
	int				status;
	int				full;
	int				notepmt;
}					t_philo;

typedef struct		s_var
{
	int				number_of_philosopher;
	sem_t			*sem;
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
void				ft_usleep(unsigned int n, t_philo *th);
void				monitor(t_var *var);

#endif
