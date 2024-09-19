/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:39:01 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:39:01 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(void **lst, void (*del)(void*))
{
	t_list	*nxt;
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		nxt = (tmp)->next;
		ft_lstdelone(tmp, del);
		tmp = nxt;
	}
	*lst = NULL;
}
