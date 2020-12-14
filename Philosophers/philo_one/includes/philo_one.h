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

typedef struct  s_philo
{
    int         number_of_philosopher;
    int         fork;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         notepmt;
}               t_philo;

#endif