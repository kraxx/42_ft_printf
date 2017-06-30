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

int postprocess(t_str *master, t_data *data, char *s, va_list *ap)
{
	
}

int process_C(t_str *master, t_data *data, char *s, va_list *ap)
{
	// wide chars. yep.
	return (1);
}

int	process_c(t_str *master, t_data *data, char *s, va_list *ap)
{
	// if (data->mod == 'l')
	// 	// wint_t, maybe it's different
	// 	return (process_C(master, data, s, ap));
	// else
	if (*s == 0)
	{ //this is fucked, gotta fix it
		char *temp = ft_strnew(1);
		temp[0] = '\0';
		master->ret = ft_strjoin(master->ret, 0);
	}
	else
	{
		char *temp = ft_strnew(1);
		temp[0] = (char)va_arg(*ap, t_ui);
		master->ret = ft_strjoin(master->ret, temp);
		free(temp);
	}
	return (1);
}

int process_s(t_str *master, t_data *data, char *s, va_list *ap)
{
	// if (data->mod == 'l')
	// {
		
	// }
	// else
		master->ret = ft_strjoin(master->ret, va_arg(*ap, char *));
	return (1);
}

int process_S(t_str *master, t_data *data, char *s, va_list *ap)
{
	// wide chars. yep.
	return (1);
}

int process_d(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->mod == 'i')
		master->ret = ft_strjoin(master->ret, ft_itoa((signed char)va_arg(*ap, int)));
	else if (data->mod == 'h')
		master->ret = ft_strjoin(master->ret, ft_itoa((short)va_arg(*ap, int)));
	else if (data->mod == 'm')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long long) < 0)
		{
			long long temp = -1 * va_arg(*ap, long long);
			master->ret = ft_strjoin(master->ret, ft_strjoin("-", ft_ulltoa_base(temp, 10)));					
		}
		else
			master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, long long), 10));
	}
	else if (data->mod == 'l')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long) < 0)
		{
			long temp = -1 * va_arg(*ap, long);
			master->ret = ft_strjoin(master->ret, ft_strjoin("-", ft_ulltoa_base(temp, 10)));					
		}
		else
			master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, long), 10));
	}
	else if (data->mod == 'j')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, intmax_t) < 0)
		{
			intmax_t temp = -1 * va_arg(*ap, intmax_t);
			master->ret = ft_strjoin(master->ret, ft_strjoin("-", ft_ulltoa_base(temp, 10)));					
		}
		else
			master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, intmax_t), 10));
	}
	else if (data->mod == 'z')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long) < 0)
		{
			size_t temp = -1 * va_arg(*ap, size_t);
			master->ret = ft_strjoin(master->ret, ft_strjoin("-", ft_ulltoa_base(temp, 10)));					
		}
		else
			master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, size_t), 10));
	}
	else if (data->mod == 't')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, ptrdiff_t) < 0)
		{
			ptrdiff_t temp = -1 * va_arg(*ap, ptrdiff_t);
			master->ret = ft_strjoin(master->ret, ft_strjoin("-", ft_ulltoa_base(temp, 10)));					
		}
		else
			master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 10));
	}
	else
		master->ret = ft_strjoin(master->ret, ft_itoa(va_arg(*ap, int)));
	return (1);
}

int process_D(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->mod == 'i')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long) < 0)
		{
			signed char temp = -1 * va_arg(*ap, long);
			master->ret = ft_strjoin(master->ret, ft_strjoin("-", ft_ulltoa_base(temp, 10)));					
		}
		else
			master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, long), 10));
	}
	else if (data->mod == 'h')
		master->ret = ft_strjoin(master->ret, ft_itoa((short)va_arg(*ap, long)));
	else if (data->mod == 'm')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long long) < 0)
		{
			long long temp = -1 * va_arg(*ap, long long);
			master->ret = ft_strjoin(master->ret, ft_strjoin("-", ft_ulltoa_base(temp, 10)));					
		}
		else
			master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, long long), 10));
	}
	else if (data->mod == 'l')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long) < 0)
		{
			long temp = -1 * va_arg(*ap, long);
			master->ret = ft_strjoin(master->ret, ft_strjoin("-", ft_ulltoa_base(temp, 10)));					
		}
		else
			master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, long), 10));
	}
	else if (data->mod == 'j')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, intmax_t) < 0)
		{
			intmax_t temp = -1 * va_arg(*ap, intmax_t);
			master->ret = ft_strjoin(master->ret, ft_strjoin("-", ft_ulltoa_base(temp, 10)));					
		}
		else
			master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, intmax_t), 10));
	}
	else if (data->mod == 'z')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long) < 0)
		{
			size_t temp = -1 * va_arg(*ap, size_t);
			master->ret = ft_strjoin(master->ret, ft_strjoin("-", ft_ulltoa_base(temp, 10)));					
		}
		else
			master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, size_t), 10));
	}
	else if (data->mod == 't')
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, ptrdiff_t) < 0)
		{
			ptrdiff_t temp = -1 * va_arg(*ap, ptrdiff_t);
			master->ret = ft_strjoin(master->ret, ft_strjoin("-", ft_ulltoa_base(temp, 10)));					
		}
		else
			master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 10));
	}
	else
	{
		va_list cop;
		va_copy(cop, *ap);
		if (va_arg(cop, long) < 0)
		{
			long temp = -1 * va_arg(*ap, long);
			master->ret = ft_strjoin(master->ret, ft_strjoin("-", ft_ulltoa_base(temp, 10)));					
		}
		else
			master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, long), 10));
	}
	return (1);
}

