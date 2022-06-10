/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token_list_bis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:48:16 by guderram          #+#    #+#             */
/*   Updated: 2022/06/10 12:00:03 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_redirect_input(t_data *data, t_token *tok)
{
	int	fd;

	if (tok->prev == NULL || tok->prev->prev == NULL
		|| tok->prev->prev->arg == NULL)
		return (tok);
	fd = open(tok->prev->prev->arg, O_RDWR);
	if (fd < 0)
	{
		ft_putstr("bash: ");
		ft_putstr(tok->prev->prev->arg);
		ft_putstr(": No such file or directory\n");
		g_return = 1;
	}
	else
	{
		ft_fd_redir(data, fd, -10);
		ft_launch_cmd(data, tok);
		ft_pipe_close_data_fd(data, 0);
	}
	if (tok->prev != NULL && tok->prev->prev
		!= NULL && tok->prev->prev->prev != NULL)
		tok = tok->prev->prev;
	else
		tok = NULL;
	return (tok);
}

void	ft_read_token_list_bis(t_data *data, t_token *t)
{
	if (t != NULL && t->prev != NULL && t->prev->sep == 2)
	{
		ft_pipe_close_data_fd(data, 1);
		ft_pipe_out(data);
	}
	if (t != NULL && t->cmd != -1)
		ft_launch_cmd(data, t);
}

void	ft_read_token_list(t_data *data)
{
	t_token	*t;

	// printf("g_return entree : %d\n", g_return);
	t = ft_ret_last_token(data);
	while (data->exit == 0 && t != NULL)
	{
		t = ft_read_token_list_cat(data, t);
		if (t != NULL && t->prev != NULL
			&& (t->prev->sep == 3 || t->prev->sep == 5))
			t = ft_read_token_list_while_redir(data, t);
		if (t != NULL && t->prev != NULL && t->prev->sep == 4)
			t = ft_redirect_input(data, t);
		if (t != NULL && t->next != NULL && t->next->sep == 2)
		{
			ft_pipe_close_data_fd(data, 0);
			ft_pipe_in(data);
		}
		if (t != NULL && t->prev == NULL)
			ft_pipe_close_data_fd(data, 1);
		if (t != NULL && t->prev != NULL && t->prev->sep == 6)
			t = ft_here_doc(data, t);
		ft_read_token_list_bis(data, t);
		if (t != NULL && t->prev != NULL)
			t = t->prev;
		else
			t = NULL;
	}
	// printf("g_return sortie : %d\n", g_return);
}

void	ft_print_token_list(t_data *data)
{
	t_token	*token;
	int		i;

	token = data->token;
	i = 0;
	printf("\n");
	while (token != NULL)
	{
		printf("-------------------------------\n");
		printf("Tok adr %p -- ", token);
		printf("cmd %d sep %d", token->cmd, token->sep);
		if (token->arg != NULL)
			printf(" arg '%s'", token->arg);
		while (token->bin != NULL && token->bin[i])
		{
			printf(" %p '%s'", token->bin[i], token->bin[i]);
			i++;
		}
		printf("\n");
		token = token->next;
	}
	printf("-------------------------------\n");
}

int	ft_read_token_list_cat_while(t_token *t)
{
	// printf("bin0 <%s>\n", t->bin[0]);
	if (t->bin != NULL && t->bin[0] !=  NULL && ft_strncmp(t->bin[0], "cat", 3) == 0 && t->bin[1] == NULL)
	{
		// printf("bin 0 : <%s>\n", t->bin[0]);
		if (t->prev != NULL && t->prev->sep == 2 && t->prev->prev != NULL)
			return (1);
	}
	return (0);
}

t_token	*ft_read_token_list_cat(t_data *data, t_token *tok)
{
	t_token	*t;
	char	*tmp;

	t = tok;
	data->cat = 0;
	while (ft_read_token_list_cat_while(t) == 1)
	{
		// printf("incr cat\n");
		data->cat = data->cat + 1;
		t = t->prev->prev;
	}
	// printf("whiloe ok\n");
	if (t->prev == NULL && data->cat > 0)
	{
		// printf("ok\n");
		ft_launch_cmd(data, t);
		while (data->cat > 0)
		{
			tmp = readline("");
			ft_strdel(&tmp);
			data->cat = data->cat - 1;
		}
		return (NULL);
	}
	return(tok);
}