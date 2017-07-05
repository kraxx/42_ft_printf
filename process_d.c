/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:09:06 by jchow             #+#    #+#             */
/*   Updated: 2017/07/05 01:48:34 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	process_hhd(t_str *master, t_data *data, va_list *ap)
{
	va_list		cop;
	t_uc		temp;

	va_copy(cop, *ap);
	if ((signed char)va_arg(cop, int) < 0)
	{
		data->neg = 1;
		temp = -1 * (signed char)va_arg(*ap, int);
		master->tmp = ft_itoa(temp);
	}
	else
		master->tmp = ft_itoa((signed char)va_arg(*ap, int));
}

void	process_hd(t_str *master, t_data *data, va_list *ap)
{
	va_list			cop;
	unsigned short	temp;

	va_copy(cop, *ap);
	if ((short)va_arg(cop, int) < 0)
	{
		data->neg = 1;
		temp = -1 * (short)va_arg(*ap, int);
		master->tmp = ft_itoa(temp);
	}
	else
		master->tmp = ft_itoa((short)va_arg(*ap, int));
}

void	process_lld(t_str *master, t_data *data, va_list *ap)
{
	va_list		cop;
	long long	temp;

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

void	process_ld(t_str *master, t_data *data, va_list *ap)
{
	va_list	cop;
	long	temp;

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

void	process_d(t_str *master, t_data *data, va_list *ap)
{
	if (data->mod == 'i')
		process_hhd(master, data, ap);
	else if (data->mod == 'h')
		process_hd(master, data, ap);
	else if (data->mod == 'm')
		process_lld(master, data, ap);
	else if (data->mod == 'l')
		process_ld(master, data, ap);
	else if (data->mod == 'j')
		process_jd(master, data, ap);
	else if (data->mod == 'z')
		process_zd(master, data, ap);
	else if (data->mod == 't')
		process_td(master, data, ap);
	else
		process_d_reg(master, data, ap);
}
