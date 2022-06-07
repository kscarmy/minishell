/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_export_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:22:07 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 15:22:36 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_export_sizeof_arg(char	*str, int i)
{
	int	u;

	u = 0;
	while (str[i + u] && ft_is_separator(str, (i + u)) == 0
		&& str[i + u] != ' ')
		u++;
	if (ft_check_char(&(str[i]), '=', u) == 1)
		return (u);
	return (0);
}

void	ft_export_in_bin(t_data *data, int nb)
{
	int	i;
	int	u;
	int	s;

	i = data->i;
	u = 0;
	while (data->input[i] && ft_is_separator(data->input, i) == 0 && u < nb)
	{
		i = i + ft_space(data->input, i);
		s = ft_export_sizeof_arg(data->input, i);
		if (s > 0)
		{
			data->token->bin[u] = ft_malloc_str(data, s);
			data->token->bin[u] = ft_strncpy(
					data->token->bin[u], &(data->input[i]), s);
			u++;
			i = i + s;
		}
		else
			i++;
	}
	data->i = i;
	data->token->bin[u] = NULL;
}

void	ft_create_export_token(t_data *data)
{
	int	i;

	i = 0;
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 3;
	data->token->arg = ft_malloc_str(data, 0);
	i = ft_export_count_equal(data);
	data->token->bin = malloc(sizeof(char *) * (i + 1));
	if (data->token->bin == NULL)
		data->err = 8010;
	else
		ft_export_in_bin(data, i);
	ft_parse_export(data);
}
