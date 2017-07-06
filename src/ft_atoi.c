/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 23:56:46 by jchow             #+#    #+#             */
/*   Updated: 2017/06/08 01:52:45 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_iswhitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r');
}

int			ft_atoi(const char *nptr)
{
	t_ull	acc;
	int		sign;

	acc = 0;
	sign = 1;
	while (ft_iswhitespace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		sign = (*nptr == '-') ? -1 : 1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
		acc = (acc * 10) + *nptr++ - '0';
	if (acc > 9223372036854775807)
		return (sign == -1 ? 0 : -1);
	return (acc * sign);
}
