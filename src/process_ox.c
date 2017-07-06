/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:12:38 by jchow             #+#    #+#             */
/*   Updated: 2017/07/05 02:11:57 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	process_o(t_str *master, t_data *data, va_list *ap)
{
	if (data->mod == 'i')
		master->tmp = ft_ulltoa_base((unsigned char)va_arg(*ap, int), 8);
	else if (data->mod == 'h')
		master->tmp = ft_ulltoa_base((unsigned short)va_arg(*ap, int), 8);
	else if (data->mod == 'm')
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned long long), 8);
	else if (data->mod == 'l')
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned long), 8);
	else if (data->mod == 'j')
		master->tmp = ft_ulltoa_base(va_arg(*ap, uintmax_t), 8);
	else if (data->mod == 'z')
		master->tmp = ft_ulltoa_base(va_arg(*ap, size_t), 8);
	else if (data->mod == 't')
		master->tmp = ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 8);
	else
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned int), 8);
}

void	process_big_o(t_str *master, t_data *data, va_list *ap)
{
	if (data->mod == 'i')
		master->tmp = ft_ulltoa_base(va_arg(*ap, long long), 8);
	else if (data->mod == 'h')
		master->tmp = ft_ulltoa_base(va_arg(*ap, long long), 8);
	else if (data->mod == 'm')
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned long long), 8);
	else if (data->mod == 'l')
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned long), 8);
	else if (data->mod == 'j')
		master->tmp = ft_ulltoa_base(va_arg(*ap, uintmax_t), 8);
	else if (data->mod == 'z')
		master->tmp = ft_ulltoa_base(va_arg(*ap, size_t), 8);
	else if (data->mod == 't')
		master->tmp = ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 8);
	else
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned long), 8);
}

void	process_x(t_str *m, t_data *data, va_list *ap)
{
	if (data->mod == 'i')
		m->tmp = ft_ulltoa_base((unsigned char)va_arg(*ap, int), 16);
	else if (data->mod == 'h')
		m->tmp = ft_ulltoa_base((unsigned short)va_arg(*ap, int), 16);
	else if (data->mod == 'm')
		m->tmp = ft_ulltoa_base(va_arg(*ap, unsigned long long), 16);
	else if (data->mod == 'l')
		m->tmp = ft_ulltoa_base(va_arg(*ap, unsigned long), 16);
	else if (data->mod == 'j')
		m->tmp = ft_ulltoa_base(va_arg(*ap, uintmax_t), 16);
	else if (data->mod == 'z')
		m->tmp = ft_ulltoa_base(va_arg(*ap, size_t), 16);
	else if (data->mod == 't')
		m->tmp = ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 16);
	else
		m->tmp = ft_ulltoa_base(va_arg(*ap, unsigned int), 16);
}

void	process_big_x(t_str *m, t_data *data, va_list *ap)
{
	if (data->mod == 'i')
		m->tmp = ft_strupper(ft_ulltoa_base((t_uc)va_arg(*ap, int), 16));
	else if (data->mod == 'h')
		m->tmp = ft_strupper(ft_ulltoa_base((t_ush)va_arg(*ap, int), 16));
	else if (data->mod == 'm')
		m->tmp = ft_strupper(ft_ulltoa_base(va_arg(*ap, t_ull), 16));
	else if (data->mod == 'l')
		m->tmp = ft_strupper(ft_ulltoa_base(va_arg(*ap, unsigned long), 16));
	else if (data->mod == 'j')
		m->tmp = ft_strupper(ft_ulltoa_base(va_arg(*ap, uintmax_t), 16));
	else if (data->mod == 'z')
		m->tmp = ft_strupper(ft_ulltoa_base(va_arg(*ap, size_t), 16));
	else if (data->mod == 't')
		m->tmp = ft_strupper(ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 16));
	else
		m->tmp = ft_strupper(ft_ulltoa_base(va_arg(*ap, unsigned int), 16));
}
