/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:06:50 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 14:18:07 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_parse_cmd_not_found(t_data *data)
{
	ft_putstr("minishell : command not found : ");
	ft_putstr(&(data->input[data->i]));
	ft_putchar('\n');
	return (-1);
}

int	ft_parse_input(t_data *data)
{
	int	found;

	data->i = 0;
	found = 0;
	while (data->exit == 0 && found >= 0 && data->input[data->i])
	{
		found = 0;
		data->i = data->i + ft_space(data->input, data->i);
		if (ft_str_size(&(data->input[data->i])) == 0)
			found++;
		if (found == 0 && ft_cut_exit(data))
			found++;
		if (found == 0 && ft_cut_env(data, data->i) == 1)
			found++;
		if (found == 0 && ft_cut_cd(data, data->i))
			found++;
		if (found == 0 && ft_cut_echo(data, data->i) == 1)
			found++;
		if (found == 0 && ft_cut_pwd(data) == 1)
			found++;
		if (found == 0 && ft_cut_export(data) == 1)
			found++;
		if (found == 0 && ft_cut_unset(data, data->i) == 1)
			found++;
		if (found == 0 && ft_cut_redirects(data) == 1)
			found++;
		if (found == 0 && ft_cut_bin(data) == 1)
			found++;
		if (found == 0)
			found = ft_parse_cmd_not_found(data);
	}
	if (found == -1)
		return (1);
	return (0);
}
