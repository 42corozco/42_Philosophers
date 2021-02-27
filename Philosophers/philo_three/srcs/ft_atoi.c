/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <3535@3535.3535>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 13:30:14 by corozco           #+#    #+#             */
/*   Updated: 2021/02/25 15:55:29 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(const char s)
{
	return (s == '\t' || s == '\n' || s == '\v'
			|| s == '\f' || s == '\r' || s == ' ');
}

int			ft_atoi(const char *str)
{
	long	nb;

	nb = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			return (-1);
	}
	while (*str && *str <= '9' && *str >= '0')
	{
		nb = nb * 10 + (*str++ - 48);
		if (nb < 0)
			return (-1);
	}
	if (*str && *str != '\0' && (*str > '9' || *str < '0'))
		return (-1);
	return (nb);
}
