/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 22:34:16 by jchow             #+#    #+#             */
/*   Updated: 2017/06/29 00:32:58 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

/*

http://en.cppreference.com/w/cpp/io/c/fprintf
http://personal.ee.surrey.ac.uk/Personal/R.Bowden/C/printf.html
http://alvinalexander.com/programming/printf-format-cheat-sheet

flags:
-: left-justify
+: for numbers; precede result with + or -
sp: for numbers; if no '-' sign, blank space before value
#: used with o, x or X. precede with 0, 0x, or 0X
0: left-pads number with zeroes instead of spaces
num: field width; chars will take up this amount of space
.: precision.

argument type: 
hh: signed char
h: short 
l: long 
ll: long long 
j: intmax_t
z: size_t 

t: ptrdiff_t
L: long double

conversion specifiers:
c C: char
s S: string
d D i: integer
o O: octal
x X: hex
u U: unsigned int to decimal 
p: pointer

optional specs:
f F: floating point to decimal
e E: decimal exponent
a A: foating point to hex exponent
g G: floating point to decimal or decimal exponent
n: number of chars written so far
*/

int is_flag(char c)
{
	return (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0');
}

int is_mod(char c)
{
	return (c == 'h' || c == 'l' ||	c == 'j' ||	c == 'z' || c == 't');
}

int is_spec(char c)
{
	return (c == 'c' || c == 'C' || c == 's' || c == 'S' ||
	c == 'd' ||	c == 'D' || c == 'i' || c == 'o' || c == 'O' ||
	c == 'x' || c == 'X' || c == 'u' || c == 'U' || c == 'p');
}

void	postprocess(t_str *master, t_data *data, char *s, va_list *ap)
{
	int i;
	int j;

	if (data->spec != 's' && data->spec != 'S')
	{
		if (data->flag[3])
		{
			if (data->spec == 'o' || data->spec == 'O')
			{
				if (ft_strlen(master->tmp) != 1 && ft_strcmp(master->tmp, "0"))
					master->tmp = ft_strjoin("0", master->tmp);
			}
			else if (data->spec == 'x')
				master->tmp = ft_strjoin("0x", master->tmp);
			else if (data->spec == 'X')
				master->tmp = ft_strjoin("0X", master->tmp);
		}
		i = data->flag[6];
		j = ft_strlen(master->tmp);
		while (i-- > j)
			master->tmp = ft_strjoin("0", master->tmp);
		if (data->flag[5] >= data->flag[6])
		{
			if (!data->flag[4] || data->flag[0]) //not 0 buffered
			{
				if (!data->neg)
				{
					if (data->flag[1])
						master->tmp = ft_strjoin("+", master->tmp);
					else if (data->flag[2])
						master->tmp = ft_strjoin(" ", master->tmp);
				}
				else if (data->neg)
					master->tmp = ft_strjoin("-", master->tmp);	
				i = data->flag[5];
				j = ft_strlen(master->tmp);
				while (i-- > j)
				{
					if (data->flag[0]) // left aligned
						master->tmp = ft_strjoin(master->tmp, " ");
					else // right aligned
						master->tmp = ft_strjoin(" ", master->tmp);
				}			
			}
			else // 0 buffered
			{
				if (data->flag[6]) //precision
				{
					while (data->flag[6] > ft_strlen(master->tmp))
							master->tmp = ft_strjoin("0", master->tmp);
					if (!data->neg)
					{
						if (data->flag[1])
							master->tmp = ft_strjoin("+", master->tmp);
						else if (data->flag[2])
							master->tmp = ft_strjoin(" ", master->tmp);
					}
					else if (data->neg)
						master->tmp = ft_strjoin("-", master->tmp);	
					i = data->flag[5];
					j = ft_strlen(master->tmp);
					while (i-- > j)
							master->tmp = ft_strjoin(" ", master->tmp);
				}
				else //no precision
				{
					i = data->flag[5];
					j = ft_strlen(master->tmp) + ((data->flag[1] || data->flag[2] || data->neg) ? 1 : 0);
					while (i-- > j)
							master->tmp = ft_strjoin("0", master->tmp);
					if (!data->neg)
					{
						if (data->flag[1])
							master->tmp = ft_strjoin("+", master->tmp);
						else if (data->flag[2])
							master->tmp = ft_strjoin(" ", master->tmp);
					}
					else if (data->neg)
						master->tmp = ft_strjoin("-", master->tmp);	
				}
			}
		}
		else
		{
			if (!data->neg)
			{
				if (data->flag[1])
					master->tmp = ft_strjoin("+", master->tmp);
				else if (data->flag[2])
					master->tmp = ft_strjoin(" ", master->tmp);
			}
			else if (data->neg)
				master->tmp = ft_strjoin("-", master->tmp);	
		}		
	}
	else if (data->spec == 's' || data->spec == 'S') //string truncate
	{
		if (data->prec)
		{
			master->tmp = ft_strsub(master->tmp, 0, data->flag[6]);
			if (data->flag[0])
				while (data->flag[5]-- > data->flag[6])
					master->tmp = ft_strjoin(master->tmp, " ");
			else
				while (data->flag[5]-- > data->flag[6])
					master->tmp = ft_strjoin(" ", master->tmp);	
		}
	}
	master->ret = ft_strjoin(master->ret, master->tmp);
}

void	process_c(t_str *master, t_data *data, char *s, va_list *ap)
{
	// if (data->mod == 'l')
	// 	// wint_t, maybe it's different
	// 	return (process_C(master, data, s, ap));
	// else
	// char *temp;

	// temp = ft_strnew(1);
	// temp = (char)va_arg(*ap, t_ui);
	// if (ft_strcmp(temp, 0))
	// {
	// 	master->tmp = ft_strnew(1);
	// 	master->tmp[0] = (char)va_arg(*ap, t_ui);		
	// }
	// else
	{ 		
		master->tmp = ft_strnew(1);
		master->tmp[0] = (char)va_arg(*ap, t_ui);
	}
}

void	process_C(t_str *master, t_data *data, char *s, va_list *ap)
{
	// wide chars. yep.
}

void	process_s(t_str *master, t_data *data, char *s, va_list *ap)
{
	// if (data->mod == 'l')
	// {

	// }
	// else
		master->tmp = va_arg(*ap, char *);
}

void	process_S(t_str *master, t_data *data, char *s, va_list *ap)
{
	// wide chars. yep.
}

void	process_d(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->mod == 'i')
	{
		va_list cop;
		va_copy(cop, *ap);
		if ((signed char)va_arg(cop, int) < 0)
		{
			data->neg = 1;
			unsigned char temp = -1 * (signed char)va_arg(*ap, int);
			master->tmp = ft_itoa(temp);
		}
		else
			master->tmp = ft_itoa((signed char)va_arg(*ap, int));
	}
	else if (data->mod == 'h')
	{
		va_list cop;
		va_copy(cop, *ap);
		if ((short)va_arg(cop, int) < 0)
		{
			data->neg = 1;
			unsigned short temp = -1 * (short)va_arg(*ap, int);
			master->tmp = ft_itoa(temp);					
		}
		else
			master->tmp = ft_itoa((short)va_arg(*ap, int));
	}
	else if (data->mod == 'm')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long long) < 0)
		{
			data->neg = 1;
			long long temp = -1 * va_arg(*ap, long long);
			master->tmp = ft_ulltoa_base(temp, 10);					
		}
		else
			master->tmp = ft_ulltoa_base(va_arg(*ap, long long), 10);
	}
	else if (data->mod == 'l')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long) < 0)
		{
			data->neg = 1;
			long temp = -1 * va_arg(*ap, long);
			master->tmp = ft_ulltoa_base(temp, 10);					
		}
		else
			master->tmp = ft_ulltoa_base(va_arg(*ap, long), 10);
	}
	else if (data->mod == 'j')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, intmax_t) < 0)
		{
			data->neg = 1;
			intmax_t temp = -1 * va_arg(*ap, intmax_t);
			master->tmp =ft_ulltoa_base(temp, 10);					
		}
		else
			master->tmp = ft_ulltoa_base(va_arg(*ap, intmax_t), 10);
	}
	else if (data->mod == 'z')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long) < 0)
		{
			data->neg = 1;
			size_t temp = -1 * va_arg(*ap, size_t);
			master->tmp = ft_ulltoa_base(temp, 10);					
		}
		else
			master->tmp = ft_ulltoa_base(va_arg(*ap, size_t), 10);
	}
	else if (data->mod == 't')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, ptrdiff_t) < 0)
		{
			data->neg = 1;
			ptrdiff_t temp = -1 * va_arg(*ap, ptrdiff_t);
			master->tmp = ft_ulltoa_base(temp, 10);					
		}
		else
			master->tmp = ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 10);
	}
	else
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, int) < 0)
		{
			data->neg = 1;
			unsigned int temp = -1 * va_arg(*ap, int);
			master->tmp = ft_ulltoa_base(temp, 10);					
		}
		else
			master->tmp = ft_itoa(va_arg(*ap, int));
	}
}

