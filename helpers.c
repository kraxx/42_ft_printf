/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:02:18 by jchow             #+#    #+#             */
/*   Updated: 2017/07/05 01:02:20 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_pf(char *s)
{
	while (*s)
	{
		if (*s == -42)
			ft_putchar(0);
		else
			ft_putchar(*s);
		++s;
	}
}

void	ft_freejoin(char **s1, char **s2)
{
	free(*s1);
	*s1 = ft_strdup(*s2);
	free(*s2);
}

void	ft_freeappend(char **s1, char **s2, char *c, int left)
{
	char	*temp;

	temp = ft_strdup(c);
	if (left)
		*s2 = ft_strjoin(temp, *s1);
	else
		*s2 = ft_strjoin(*s1, temp);
	free(temp);
	free(*s1);
	*s1 = NULL;
	ft_freejoin(s1, s2);
}
