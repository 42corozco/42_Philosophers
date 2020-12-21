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

typedef struct  s_philo
{
    int         id;
    int         *fl;
    int         *fr;
    int         t_die;
    int         t_eat;
    int         t_sleep;
    int         cont_eats;
}               t_philo;


typedef struct  s_var
{
    int         number_of_philosopher;
    int         *forks;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         notepmt;

	int			borrar;

    t_philo     *ph;
}               t_var;

#endif
