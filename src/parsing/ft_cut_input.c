/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:06:50 by guderram          #+#    #+#             */
/*   Updated: 2022/02/24 11:10:22 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_parse_input(t_data *data) // return 0 si ok, sinon 1 ou numero specifique a l'erreur
{
	int	found;

	data->i = 0;
	found = 0;

//	if (!cut_str(data, data->input))
//		return (1);
//	return (0);
	if (ft_cut_exit(data))			// sets data->exit = 1 if command is "exit"
		return (0);

	if (cut_history(data) == 1)		// checks if command is "history" and creates its token
		found++;
	else 
		add_history(data->input, 1);	// adds line to history if it is not "history"
	
//	if (ft_cut_env(data))			// checks if command is "env" and creates its token
//		found++;
	
	if (ft_cut_cd(data))
		found++;
	
	while (data->input[data->i])
	{
		ft_space(data->input, data->i);
		// if ()
		if (found == 0 && ft_cut_echo(data, data->i) == 1)
			found++;
		if (found == 0 && ft_cut_pwd(data) == 1)
			found++;
		if (found == 0 && ft_cut_export(data) == 1)
			found++;
		if (found == 0 && ft_cut_unset(data, data->i) == 1)
			found++;
		if (found == 0 && ft_cut_bin(data) == 1)
			found++;
		data->i = data->i + 1;
	}
	if (found == 0)
	{
		if (!'\n')
			printf("minishell : command not found : %s\n", data->input);
		return (1); // pas de commande trouvee
	}
	return (0);
}
