/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_big_d2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:54:10 by jchow             #+#    #+#             */
/*   Updated: 2017/07/05 01:54:11 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	process_big_d_reg(t_str *master, t_data *data, va_list *ap)
{
	va_list		cop;
	long		temp;

	va_copy(cop, *ap);
	if (va_arg(cop, long) < 0)
	{
		data->neg = 1;
		temp = -1 * va_arg(*ap, long);
		master->tmp = ft_ulltoa_base(temp, 10);
	}
	else
		master->tmp = ft_ulltoa_base(va_arg(*ap, long), 10);
}

void	process_big_jd(t_str *master, t_data *data, va_list *ap)
{
	va_list			cop;
	intmax_t		temp;

	va_copy(cop, *ap);
	if (va_arg(cop, long) < 0)
	{
		data->neg = 1;
		temp = -1 * va_arg(*ap, long);
		master->tmp = ft_ulltoa_base(temp, 10);
	}
	else
		master->tmp = ft_ulltoa_base(va_arg(*ap, long), 10);
}

void	process_big_zd(t_str *master, t_data *data, va_list *ap)
{
	va_list		cop;
	size_t		temp;

	va_copy(cop, *ap);
	if (va_arg(cop, long) < 0)
	{
		data->neg = 1;
		temp = -1 * va_arg(*ap, long);
		master->tmp = ft_ulltoa_base(temp, 10);
	}
	else
		master->tmp = ft_ulltoa_base(va_arg(*ap, long), 10);
}

void	process_big_td(t_str *master, t_data *data, va_list *ap)
{
	va_list		cop;
	ptrdiff_t	temp;

	va_copy(cop, *ap);
	if (va_arg(cop, long long) < 0)
	{
		data->neg = 1;
		temp = -1 * va_arg(*ap, long long);
		master->tmp = ft_ulltoa_base(temp, 10);
	}
	else
		master->tmp = ft_ulltoa_base(va_arg(*ap, long long), 10);
}