int process_o(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->mod == 'i')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base((unsigned char)va_arg(*ap, int), 8));
	else if (data->mod == 'h')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base((unsigned short)va_arg(*ap, int), 8));
	else if (data->mod == 'm')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, unsigned long long), 8));
	else if (data->mod == 'l')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, unsigned long), 8));
	else if (data->mod == 'j')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, uintmax_t), 8));
	else if (data->mod == 'z')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, size_t), 8));
	else if (data->mod == 't')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 8));
	else
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, unsigned int), 8));
	return (1);
}

int process_O(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->mod == 'i')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, long long), 8));
	else if (data->mod == 'h')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, long long), 8));
	else if (data->mod == 'm')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, unsigned long long), 8));
	else if (data->mod == 'l')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, unsigned long), 8));
	else if (data->mod == 'j')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, uintmax_t), 8));
	else if (data->mod == 'z')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, size_t), 8));
	else if (data->mod == 't')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 8));
	else
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, unsigned long), 8));
	return (1);
}

int process_x(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->mod == 'i')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base((unsigned char)va_arg(*ap, int), 16));
	else if (data->mod == 'h')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base((unsigned short)va_arg(*ap, int), 16));
	else if (data->mod == 'm')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, unsigned long long), 16));
	else if (data->mod == 'l')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, unsigned long), 16));
	else if (data->mod == 'j')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, uintmax_t), 16));
	else if (data->mod == 'z')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, size_t), 16));
	else if (data->mod == 't')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 16));
	else
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, unsigned int), 16));
	return (1);
}

int process_X(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->mod == 'i')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base((unsigned char)va_arg(*ap, int), 16)));
	else if (data->mod == 'h')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base((unsigned short)va_arg(*ap, int), 16)));
	else if (data->mod == 'm')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, unsigned long long), 16)));
	else if (data->mod == 'l')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, unsigned long), 16)));
	else if (data->mod == 'j')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, uintmax_t), 16)));
	else if (data->mod == 'z')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, size_t), 16)));
	else if (data->mod == 't')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 16)));
	else
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, unsigned int), 16)));
	return (1);
}

int process_u(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->mod == 'i')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base((unsigned char)va_arg(*ap, int), 10));
	else if (data->mod == 'h')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base((unsigned short)va_arg(*ap, int), 10));
	else if (data->mod == 'm')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, unsigned long long), 10));
	else if (data->mod == 'l')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, unsigned long), 10));
	else if (data->mod == 'j')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, uintmax_t), 10));
	else if (data->mod == 'z')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, size_t), 10));
	else if (data->mod == 't')
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 10));
	else
		master->ret = ft_strjoin(master->ret, ft_ulltoa_base(va_arg(*ap, unsigned int), 10));
	return (1);
}

int process_U(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->mod == 'i')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, long long), 10)));
	else if (data->mod == 'h')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, long long), 10)));
	else if (data->mod == 'm')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, unsigned long long), 10)));
	else if (data->mod == 'l')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, unsigned long), 10)));
	else if (data->mod == 'j')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, uintmax_t), 10)));
	else if (data->mod == 'z')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, size_t), 10)));
	else if (data->mod == 't')
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, ptrdiff_t), 10)));
	else
		master->ret = ft_strjoin(master->ret, ft_strupper(ft_ulltoa_base(va_arg(*ap, unsigned long long), 10)));
	return (1);
}

