/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:39:49 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:39:49 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstmap(void *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	t_list	*lis;

	new_lst = NULL;
	lis = (t_list *)lst;
	while (lst)
	{
		new_node = (t_list *)ft_lstnew((*f)(lis->content));
		if (!new_node)
		{
			ft_lstclear((void **)&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back((void **)&new_lst, new_node);
		lis = lis->next;
	}
	return ((void *)new_lst);
}