void	process_D(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->mod == 'i')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long) < 0)
		{
			data->neg = 1;
			signed char temp = -1 * va_arg(*ap, long);
			master->tmp = ft_ulltoa_base(temp, 10);					
		}
		else
			master->tmp = ft_ulltoa_base(va_arg(*ap, long), 10);
	}
	else if (data->mod == 'h')
	{
		va_list cop;
		va_copy(cop, *ap);
		if ((short)va_arg(cop, long) < 0)
		{
			data->neg = 1;
			unsigned short temp = -1 * (short)va_arg(*ap, long);
			master->tmp = ft_itoa(temp);					
		}
		else
			master->tmp = ft_itoa((short)va_arg(*ap, long));
	}
	else if (data->mod == 'm')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long long) < 0)
		{
			data->neg = 1;
			long long temp = -1 * va_arg(*ap, long long);
			master->tmp = ft_ulltoa_base(temp, 10);					
		}
		else
			master->tmp = ft_ulltoa_base(va_arg(*ap, long long), 10);
	}
	else if (data->mod == 'l')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long) < 0)
		{
			data->neg = 1;
			long temp = -1 * va_arg(*ap, long);
			master->tmp = ft_ulltoa_base(temp, 10);					
		}
		else
			master->tmp = ft_ulltoa_base(va_arg(*ap, long), 10);
	}
	else if (data->mod == 'j')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, intmax_t) < 0)
		{
			data->neg = 1;
			intmax_t temp = -1 * va_arg(*ap, intmax_t);
			master->tmp = ft_ulltoa_base(temp, 10);					
		}
		else
			master->tmp = ft_ulltoa_base(va_arg(*ap, intmax_t), 10);
	}
	else if (data->mod == 'z')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long) < 0)
		{
			data->neg = 1;
			size_t temp = -1 * va_arg(*ap, size_t);
			master->tmp = ft_ulltoa_base(temp, 10);					
		}
		else
			master->tmp = ft_ulltoa_base(va_arg(*ap, size_t), 10);
	}
	else if (data->mod == 't')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, ptrdiff_t) < 0)
		{
			data->neg = 1;
			ptrdiff_t temp = -1 * va_arg(*ap, ptrdiff_t);
			master->tmp = ft_ulltoa_base(temp, 10);					
		}
		else
			master->tmp = ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 10);
	}
	else
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long) < 0)
		{
			data->neg = 1;
			long temp = -1 * va_arg(*ap, long);
			master->tmp = ft_ulltoa_base(temp, 10);					
		}
		else
			master->tmp = ft_ulltoa_base(va_arg(*ap, long), 10);
	}
}

