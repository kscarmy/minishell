/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:45:12 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 14:24:35 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cut_bin(t_data *data)
{
	int	u;
	int i;

	i = 0;
	u = ft_bin_size(data);
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 9;
	data->token->bin = (char **)malloc(sizeof(char*) * (u + 1));
	data->token->bin[u] = NULL;
	u = ft_space(data->input, data->i);
	ft_strdel(&data->token->arg);
	u = u + ft_space(data->input, data->i + u);
	while (data->input[data->i + u] && ft_is_separator(data->input, data->i + u) == 0)
	{
		u = u + ft_space(data->input, data->i + u);
		data->token->bin[i] = ft_one_arg(data, u);
		u = ft_incre_one_arg(data, u);
		u = u + ft_space(data->input, data->i + u);
		i++;
	}
	data->i = data->i + u;
	return (1);
}

int	ft_bin_size(t_data *data)
{
	int		nbr;
	int		u;

	u = 0;
	nbr = 0;
	while (data->input[data->i + u] && ft_is_separator(data->input, data->i + u) == 0)
	{
		u = u + ft_space(data->input, data->i + u);
		u = ft_incre_one_arg(data, u);
		u = u + ft_space(data->input, data->i + u);
		nbr++;
	}
	return (nbr);
}
