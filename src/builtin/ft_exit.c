/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:38:20 by guderram          #+#    #+#             */
/*   Updated: 2022/07/09 03:33:24 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_resize_g_return(int i)
{
	while (i > 255)
		i = i % 256;
	while (i < 0)
		i = i + 256;
	return (i);
}

void	ft_exit_bis(t_data *data, t_token *tok, int i, int ret)
{
	ret = ft_atoi(tok->arg);
	if (tok->arg[i] == '\0')
	{
		g_return = ret;
		if (tok->prev == NULL && tok->next == NULL)
			data->exit = 1;
		else
			data->exit = 0;
	}
	else
	{
		ft_putstr("bash: ");
		ft_putstr("exit");
		ft_putstr("too many arguments\n");
		g_return = 2;
	}
	if (tok->prev == NULL && tok->next == NULL)
		data->exit = 1;
	else
		data->exit = 0;
}

void	ft_exit(t_data *data, t_token *tok)
{
	int	ret;
	int	i;

	i = 0;
	ret = -111111;
	if (tok->arg == NULL)
	{
		if (tok->prev == NULL && tok->next == NULL)
			data->exit = 1;
		else
			data->exit = 0;
		return ;
	}
	i = i + ft_space(tok->arg, i);
	if (tok->arg[i] == '-')
		i++;
	else if (tok->arg[i] == '+')
		i++;
	while (tok->arg && tok->arg[i] != '\0' && tok->arg[i] != ' ')
		i++;
	i = i + ft_space(tok->arg, i);
	ft_exit_bis(data, tok, i, ret);
}