void	process_o(t_str *master, t_data *data, char *s, va_list *ap)
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

void	process_O(t_str *master, t_data *data, char *s, va_list *ap)
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

void	process_x(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->mod == 'i')
		master->tmp = ft_ulltoa_base((unsigned char)va_arg(*ap, int), 16);
	else if (data->mod == 'h')
		master->tmp = ft_ulltoa_base((unsigned short)va_arg(*ap, int), 16);
	else if (data->mod == 'm')
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned long long), 16);
	else if (data->mod == 'l')
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned long), 16);
	else if (data->mod == 'j')
		master->tmp = ft_ulltoa_base(va_arg(*ap, uintmax_t), 16);
	else if (data->mod == 'z')
		master->tmp = ft_ulltoa_base(va_arg(*ap, size_t), 16);
	else if (data->mod == 't')
		master->tmp = ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 16);
	else
		master->tmp = ft_ulltoa_base(va_arg(*ap, unsigned int), 16);
}

void	process_X(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->mod == 'i')
		master->tmp = ft_strupper(ft_ulltoa_base((unsigned char)va_arg(*ap, int), 16));
	else if (data->mod == 'h')
		master->tmp = ft_strupper(ft_ulltoa_base((unsigned short)va_arg(*ap, int), 16));
	else if (data->mod == 'm')
		master->tmp = ft_strupper(ft_ulltoa_base(va_arg(*ap, unsigned long long), 16));
	else if (data->mod == 'l')
		master->tmp = ft_strupper(ft_ulltoa_base(va_arg(*ap, unsigned long), 16));
	else if (data->mod == 'j')
		master->tmp = ft_strupper(ft_ulltoa_base(va_arg(*ap, uintmax_t), 16));
	else if (data->mod == 'z')
		master->tmp = ft_strupper(ft_ulltoa_base(va_arg(*ap, size_t), 16));
	else if (data->mod == 't')
		master->tmp = ft_strupper(ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 16));
	else
		master->tmp = ft_strupper(ft_ulltoa_base(va_arg(*ap, unsigned int), 16));
}

