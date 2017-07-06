/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 12:51:31 by jchow             #+#    #+#             */
/*   Updated: 2017/06/27 12:54:20 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

char		*ft_strupper(char *s)
{
	char *head;

	head = s;
	while (*s)
	{
		if (ft_islower(*s))
			*s -= 32;
		++s;
	}
	return (head);
}
