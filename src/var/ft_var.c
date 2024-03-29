/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:02:35 by guderram          #+#    #+#             */
/*   Updated: 2022/07/13 13:37:32 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_found_var_name_dol(t_data *data)
{
	t_var	*var;
	char	*str;

	str = "?";
	if (data->var != NULL)
		var = data->var;
	else
		return (0);
	while (var != NULL)
	{
		if (var->name && str[0] == var->name[0] && str[1] == var->name[1])
			return (1);
		var = var->next;
	}
	return (0);
}

t_var	*ft_found_var_name(t_data *data, char *str)
{
	t_var	*var;
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (data->var != NULL)
		var = data->var;
	else
		return (NULL);
	if (i == 0)
		return (NULL);
	while (var != NULL)
	{
		if (str[0] == '?' && str[1] == '\0')
		{
			ft_strdel(&var->value);
			var->value = ft_itoa(ft_resize_g_return(g_return));
			return (var);
		}
		if (ft_strncmp(var->name, str, i) == 0 && var->name[i] == '\0')
			return (var);
		var = var->next;
	}
	return (NULL);
}

void	ft_disp_all_var(t_data *data, char sep, int export)
{
	t_var	*var;

	var = data->var;
	while (var != NULL && var->name != NULL)
	{
		if (var->name && var->name[0] == '?' && var->name[1] == '\0')
			var = var->next;
		if (var == NULL)
			break ;
		if (var && var->name != NULL && export == 1)
			ft_putstr("declare -x ");
		ft_putstr(var->name);
		ft_putchar(sep);
		if (var && var->name != NULL && export == 1)
			ft_putchar('"');
		if (var && var->name != NULL)
			ft_putstr(var->value);
		if (var && var->name != NULL && export == 1)
			ft_putchar('"');
		if (var)
			ft_putchar('\n');
		if (var)
			var = var->next;
	}
}