void	process_u(t_str *master, t_data *data, char *s, va_list *ap)
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

void	process_U(t_str *master, t_data *data, char *s, va_list *ap)
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

void	process_p(t_str *master, t_data *data, char *s, va_list *ap)
{
	long temp = va_arg(*ap, long);
	if (temp == 0)
		master->tmp = ft_strjoin(master->tmp, "0x0");
	else
		master->tmp = ft_strjoin("0x", ft_ulltoa_base(temp, 16));
}

void	process(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->spec == 'c')
		process_c(master, data, s, ap);
	if (data->spec == 'C')
		process_c(master, data, s, ap);
	if (data->spec == 's')
		process_s(master, data, s, ap);
	if (data->spec == 'S')
		process_S(master, data, s, ap);
	if (data->spec == 'd' || data->spec == 'i')
		process_d(master, data, s, ap);
	if (data->spec == 'D')
		process_D(master, data, s, ap);
	if (data->spec == 'o')
		process_o(master, data, s, ap);
	if (data->spec == 'O')
		process_O(master, data, s, ap);
	if (data->spec == 'x')
		process_x(master, data, s, ap);
	if (data->spec == 'X')
		process_X(master, data, s, ap);
	if (data->spec == 'u')
		process_u(master, data, s, ap);
	if (data->spec == 'U')
		process_U(master, data, s, ap);
	if (data->spec == 'p')
		process_p(master, data, s, ap);
}

int preprocess(t_str *master, char *s, va_list *ap)
{
	t_data data;

	data.neg = 0;
	data.prec = 0;
	ft_bzero(data.flag, sizeof(int) * 7);
	if (*s == '%')
	{
		master->ret = ft_strjoin(master->ret, "%");
		++master->len;
		return (1);
	}
	while (is_flag(*s))
	{
		if (*s == '-')
			data.flag[0] = 1;
		else if (*s == '+')
			data.flag[1] = 1;
		else if (*s == ' ')
			data.flag[2] = 1;
		else if (*s == '#')
			data.flag[3] = 1;
		else if (*s == '0')
			data.flag[4] = 1;
		++master->len;
		++s;		
	}
	if (ft_isdigit(*s))
	{
		data.flag[5] = ft_atoi(s);
		while (ft_isdigit(*s))
		{
			++master->len;
			++s;
		}
	}
	if (*s == '.')
	{
		++s;
		++master->len;
		data.prec = 1;
		data.flag[6] = ft_atoi(s);
		while (ft_isdigit(*s))
		{
			++master->len;
			++s;
		}
	}
	if (is_mod(*s))
	{
		if (is_spec(*(s + 1)) || (is_spec(*(s + 2)) && *(s + 1) == 'h') ||
		(is_spec(*(s + 2)) && *(s + 1) == 'l'))
		{
			if (*s == 'h' && *(s + 1) == 'h')
			{
				data.mod = 'i';
				master->len += 2;
				s += 2;
			}
			else if (*s == 'l' && *(s + 1) == 'l')
			{
				data.mod = 'm';
				master->len += 2;
				s += 2;
			}
			else
			{
				data.mod = *s;
				++master->len;
				++s;
			}
		}
		else
			return (0);
	}
	if (is_spec(*s))
	{
		data.spec = *s;
		++master->len;
		process(master, &data, s, ap);	
		postprocess(master, &data, s, ap);
	}
	return (1);
}

