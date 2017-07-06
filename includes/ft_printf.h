/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 19:57:45 by jchow             #+#    #+#             */
/*   Updated: 2017/07/05 17:59:51 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdarg.h>
# include <stddef.h>

typedef unsigned char		t_uc;
typedef unsigned int		t_ui;
typedef unsigned short		t_ush;
typedef unsigned long long	t_ull;

typedef struct				s_str
{
	char	*tmp;
	char	*tmp2;
	char	*ret;
	int		len;
}							t_str;

typedef struct				s_data
{
	int		neg;
	int		flag[7];
	int		prec;
	char	mod;
	char	spec;
}							t_data;

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

int							ft_printf(const char *format, ...);

void						ft_putstr_pf(char *s);
void						ft_freejoin(char **s1, char **s2);
void						ft_freeappend(char **s1, char **s2,
		char *c, int left);
int							is_flag(char c);
int							is_mod(char c);
int							is_spec(char c);
void						postprocess_prefix(t_str *m, t_data *d);
void						postprocess_num_space(t_str *m, t_data *d,
		int i, int j);
void						postprocess_num_zero(t_str *m, t_data *d,
		int i, int j);
void						postprocess_num_zero_prec(t_str *m, t_data *d,
		int i, int j);
void						postprocess_width(t_str *m, t_data *d,
		int i, int j);
void						postprocess_num(t_str *m, t_data *d);
void						postprocess_string(t_str *m, t_data *d);
void						postprocess(t_str *m, t_data *d);
void						process_c(t_str *m, va_list *ap);
void						process_s(t_str *m, va_list *ap);
void						process_d(t_str *m, t_data *d, va_list *ap);
void						process_hhd(t_str *m, t_data *d, va_list *ap);
void						process_hd(t_str *m, t_data *d, va_list *ap);
void						process_lld(t_str *m, t_data *d, va_list *ap);
void						process_ld(t_str *m, t_data *d, va_list *ap);
void						process_jd(t_str *m, t_data *d, va_list *ap);
void						process_zd(t_str *m, t_data *d, va_list *ap);
void						process_td(t_str *m, t_data *d, va_list *ap);
void						process_d_reg(t_str *m, t_data *d, va_list *ap);
void						process_big_d(t_str *m, t_data *d, va_list *ap);
void						process_big_hhd(t_str *m, t_data *d, va_list *ap);
void						process_big_hd(t_str *m, t_data *d, va_list *ap);
void						process_big_lld(t_str *m, t_data *d, va_list *ap);
void						process_big_ld(t_str *m, t_data *d, va_list *ap);
void						process_big_jd(t_str *m, t_data *d, va_list *ap);
void						process_big_zd(t_str *m, t_data *d, va_list *ap);
void						process_big_td(t_str *m, t_data *d, va_list *ap);
void						process_big_d_reg(t_str *m, t_data *d, va_list *ap);
void						process_o(t_str *m, t_data *d, va_list *ap);
void						process_big_o(t_str *m, t_data *d, va_list *ap);
void						process_x(t_str *m, t_data *d, va_list *ap);
void						process_big_x(t_str *m, t_data *d, va_list *ap);
void						process_u(t_str *m, t_data *d, va_list *ap);
void						process_big_u(t_str *m, t_data *d, va_list *ap);
void						process_p(t_str *m, va_list *ap);
void						process(t_str *m, t_data *d, va_list *ap);
int							preprocess_flags(t_str *m, t_data *d, char *s);
int							preprocess_size(t_str *m, t_data *d, char *s);
int							preprocess_mod(t_str *m, t_data *d, char *s);
int							preprocess(t_str *m, char *s, va_list *ap);

int							ft_atoi(const char *nptr);
void						ft_bzero(void *s, size_t n);
int							ft_isdigit(int c);
char						*ft_itoa(int n);
void						ft_putchar(char c);
int							ft_strcmp(const char *s1, const char *s2);
char						*ft_strcpy(char *dest, const char *src);
char						*ft_strdup(const char *s);
char						*ft_strjoin(char const *s1, char const *s2);
size_t						ft_strlen(const char *s);
char						*ft_strnew(size_t size);
char						*ft_strsub(char const *s, t_ui start, size_t len);
char						*ft_strupper(char *s);
char						*ft_ulltoa_base(t_ull n, int base);

#endif
