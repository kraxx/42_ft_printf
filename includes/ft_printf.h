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
	char *ret;
	// int ret;
	int len;
}				t_str;

typedef struct s_data
{
	// char *tmp;
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

#endif