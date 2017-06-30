/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 21:43:44 by jchow             #+#    #+#             */
/*   Updated: 2017/06/29 21:43:46 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ull ft_atoull_base(const char *str, int base)
{
    t_ull i = 0;
    t_ull acc = 0;

    if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
        i++;
    while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f'))
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            acc = acc * base + (str[i] - '0');
            i++;            
        }
        if (str[i] >= 'a' && str[i] <= 'f')
        {
            acc = acc * base + (str[i] - 'a' + 10);
            i++;
        }
    }
    return (acc);
}
