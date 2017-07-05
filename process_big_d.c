/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_big_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:54:03 by jchow             #+#    #+#             */
/*   Updated: 2017/07/05 01:54:04 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	process_big_hhd(t_str *master, t_data *data, va_list *ap)
{
	va_list			cop;
	signed char		temp;

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

void	process_big_hd(t_str *master, t_data *data, va_list *ap)
{
	va_list				cop;
	unsigned short		temp;

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

void	process_big_lld(t_str *master, t_data *data, va_list *ap)
{
	va_list			cop;
	long long		temp;

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

void	process_big_ld(t_str *master, t_data *data, va_list *ap)
{
	va_list			cop;
	long			temp;

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

void	process_big_d(t_str *master, t_data *data, va_list *ap)
{
	if (data->mod == 'i')
		process_big_hhd(master, data, ap);
	else if (data->mod == 'h')
		process_big_hd(master, data, ap);
	else if (data->mod == 'm')
		process_big_lld(master, data, ap);
	else if (data->mod == 'l')
		process_big_ld(master, data, ap);
	else if (data->mod == 'j')
		process_big_jd(master, data, ap);
	else if (data->mod == 'z')
		process_big_zd(master, data, ap);
	else if (data->mod == 't')
		process_big_td(master, data, ap);
	else
		process_big_d_reg(master, data, ap);
}
