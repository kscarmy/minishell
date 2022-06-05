/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:38:20 by guderram          #+#    #+#             */
/*   Updated: 2022/06/05 16:27:39 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    ft_exit(t_data *data, t_token *tok)
{
    int     ret;
    int     i;

    i = 0;
    ret = -111111;
    if (tok->arg == NULL)
    {
        if (tok->prev == NULL && tok->next == NULL) // pour exit
		    data->exit = 1;
        else
            data->exit = 0;
        return ;
    }
    i = i + ft_space(tok->arg, i);
    while (tok->arg && tok->arg[i] != '\0' && ft_is_number(tok->arg[i]) == 1)
        i++;
    i = i + ft_space(tok->arg, i);
    ret = ft_atoi(tok->arg);
    // if ( tok->arg[i] != '\0')
    // {

    // }
    // ret = ft_atoi(tok->arg);
    if (tok->arg[i] == '\0' && tok->prev == NULL && tok->next == NULL) // pour exit
    {
        g_return = ret;
		data->exit = 1;
    }
    else
    {
        data->exit = 0;
        ft_putstr("bash: ");
		ft_putstr("exit");
		ft_putstr(" : numeric argument required or too many arguments\n");
		g_return = 2;
    }
}