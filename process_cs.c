/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:05:02 by jchow             #+#    #+#             */
/*   Updated: 2017/07/05 01:05:03 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	process_c(t_str *master, va_list *ap)
{
	char temp;

	temp = (char)va_arg(*ap, t_ui);
	if (temp == 0)
	{
		master->tmp = ft_strnew(1);
		master->tmp[0] = -42;
	}
	else
	{
		master->tmp = ft_strnew(1);
		master->tmp[0] = temp;
	}
}

void	process_s(t_str *master, va_list *ap)
{
	char	*temp;

	temp = va_arg(*ap, char *);
	if (temp == NULL)
	{
		master->tmp = ft_strnew(6);
		ft_strcpy(master->tmp, "(null)");
	}
	else
		master->tmp = ft_strdup(temp);
}