int process_p(t_str *master, t_data *data, char *s, va_list *ap)
{
	long temp = va_arg(*ap, long);
	if (temp == 0)
		master->ret = ft_strjoin(master->ret, "0x0");
	else
		master->ret = ft_strjoin(master->ret, ft_strjoin("0x", ft_ulltoa_base(temp, 16)));
	return (1);
}

int process(t_str *master, t_data *data, char *s, va_list *ap)
{
	if (data->spec == 'c')
		return (process_c(master, data, s, ap));
	if (data->spec == 'C')
		return (process_C(master, data, s, ap));
	if (data->spec == 's')
		return (process_s(master, data, s, ap));
	if (data->spec == 'S')
		return (process_S(master, data, s, ap));
	if (data->spec == 'd' || data->spec == 'i')
		return (process_d(master, data, s, ap));
	if (data->spec == 'D')
		return (process_D(master, data, s, ap));
	if (data->spec == 'o')
		return (process_o(master, data, s, ap));
	if (data->spec == 'O')
		return (process_O(master, data, s, ap));
	if (data->spec == 'x')
		return (process_x(master, data, s, ap));
	if (data->spec == 'X')
		return (process_X(master, data, s, ap));
	if (data->spec == 'u')
		return (process_u(master, data, s, ap));
	if (data->spec == 'U')
		return (process_U(master, data, s, ap));
	if (data->spec == 'p')
		return (process_p(master, data, s, ap));
	return (1);
}

int preprocess(t_str *master, char *s, va_list *ap)
{
	t_data data;

	data.neg = 0;
	ft_bzero(data.flag, 5);
	if (*s == '%')
	{
		master->ret = ft_strncat(master->ret, s, 1);
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
		data.width = ft_atoi(s);
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
		data.prec = ft_atoi(s);
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
		{
			master->err = 1;
			return (0);
		}
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
	master.err = 0;
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
		{
			if (!preprocess(&master, (char *)&format[++master.len], &ap))
				return (-1);
		}
		format += master.len;
	}
	va_end(ap);
	// gotta count bytes while writing string, then print em. cuz null termintors and unprintables.
	ft_putstr(master.ret);
	return (ft_strlen(master.ret));
}

