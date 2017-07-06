/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:57:57 by jchow             #+#    #+#             */
/*   Updated: 2017/07/05 01:57:58 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	process_u(t_str *master, t_data *data, va_list *ap)
{
	if (data->mod == 'i')
		master->tmp = ft_ulltoa_base((unsigned char)va_arg(*ap, int), 10);
	else if (data->mod == 'h')
		master->tmp = ft_ulltoa_base((unsigned short)va_arg(*ap, int), 10);
	else if (data->mod == 'm')
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned long long), 10);
	else if (data->mod == 'l')
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned long), 10);
	else if (data->mod == 'j')
		master->tmp = ft_ulltoa_base(va_arg(*ap, uintmax_t), 10);
	else if (data->mod == 'z')
		master->tmp = ft_ulltoa_base(va_arg(*ap, size_t), 10);
	else if (data->mod == 't')
		master->tmp = ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 10);
	else
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned int), 10);
}

void	process_big_u(t_str *master, t_data *data, va_list *ap)
{
	if (data->mod == 'i')
		master->tmp = ft_ulltoa_base(va_arg(*ap, long long), 10);
	else if (data->mod == 'h')
		master->tmp = ft_ulltoa_base(va_arg(*ap, long long), 10);
	else if (data->mod == 'm')
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned long long), 10);
	else if (data->mod == 'l')
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned long), 10);
	else if (data->mod == 'j')
		master->tmp = ft_ulltoa_base(va_arg(*ap, uintmax_t), 10);
	else if (data->mod == 'z')
		master->tmp = ft_ulltoa_base(va_arg(*ap, size_t), 10);
	else if (data->mod == 't')
		master->tmp = ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 10);
	else
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned int), 10);
}

void	process_p(t_str *master, va_list *ap)
{
	long temp;

	temp = va_arg(*ap, long);
	if (temp == 0)
		master->tmp = ft_strjoin(master->tmp, "0x0");
	else
		master->tmp = ft_strjoin("0x", ft_ulltoa_base(temp, 16));
}

void	process(t_str *master, t_data *data, va_list *ap)
{
	if (data->spec == 'c' || data->spec == 'C')
		process_c(master, ap);
	if (data->spec == 's')
		process_s(master, ap);
	if (data->spec == 'd' || data->spec == 'i')
		process_d(master, data, ap);
	if (data->spec == 'D')
		process_big_d(master, data, ap);
	if (data->spec == 'o')
		process_o(master, data, ap);
	if (data->spec == 'O')
		process_big_o(master, data, ap);
	if (data->spec == 'x')
		process_x(master, data, ap);
	if (data->spec == 'X')
		process_big_x(master, data, ap);
	if (data->spec == 'u')
		process_u(master, data, ap);
	if (data->spec == 'U')
		process_big_u(master, data, ap);
	if (data->spec == 'p')
		process_p(master, ap);
}
