/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:38:40 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:38:40 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(void **lst, void *new)
{
	t_list	**lis;
	t_list	*nw;

	lis = (t_list **)lst;
	nw = new;
	if (*lis)
	{
		ft_lstlast((void *)lis);
		(*lis)->next = nw;
	}
	else
		*lis = nw;
}
