/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <3535@3535.3535>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 13:30:14 by corozco           #+#    #+#             */
/*   Updated: 2021/02/24 11:39:57 by corozco          ###   ########.fr       */
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
	long	nega;

	nb = 0;
	nega = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		*str++ == '-' ? nega = -nega : nega;
	while (*str && *str <= '9' && *str >= '0')
	{
		nb = nb * 10 + (*str++ - 48);
		if (nb < 0 && nega == 1)
			return (-1);
		if (nb < 0 && nega == -1)
			return (0);
	}
	if (*str && *str != '\0' && (*str > '9' || *str < '0'))
		return (0);
	return (nb * nega);
}
