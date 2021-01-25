/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <3535@3535.3535>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 13:30:14 by corozco           #+#    #+#             */
/*   Updated: 2021/01/10 15:42:59 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include "tools.h"
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct		s_fork
{
	pthread_mutex_t	fork;
	int				id;
}					t_fork;

typedef struct		s_philo
{
	int				id;
	t_fork			*fl;
	t_fork			*fr;
	long long		ttinit;
	long long		lmeal;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				cont_eats;
	int				status;
	int				full;
}					t_philo;

typedef struct		s_var
{
	int				number_of_philosopher;
	t_fork			*tforks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				notepmt;

	int				borrar;

	t_philo			*ph;
}					t_var;

#endif