int main()
{
	// printf("%d\n", ft_printf("ft: |%c%c%c%c|\n", 0,1,2,3));
	// printf("%d\n", printf("pf: |%c%c%c%c|\n", 0,1,2,3));

	
	// all of the basics

	// printf(" printf length: %d\n", printf("printf:    %%c: %c, %%s: %s, %%d: %d, %%o: %o, %%x: %x, %%X: %X, %%i: %i, %%u: %u, %%p, %p", 'c', "string", 101, 123456, 123456, 255255, -234, -505, "pointer"));
	// ft_printf(" ft_printf length: %d\n", ft_printf("ft_printf: %%c: %c, %%s: %s, %%d: %d, %%o: %o, %%x: %x, %%X: %X, %%i: %i, %%u: %u, %%p, %p", 'c', "string", 101, 123456, 123456, 255255, -234, -505, "pointer"));

	// d

	printf("%%d: %d, %%hhd: %hhd, %%hd: %hd, %%lld: %lld, %%ld: %ld, %%jd: %jd, %%zd: %zd, %%td: %td\n", INT_MIN, SCHAR_MIN, SHRT_MIN, LLONG_MIN, LONG_MIN, (intmax_t)INT_MIN, (size_t)INT_MIN, (ptrdiff_t)-12345678910);
	ft_printf("%%d: %d, %%hhd: %hhd, %%hd: %hd, %%lld: %lld, %%ld: %ld, %%jd: %jd, %%zd: %zd, %%td: %td\n", INT_MIN, SCHAR_MIN, SHRT_MIN, LLONG_MIN, LONG_MIN, (intmax_t)INT_MIN, (size_t)INT_MIN, (ptrdiff_t)-12345678910);

	// D cant handle minint

	// printf("%%D: %D, %%hhD: %hhD, %%hD: %hd, %%llD: %llD, %%lD: %lD, %%jD: %jD, %%zD: %zD, %%tD: %tD\n", LONG_MIN, SCHAR_MIN, (short)-12345678910, LLONG_MIN, LONG_MIN, (intmax_t)INT_MIN, (size_t)INT_MIN, (ptrdiff_t)-12345678910);
	// ft_printf("%%D: %D, %%hhD: %hhD, %%hD: %hd, %%llD: %llD, %%lD: %lD, %%jD: %jD, %%zD: %zD, %%tD: %tD\n", LONG_MIN, SCHAR_MIN, (short)-12345678910, LLONG_MIN, LONG_MIN, (intmax_t)INT_MIN, (size_t)INT_MIN, (ptrdiff_t)-12345678910);

	// o

	printf("%%o: %o, %%hho: %hho, %%ho: %ho, %%llo: %llo, %%lo: %lo, %%jo: %jo, %%zo: %zo, %%to: %to\n", UINT_MAX, UCHAR_MAX, USHRT_MAX, ULLONG_MAX, ULONG_MAX, UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	ft_printf("%%o: %o, %%hho: %hho, %%ho: %ho, %%llo: %llo, %%lo: %lo, %%jo: %jo, %%zo: %zo, %%to: %to\n", UINT_MAX, UCHAR_MAX, USHRT_MAX, ULLONG_MAX, ULONG_MAX, UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);

	// O cant handle minint

	printf("%%O: %O, %%hhO: %hhO, %%hO: %hO, %%llO: %llO, %%lO: %lO, %%jO: %jO, %%zO: %zO, %%tO: %tO\n", -2147483648, UCHAR_MAX, USHRT_MAX, ULLONG_MAX, ULONG_MAX, UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	ft_printf("%%O: %O, %%hhO: %hhO, %%hO: %hO, %%llO: %llO, %%lO: %lO, %%jO: %jO, %%zO: %zO, %%tO: %tO\n", -214748364, UCHAR_MAX, USHRT_MAX, ULLONG_MAX, ULONG_MAX, UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	
	// x
	
	printf("%%x: %x, %%hhx: %hhx, %%hx: %hx, %%llx: %llx, %%lx: %lx, %%jx: %jx, %%zx: %zx, %%tx: %tx\n", UINT_MAX, UCHAR_MAX, USHRT_MAX, ULLONG_MAX, ULONG_MAX, UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	ft_printf("%%x: %x, %%hhx: %hhx, %%hx: %hx, %%llx: %llx, %%lx: %lx, %%jx: %jx, %%zx: %zx, %%tx: %tx\n", UINT_MAX, UCHAR_MAX, USHRT_MAX, ULLONG_MAX, ULONG_MAX, UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	
	// X

	printf("%%X: %X, %%hhX: %hhX, %%hX: %hX, %%llX: %llX, %%lX: %lX, %%jX: %jX, %%zX: %zX, %%tX: %tX\n", UINT_MAX, UCHAR_MAX, USHRT_MAX, ULLONG_MAX, ULONG_MAX, UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	ft_printf("%%X: %X, %%hhX: %hhX, %%hX: %hX, %%llX: %llX, %%lX: %lX, %%jX: %jX, %%zX: %zX, %%tX: %tX\n", UINT_MAX, UCHAR_MAX, USHRT_MAX, ULLONG_MAX, ULONG_MAX, UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);

	// u

	printf("%%u: %u, %%hhu: %hhu, %%hu: %hu, %%llu: %llu, %%lu: %lu, %%ju: %ju, %%zu: %zu, %%tu: %tu\n", UINT_MAX, UCHAR_MAX, USHRT_MAX, ULLONG_MAX, ULONG_MAX, UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	ft_printf("%%u: %u, %%hhu: %hhu, %%hu: %hu, %%llu: %llu, %%lu: %lu, %%ju: %ju, %%zu: %zu, %%tu: %tu\n", UINT_MAX, UCHAR_MAX, USHRT_MAX, ULLONG_MAX, ULONG_MAX, UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);

	// U 

	printf("%%U: %U, %%hhU: %hhU, %%hU: %hU, %%llU: %llU, %%lU: %lU, %%jU: %jU, %%zU: %zU, %%tU: %tU\n", ULONG_MAX, UCHAR_MAX, USHRT_MAX, ULLONG_MAX, ULONG_MAX, UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);
	ft_printf("%%U: %U, %%hhU: %hhU, %%hU: %hU, %%llU: %llU, %%lU: %lU, %%jU: %jU, %%zU: %zU, %%tU: %tU\n", ULONG_MAX, UCHAR_MAX, USHRT_MAX, ULLONG_MAX, ULONG_MAX, UINT_MAX, (size_t)UINT_MAX, (ptrdiff_t)-12345678910);

	// p

	// printf("%%p: %p, %%p: %p, %%p: %p, %%p: %p, %%p: %p, %%p: %p\n", 'c', "string", 10101, -10, 00, -2147483648);
	// ft_printf("%%p: %p, %%p: %p, %%p: %p, %%p: %p, %%p: %p, %%p: %p\n", 'c', "string", 10101, -10, 00, -2147483648);
}
