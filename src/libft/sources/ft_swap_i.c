/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <mourdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 05:29:08 by mourdani          #+#    #+#             */
/*   Updated: 2022/02/10 05:29:10 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_swap_i(int *a, int *b)
{
	int	auxiliary;

	auxiliary = *a;
	*a = *b;
	*b = auxiliary;
}