int ft_printf(const char * restrict format, ...)
{
	va_list ap;
	t_str master;

	master.ret = ft_strnew(0);
	va_start(ap, format);
	while (*format)
	{
		master.len = 0;
		while (format[master.len] && format[master.len] != '%')
			++master.len;
		if (master.len) //copies chars to ret
		{ //shit needs to be freed
			master.tmp = ft_strsub(format, 0, master.len);			
			master.ret = ft_strjoin(master.ret, master.tmp);
			free(master.tmp);
		}
		else
			if (!preprocess(&master, (char *)&format[++master.len], &ap))
				return (-1);
		format += master.len;
	}
	va_end(ap);
	// gotta count bytes while writing string, then print em. cuz null termintors and unprintables.
	ft_putstr(master.ret);
	return (ft_strlen(master.ret));
}

// int main()
// {	
// 	// all of the basics

// 	// printf(" printf length:    %d\n", printf("printf:    %%c: %c, %%s: %s, %%d: %d, %%o: %o, %%x: %x, %%X: %X, %%i: %i, %%u: %u, %%p, %p", 'c', "string", 101, 123456, 123456, 255255, -234, -505, "pointer"));
// 	// ft_printf(" ft_printf length: %d\n", ft_printf("ft_printf: %%c: %c, %%s: %s, %%d: %d, %%o: %o, %%x: %x, %%X: %X, %%i: %i, %%u: %u, %%p, %p", 0, "string", 101, 123456, 123456, 255255, -234, -505, "pointer"));

// 	// printf("f2_printf length: %d\n", printf("f2_pritf: %%c: %c\n", 'c'));
// 	// ft_printf("ft_printf length: %d\n", ft_printf("ft_pritf:  %c\n", 'r'));

// 	// // d signed char is fucked

// 	// printf("pf: %%d: %d, %%hhd: %hhd, %%hd: %hd, %%lld: %lld, %%ld: %ld, %%jd: %jd, %%zd: %zd, %%td: %td\n", INT_MIN, (signed char)SCHAR_MIN, (short)SHRT_MIN, (long long)LLONG_MIN, (long)LONG_MIN, (intmax_t)INT_MIN, (size_t)INT_MIN, (ptrdiff_t)-12345678910);
// 	// ft_printf("ft: %%d: %d, %%hhd: %hhd, %%hd: %hd, %%lld: %lld, %%ld: %ld, %%jd: %jd, %%zd: %zd, %%td: %td\n", INT_MIN, (signed char)SCHAR_MIN, (short)SHRT_MIN, (long long)LLONG_MIN, (long)LONG_MIN, (intmax_t)INT_MIN, (size_t)INT_MIN, (ptrdiff_t)-12345678910);

// 	// // D

// 	// printf("pf: %%D: %D, %%hhD: %hhD, %%hD: %hd, %%llD: %llD, %%lD: %lD, %%jD: %jD, %%zD: %zD, %%tD: %tD\n", LONG_MIN, (signed char)SCHAR_MIN, (short)SHRT_MIN, (long long)LLONG_MIN, (long)LONG_MIN, (intmax_t)INT_MIN, (size_t)INT_MIN, (ptrdiff_t)-12345678910);
// 	// ft_printf("ft: %%D: %D, %%hhD: %hhD, %%hD: %hd, %%llD: %llD, %%lD: %lD, %%jD: %jD, %%zD: %zD, %%tD: %tD\n", LONG_MIN, (signed char)SCHAR_MIN, (short)SHRT_MIN, (long long)LLONG_MIN, (long)LONG_MIN, (intmax_t)INT_MIN, (size_t)INT_MIN, (ptrdiff_t)-12345678910);

