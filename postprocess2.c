/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocess2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:04:10 by jchow             #+#    #+#             */
/*   Updated: 2017/07/05 02:09:36 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	postprocess_prefix(t_str *master, t_data *data)
{
	if ((data->spec == 'o' || data->spec == 'O')
			&& ft_strlen(master->tmp) != 1 && ft_strcmp(master->tmp, "0"))
		ft_freeappend(&master->tmp, &master->tmp2, "0", 1);
	else if (data->spec == 'x')
		ft_freeappend(&master->tmp, &master->tmp2, "0x", 1);
	else if (data->spec == 'X')
		ft_freeappend(&master->tmp, &master->tmp2, "0X", 1);
}

void	postprocess_num_space(t_str *master, t_data *data, int i, int j)
{
	if (!data->neg)
	{
		if (data->flag[1])
			ft_freeappend(&master->tmp, &master->tmp2, "+", 1);
		else if (data->flag[2])
			ft_freeappend(&master->tmp, &master->tmp2, " ", 1);
	}
	else if (data->neg)
		ft_freeappend(&master->tmp, &master->tmp2, "-", 1);
	i = data->flag[5];
	j = ft_strlen(master->tmp);
	while (i-- > j)
	{
		if (data->flag[0])
			ft_freeappend(&master->tmp, &master->tmp2, " ", 0);
		else
			ft_freeappend(&master->tmp, &master->tmp2, " ", 1);
	}
}

void	postprocess_num_zero(t_str *master, t_data *data, int i, int j)
{
	i = data->flag[5];
	j = ft_strlen(master->tmp) + ((data->flag[1] ||
				data->flag[2] || data->neg) ? 1 : 0);
	while (i-- > j)
		ft_freeappend(&master->tmp, &master->tmp2, "0", 1);
	if (!data->neg)
	{
		if (data->flag[1])
			ft_freeappend(&master->tmp, &master->tmp2, "+", 1);
		else if (data->flag[2])
			ft_freeappend(&master->tmp, &master->tmp2, " ", 1);
	}
	else if (data->neg)
		ft_freeappend(&master->tmp, &master->tmp2, "-", 1);
}

void	postprocess_num_zero_prec(t_str *master, t_data *data, int i, int j)
{
	while ((size_t)data->flag[6] > ft_strlen(master->tmp))
		ft_freeappend(&master->tmp, &master->tmp2, "0", 1);
	if (!data->neg)
	{
		if (data->flag[1])
			ft_freeappend(&master->tmp, &master->tmp2, "+", 1);
		else if (data->flag[2])
			ft_freeappend(&master->tmp, &master->tmp2, " ", 1);
	}
	else if (data->neg)
		ft_freeappend(&master->tmp, &master->tmp2, "-", 1);
	i = data->flag[5];
	j = ft_strlen(master->tmp);
	while (i-- > j)
		ft_freeappend(&master->tmp, &master->tmp2, " ", 1);
}
