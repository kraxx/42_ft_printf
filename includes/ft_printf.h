/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 19:57:45 by jchow             #+#    #+#             */
/*   Updated: 2017/06/22 19:57:46 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF
# define FT_PRINTF

# include "libft.h"
# include <stdarg.h>
# include <stddef.h>

typedef struct s_str
{
	char *tmp;
	char *tmp2;
	char *ret;
	int len;
}				t_str;

typedef struct s_data
{
	int neg;
	int flag[7];
	int prec;
	char mod;
	char spec;
}				t_data;

/*
** Flags:
**
** 0) '-'
** 1) '+'
** 2) ' '
** 3) '#'
** 4) '0'
** 5) 'width'
** 6) 'precision'
*/

int ft_printf(const char *format, ...);

void	ft_putstr_pf(char *s);
void	ft_freejoin(char **s1, char **s2);
void	ft_freeappend(char **s1, char **s2, char *c, int left);
int		is_flag(char c);
int		is_mod(char c);
int		is_spec(char c);
void	postprocess_prefix(t_str *master, t_data *data);
void	postprocess_num_space(t_str *master, t_data *data, int i, int j);
void	postprocess_num_zero(t_str *master, t_data *data, int i, int j);
void	postprocess_num_zero_prec(t_str *master, t_data *data, int i, int j);
void	postprocess_width(t_str *master, t_data *data, int i, int j);
void	postprocess_num(t_str *master, t_data *data);
void	postprocess_string(t_str *master, t_data *data);
void	postprocess(t_str *master, t_data *data);
void	process_c(t_str *master, va_list *ap);
void	process_s(t_str *master, va_list *ap);
void	process_d(t_str *master, t_data *data, va_list *ap);
void	process_hhd(t_str *master, t_data *data, va_list *ap);
void	process_hd(t_str *master, t_data *data, va_list *ap);
void	process_lld(t_str *master, t_data *data, va_list *ap);
void	process_ld(t_str *master, t_data *data, va_list *ap);
void	process_jd(t_str *master, t_data *data, va_list *ap);
void	process_zd(t_str *master, t_data *data, va_list *ap);
void	process_td(t_str *master, t_data *data, va_list *ap);
void	process_d_reg(t_str *master, t_data *data, va_list *ap);
void	process_big_d(t_str *master, t_data *data, va_list *ap);
void	process_big_hhd(t_str *master, t_data *data, va_list *ap);
void	process_big_hd(t_str *master, t_data *data, va_list *ap);
void	process_big_lld(t_str *master, t_data *data, va_list *ap);
void	process_big_ld(t_str *master, t_data *data, va_list *ap);
void	process_big_jd(t_str *master, t_data *data, va_list *ap);
void	process_big_zd(t_str *master, t_data *data, va_list *ap);
void	process_big_td(t_str *master, t_data *data, va_list *ap);
void	process_big_d_reg(t_str *master, t_data *data, va_list *ap);
void	process_o(t_str *master, t_data *data, va_list *ap);
void	process_big_o(t_str *master, t_data *data, va_list *ap);
void	process_x(t_str *master, t_data *data, va_list *ap);
void	process_big_x(t_str *master, t_data *data, va_list *ap);
void	process_u(t_str *master, t_data *data, va_list *ap);
void	process_big_u(t_str *master, t_data *data, va_list *ap);
void	process_p(t_str *master, va_list *ap);
void	process(t_str *master, t_data *data, va_list *ap);
int		preprocess_flags(t_str *master, t_data *data, char *s);
int		preprocess_size(t_str *master, t_data *data, char *s);
int		preprocess_mod(t_str *master, t_data *data, char *s);
int		preprocess(t_str *master, char *s, va_list *ap);

#endif