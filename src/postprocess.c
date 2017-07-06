/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:04:05 by jchow             #+#    #+#             */
/*   Updated: 2017/07/05 16:46:17 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	postprocess_width(t_str *master, t_data *data, int i, int j)
{
	if (!data->flag[4] || data->flag[0])
		postprocess_num_space(master, data, i, j);
	else
	{
		if (data->flag[6])
			postprocess_num_zero_prec(master, data, i, j);
		else
			postprocess_num_zero(master, data, i, j);
	}
}

void	postprocess_num(t_str *master, t_data *data)
{
	int	i;
	int	j;

	if (data->flag[3])
		postprocess_prefix(master, data);
	i = data->flag[6];
	j = ft_strlen(master->tmp);
	while (i-- > j)
		ft_freeappend(&master->tmp, &master->tmp2, "0", 1);
	if (data->flag[5] >= data->flag[6])
		postprocess_width(master, data, i, j);
	else
	{
		if (!data->neg && (data->spec == 'd' ||
					data->spec == 'D' || data->spec == 'i'))
		{
			if (data->flag[1])
				ft_freeappend(&master->tmp, &master->tmp2, "+", 1);
			else if (data->flag[2])
				ft_freeappend(&master->tmp, &master->tmp2, " ", 1);
		}
		else if (data->neg)
			ft_freeappend(&master->tmp, &master->tmp2, "-", 1);
	}
}

void	postprocess_string(t_str *master, t_data *data)
{
	if (data->prec)
	{
		master->tmp2 = ft_strsub(master->tmp, 0, data->flag[6]);
		free(master->tmp);
		master->tmp = NULL;
		ft_freejoin(&master->tmp, &master->tmp2);
		if (data->flag[0])
			while (data->flag[5]-- > data->flag[6])
				ft_freeappend(&master->tmp, &master->tmp2, " ", 0);
		else
			while (data->flag[5]-- > data->flag[6])
				ft_freeappend(&master->tmp, &master->tmp2, " ", 1);
	}
}

void	postprocess(t_str *master, t_data *data)
{
	if (data->spec != 's' && data->spec != 'S')
		postprocess_num(master, data);
	else if (data->spec == 's' || data->spec == 'S')
		postprocess_string(master, data);
	master->tmp2 = ft_strjoin(master->ret, master->tmp);
	free(master->tmp);
	ft_freejoin(&master->ret, &master->tmp2);
}
