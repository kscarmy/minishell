/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:47:58 by guderram          #+#    #+#             */
/*   Updated: 2022/07/09 00:58:23 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_cd(t_data *data, t_token *token)
{
	int	i;

	i = 0;
	if (token->arg != NULL)
		i = i + ft_space(token->arg, i);
	if (token->arg == NULL || token->arg[i] == '\0' || token->arg[i] == '~')
		ft_cd_home(data);
	else if (token->arg[i] == '-')
		ft_cd_goto_opwd(data, data->opwd, ft_found_var_name(data, "OLDPWD"));
	else
		ft_cd_goto_path(data, &token->arg[i]);
}

void	ft_cd_home(t_data *data)
{
	t_var	*var;

	var = ft_found_var_name(data, "HOME");
	if (var == NULL)
	{
		ft_putstr("Minishell: cd: HOME not set\n");
		g_return = 1;
	}
	else
		ft_cd_goto_path(data, var->value);
}

void	ft_cd_goto_opwd(t_data *data, char *path, t_var *opwd)
{
	char	*tmp;

	if (opwd == NULL)
	{
		ft_putstr("Minishell: cd: ");
		ft_putstr("OLDPWD not set\n");
		g_return = 1;
	}
	else
	{
		tmp = getcwd(NULL, 0);
		chdir(path);
		ft_strdel(&data->opwd);
		data->opwd = ft_malloc_str(data, ft_strlen(data->pwd));
		data->opwd = ft_strncpy(data->opwd, data->pwd, ft_strlen(data->pwd));
		ft_strdel(&data->pwd);
		data->pwd = ft_malloc_str(data, ft_strlen(tmp));
		data->pwd = ft_strncpy(data->pwd, tmp, ft_strlen(tmp));
		ft_cd_from_data_to_var_opwd(data);
		ft_cd_from_data_to_var_pwd(data);
		ft_putstr(data->pwd);
		ft_putchar('\n');
		ft_strdel(&tmp);
	}
}

void	ft_cd_goto_path_bis(t_data *data)
{
	char	*tmp;

	tmp = NULL;
	tmp = getcwd(NULL, 0);
	ft_strdel(&data->opwd);
	data->opwd = ft_malloc_str(data, ft_strlen(data->pwd));
	data->opwd = ft_strncpy(data->opwd, data->pwd, ft_strlen(data->pwd));
	ft_strdel(&data->pwd);
	data->pwd = ft_malloc_str(data, ft_strlen(tmp));
	data->pwd = ft_strncpy(data->pwd, tmp, ft_strlen(tmp));
	ft_cd_from_data_to_var_opwd(data);
	ft_cd_from_data_to_var_pwd(data);
	ft_strdel(&tmp);
}

void	ft_cd_goto_path(t_data *data, char *path)
{
	int		i;
	char	*npath;

	i = 0;
	while (path[i] && path[i] != ' ' && ft_is_separator(data->input, i) == 0)
		i++;
	npath = ft_malloc_str(data, i);
	npath = ft_strncpy(npath, path, i);
	if (chdir(npath) < 0)
	{
		ft_putstr("Minishell: cd: ");
		ft_putstr(npath);
		ft_putstr(": No such file or directory\n");
		g_return = 1;
	}
	else
		ft_cd_goto_path_bis(data);
	ft_strdel(&npath);
}