// 	// o

// 	printf("pf: %%o: %o, %%hho: %hho, %%ho: %ho, %%llo: %llo, %%lo: %lo, %%jo: %jo, %%zo: %zo, %%to: %to\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, (unsigned long long)ULLONG_MAX, (unsigned long)ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
// 	ft_printf("ft: %%o: %o, %%hho: %hho, %%ho: %ho, %%llo: %llo, %%lo: %lo, %%jo: %jo, %%zo: %zo, %%to: %to\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, (unsigned long long)ULLONG_MAX, (unsigned long)ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	
// 	printf("pf: %%#o: %#o, %%#hho: %#hho, %%#ho: %ho, %%#llo: %#llo, %%#lo: %#lo, %%#jo: %#jo, %%#zo: %#zo, %%#to: %#to\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
// 	ft_printf("ft: %%#o: %#o, %%#hho: %#hho, %%#ho: %ho, %%#llo: %#llo, %%#lo: %#lo, %%#jo: %#jo, %%#zo: %#zo, %%#to: %#to\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);

// 	printf("pf: %%#o: %#o\n", 0);
// 	ft_printf("ft: %%#o: %#o\n", 0);


// 	// // O

// 	// printf("pf: %%O: %O, %%hhO: %hhO, %%hO: %hO, %%llO: %llO, %%lO: %lO, %%jO: %jO, %%zO: %zO, %%tO: %tO\n", (unsigned int)INT_MIN, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
// 	// ft_printf("ft: %%O: %O, %%hhO: %hhO, %%hO: %hO, %%llO: %llO, %%lO: %lO, %%jO: %jO, %%zO: %zO, %%tO: %tO\n", (unsigned int)INT_MIN, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	
// 	// printf("pf: %%#O: %#O, %%#hhO: %#hhO, %%#hO: %#hO, %%#llO: %#llO, %%#lO: %#lO, %%#jO: %#jO, %%#zO: %#zO, %%#tO: %#tO\n", (unsigned int)INT_MIN, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
// 	// ft_printf("ft: %%#O: %#O, %%#hhO: %#hhO, %%#hO: %#hO, %%#llO: %#llO, %%#lO: %#lO, %%#jO: %#jO, %%#zO: %#zO, %%#tO: %#tO\n", (unsigned int)INT_MIN, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	
// 	// // x ullong
	
// 	// printf("pf: %%x: %x, %%hhx: %hhx, %%hx: %hx, %%llx: %llx, %%lx: %lx, %%jx: %jx, %%zx: %zx, %%tx: %tx\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
// 	// ft_printf("ft: %%x: %x, %%hhx: %hhx, %%hx: %hx, %%llx: %llx, %%lx: %lx, %%jx: %jx, %%zx: %zx, %%tx: %tx\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	
// 	// printf("ft: %%#x: %#x, %%#hhx: %#hhx, %%#hx: %#hx, %%#llx: %#llx, %%#lx: %#lx, %%#jx: %#jx, %%#zx: %#zx, %%#tx: %#tx\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
// 	// ft_printf("ft: %%#x: %#x, %%#hhx: %#hhx, %%#hx: %#hx, %%#llx: %#llx, %%#lx: %#lx, %%#jx: %#jx, %%#zx: %#zx, %%#tx: %#tx\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	
// 	// // X

// 	// printf("pf: %%X: %X, %%hhX: %hhX, %%hX: %hX, %%llX: %llX, %%lX: %lX, %%jX: %jX, %%zX: %zX, %%tX: %tX\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
// 	// ft_printf("pf: %%X: %X, %%hhX: %hhX, %%hX: %hX, %%llX: %llX, %%lX: %lX, %%jX: %jX, %%zX: %zX, %%tX: %tX\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	
// 	// printf("pf: %%#X: %#X, %%#hhX: %#hhX, %%#hX: %#hX, %%#llX: %#llX, %%#lX: %#lX, %%#jX: %#jX, %%#zX: %#zX, %%#tX: %#tX\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
// 	// ft_printf("ft: %%#X: %#X, %%#hhX: %#hhX, %%#hX: %#hX, %%#llX: %#llX, %%#lX: %#lX, %%#jX: %#jX, %%#zX: %#zX, %%#tX: %#tX\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);

