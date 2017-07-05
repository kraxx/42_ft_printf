/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 22:34:16 by jchow             #+#    #+#             */
/*   Updated: 2017/07/05 00:54:33 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Does not handle %S (wide strings)
*/

int	preprocess_flags(t_str *master, t_data *data, char *s)
{
	int	i;

	i = 0;
	while (is_flag(*s))
	{
		if (*s == '-')
			data->flag[0] = 1;
		else if (*s == '+')
			data->flag[1] = 1;
		else if (*s == ' ')
			data->flag[2] = 1;
		else if (*s == '#')
			data->flag[3] = 1;
		else if (*s == '0')
			data->flag[4] = 1;
		++master->len;
		++i;
		++s;
	}
	return (i);
}

int	preprocess_size(t_str *master, t_data *data, char *s)
{
	int i;

	i = 0;
	if (ft_isdigit(*s))
	{
		data->flag[5] = ft_atoi(s);
		while (ft_isdigit(*s++))
		{
			++master->len;
			++i;
		}
	}
	if (*s++ == '.')
	{
		++i;
		++master->len;
		data->prec = 1;
		data->flag[6] = ft_atoi(s);
		while (ft_isdigit(*s++))
		{
			++master->len;
			++i;
		}
	}
	return (i);
}

int	preprocess_mod(t_str *master, t_data *data, char *s)
{
	if (is_spec(*(s + 1)) || (is_spec(*(s + 2)) && *(s + 1) == 'h') ||
	(is_spec(*(s + 2)) && *(s + 1) == 'l'))
	{
		if (*s == 'h' && *(s + 1) == 'h')
		{
			data->mod = 'i';
			master->len += 2;
			return (2);
		}
		else if (*s == 'l' && *(s + 1) == 'l')
		{
			data->mod = 'm';
			master->len += 2;
			return (2);
		}
		else
		{
			data->mod = *s;
			++master->len;
			return (1);
		}
	}
	return (0);
}

int	preprocess(t_str *master, char *s, va_list *ap)
{
	t_data data;

	data.neg = 0;
	data.prec = 0;
	ft_bzero(data.flag, sizeof(int) * 7);
	if (*s == '%')
	{
		master->tmp = ft_strjoin(master->ret, "%");
		ft_freejoin(&master->ret, &master->tmp);
		++master->len;
		return (1);
	}
	s += preprocess_flags(master, &data, s);
	if (is_mod(*s))
		s += preprocess_size(master, &data, s);
	s += preprocess_mod(master, &data, s);
	if (is_spec(*s))
	{
		data.spec = *s;
		++master->len;
		process(master, &data, ap);
		postprocess(master, &data);
	}
	return (1);
}

int	ft_printf(const char *restrict format, ...)
{
	va_list ap;
	t_str	master;

	master.ret = ft_strnew(0);
	va_start(ap, format);
	while (*format)
	{
		master.len = 0;
		while (format[master.len] && format[master.len] != '%')
			++master.len;
		if (master.len)
		{
			master.tmp = ft_strsub(format, 0, master.len);
			master.tmp2 = ft_strjoin(master.ret, master.tmp);
			free(master.tmp);
			ft_freejoin(&master.ret, &master.tmp2);
		}
		else if (!preprocess(&master, (char *)&format[++master.len], &ap))
			return (-1);
		format += master.len;
	}
	va_end(ap);
	ft_putstr_pf(master.ret);
	return (ft_strlen(master.ret));
}
