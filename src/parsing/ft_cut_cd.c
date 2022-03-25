/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:59:30 by mourdani          #+#    #+#             */
/*   Updated: 2022/03/25 07:21:55 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	change_dir(t_data *data)                 // changes directory
{
	if (data->token->arg == NULL || !ft_strncmp(data->token->arg, "~\0", 2))
	{
		chdir(getenv("HOME"));
		if (data->pwd)
		{
			free(data->pwd);
			data->pwd = NULL;
		}
		data->pwd = getcwd(NULL, 0);
		return (1);
	}
	if (chdir(data->token->arg) < 0)
		perror(data->token->arg);        // printf error message
	if (data->pwd)
	{
		free(data->pwd);
		data->pwd = NULL;
	}
	data->pwd = getcwd(NULL, 0);
	return (1); //ok
}



int	ft_cut_cd(t_data *data, int i) // ret 1 si cd est trouvé, sinon ret 0
{
	char *str;
	int u;

	u = 0;
	str = "cd";
	i = i + ft_space(data->input, i);
	while (data->input[i] && data->input[i] != ' ' && ft_is_separator(data->input, i) == 0)
	{
		if (ft_is_a_b(data->input[i], str[u]) == 1)
			u++;
		i++;
	}
	if (u == 2)
	{
		data->i = data->i + 2 + ft_space(data->input, data->i);
		ft_create_cd_token(data);
		return (1);
	}
	return (0);
}

void	ft_create_cd_token(t_data *data) // cree le token de la commande cd.
{
	int	u;

	u = 0;
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 6;

	while (data->input[data->i + u] && ft_is_separator(data->input, (data->i + u)) == 0)
		u++;
	// while (ft_is_separator(data->input, (data->i + u)) == 0 && data->input[data->i + u])
	// 	u++;
	data->token->arg = ft_malloc_str(data, u);
	if (data->token->arg != NULL)
	{
		data->token->arg = ft_strncpy(data->token->arg, &(data->input[data->i]), u);
		data->i = data->i + u;
		// data->token->arg = cut_str(data, data->token->arg);
	}
	else
		data->err = 200; // erreur malloc
}