// 	// // u ullong

// 	// printf("pf: %%u: %u, %%hhu: %hhu, %%hu: %hu, %%llu: %llu, %%lu: %lu, %%ju: %ju, %%zu: %zu, %%tu: %tu\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
// 	// ft_printf("pf: %%u: %u, %%hhu: %hhu, %%hu: %hu, %%llu: %llu, %%lu: %lu, %%ju: %ju, %%zu: %zu, %%tu: %tu\n", UINT_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);

// 	// // U stuff

// 	// printf("pf: %%U: %U, %%hhU: %hhU, %%hU: %hU, %%llU: %llU, %%lU: %lU, %%jU: %jU, %%zU: %zU, %%tU: %tU\n", (unsigned int)ULONG_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
// 	// ft_printf("ft: %%U: %U, %%hhU: %hhU, %%hU: %hU, %%llU: %llU, %%lU: %lU, %%jU: %jU, %%zU: %zU, %%tU: %tU\n", (unsigned int)ULONG_MAX, (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, ULLONG_MAX, ULONG_MAX, (uintmax_t)UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);

// 	// // p

// 	// printf("pf: %%p: %p, %%p: %p, %%p: %p, %%p: %p, %%p: %p, %%p: %p\n", 'c', "string", 10101, -10, 00, -2147483648);
// 	// ft_printf("ft: %%p: %p, %%p: %p, %%p: %p, %%p: %p, %%p: %p, %%p: %p\n", 'c', "string", 10101, -10, 00, -2147483648);


// 	// printf("|%5.s|\n", "Hello world!");
// 	// printf("|%6.1s|\n", "Hello world!");
// 	// printf("|%.2s|\n", "Hello world!");
// 	// printf("|%.3s|\n", "Hello world!");
// 	// printf("|%.4s|\n", "Hello world!");
// 	// printf("|%.5s|\n", "Hello world!");
// 	// printf("|%.6s|\n", "Hello world!");
// 	// printf("|%.7s|\n", "Hello world!");
// 	// printf("|%.8s|\n", "Hello world!");
// 	// printf("|%.9s|\n", "Hello world!");
// 	// printf("|%6.10s|\n", "Hello world!");
// 	// printf("|%-6.11s|\n", "Hello world!");
// 	// printf("|%6.12s|\n", "Hello world!");

// 	// ft_printf("|%5.s|\n", "Hello world!");
// 	// ft_printf("|%6.1s|\n", "Hello world!");
// 	// ft_printf("|%.2s|\n", "Hello world!");
// 	// ft_printf("|%.3s|\n", "Hello world!");
// 	// ft_printf("|%.4s|\n", "Hello world!");
// 	// ft_printf("|%.5s|\n", "Hello world!");
// 	// ft_printf("|%.6s|\n", "Hello world!");
// 	// ft_printf("|%.7s|\n", "Hello world!");
// 	// ft_printf("|%.8s|\n", "Hello world!");
// 	// ft_printf("|%.9s|\n", "Hello world!");
// 	// ft_printf("|%6.10s|\n", "Hello world!");
// 	// ft_printf("|%-6.11s|\n", "Hello world!");
// 	// ft_printf("|%6.12s|\n", "Hello world!");
	
