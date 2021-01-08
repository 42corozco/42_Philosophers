/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <3535@3535.3535>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 13:30:14 by corozco           #+#    #+#             */
/*   Updated: 2020/12/04 01:04:45 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include "tools.h"
#include <pthread.h>

typedef struct		s_philo
{
	int				id;
	pthread_mutex_t	*fl;
	pthread_mutex_t	*fr;
	long long		ttinit;
	long long		u_comida;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int			cont_eats;
}					t_philo;


typedef struct		s_var
{
	int				number_of_philosopher;
	pthread_mutex_t	*forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				notepmt;

	int				borrar;

	t_philo			*ph;
}					t_var;

#endif
