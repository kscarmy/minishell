/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:35:31 by guderram          #+#    #+#             */
/*   Updated: 2022/06/06 13:19:55 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(t_data *data, t_token *token) // commande echo
{
	/*	sortie sur l'entree standard	*/
	// printf("ft_echo\n");
	// printf("pid : %d\n", getpid());
	ft_putstr(token->arg);
	if (token->option != 1)
		ft_putstr("\n");
	data->i = data->i;
	// ft_delete_token(data, token); // SEG FAULT
}