// 	// printf("pf01: |%-010.0d|\n", -69);
// 	// printf("pf02: |%-010.1d|\n", 69);
// 	// printf("pf03: |%010.2d|\n", -69);
// 	// printf("pf04: |%+010.3d|\n", 69);
// 	// printf("pf05: |%-+010.4d|\n", 69);
// 	// printf("pf06: |%10.5d|\n", -69);
// 	// printf("pf07: |%10.6d|\n", -69);
// 	// printf("pf08: |%10.7d|\n", -69);
// 	// printf("pf09: |%10.8d|\n", -69);
// 	// printf("pf10: |%10.9d|\n", -69);
// 	// printf("pf11: |%10.10d|\n", -69);
// 	// printf("pf12: |%10.11d|\n", -69);
// 	// printf("pf13: |%10.12d|\n", -69);
// 	// printf("pf14: |% 10.12d|\n", -69);
// 	// printf("pf15: |%+10.12d|\n", -69);
// 	// printf("pf16: |%-10.12d|\n", -69);
// 	// printf("pf17: |%-+20.12d|\n", -69);
// 	// printf("pf18: |%+0.5d|\n", 69);
// 	// printf("pf19: |%0.10d|\n", -69);
// 	// printf("pf20: |%+0.15d|\n", 69);
// 	// printf("pf21: |%05d|\n", -69);
// 	// printf("pf22: |%010d|\n", -69);
// 	// printf("pf23: |%015d|\n", -69);
// 	// printf("pf21: |%+05d|\n", 69);
// 	// printf("pf22: |%+010d|\n", 69);
// 	// printf("pf23: |%+015d|\n", 69);
// 	// printf("ft24: |%#+0.5o|\n", 6969);
// 	// printf("ft25: |%#0.10o|\n", -6969);
// 	// printf("ft26: |%#+0.15o|\n", 6969);
// 	// printf("ft27: |%#+05o|\n", -6969);
// 	// printf("ft28: |%#+010o|\n", -6969);
// 	// printf("ft29: |%#+015o|\n", -6969);
	
// 	// ft_printf("ft01: |%-010.0d|\n", -69);
// 	// ft_printf("ft02: |%-010.1d|\n", 69);
// 	// ft_printf("ft03: |%010.2d|\n", -69);
// 	// ft_printf("ft04: |%+010.3d|\n", 69);
// 	// ft_printf("ft05: |%-+010.4d|\n", 69);
// 	// ft_printf("ft06: |%10.5d|\n", -69);
// 	// ft_printf("ft07: |%10.6d|\n", -69);
// 	// ft_printf("ft08: |%10.7d|\n", -69);
// 	// ft_printf("ft09: |%10.8d|\n", -69);
// 	// ft_printf("ft10: |%10.9d|\n", -69);
// 	// ft_printf("ft11: |%10.10d|\n", -69);
// 	// ft_printf("ft12: |%10.11d|\n", -69);
// 	// ft_printf("ft13: |%10.12d|\n", -69);
// 	// ft_printf("ft14: |% 10.12d|\n", -69);
// 	// ft_printf("ft15: |%+10.12d|\n", -69);
// 	// ft_printf("ft16: |%-10.12d|\n", -69);
// 	// ft_printf("ft17: |%-+20.12d|\n", -69);
// 	// ft_printf("ft18: |%+0.5d|\n", 69);
// 	// ft_printf("ft19: |%0.10d|\n", -69);
// 	// ft_printf("ft20: |%+0.15d|\n", 69);
// 	// ft_printf("ft21: |%05d|\n", -69);
// 	// ft_printf("ft22: |%010d|\n", -69);
// 	// ft_printf("ft23: |%015d|\n", -69);
// 	// ft_printf("ft21: |%+05d|\n", 69);
// 	// ft_printf("ft22: |%+010d|\n", 69);
// 	// ft_printf("ft23: |%+015d|\n", 69);
// 	// ft_printf("ft24: |%#+0.5o|\n", 6969);
// 	// ft_printf("ft25: |%#0.10o|\n", -6969);
// 	// ft_printf("ft26: |%#+0.15o|\n", 6969);
// 	// ft_printf("ft27: |%#+05o|\n", -6969);
// 	// ft_printf("ft28: |%#+010o|\n", -6969);
// 	// ft_printf("ft29: |%#+015o|\n", -6969);

// 	// printf("%d\n", ft_printf("ft: |%c%c%c%c|\n", 0,1,2,3));
// 	// printf("%d\n", printf("pf: |%c%c%c%c|\n", 0,1,2,3));
// }

