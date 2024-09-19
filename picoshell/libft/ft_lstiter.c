/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:39:24 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:39:24 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(void *lst, void (*f)(void *))
{
	t_list	*tmp;

	tmp = lst;
	while (lst)
	{
		(*f)(tmp->content);
		tmp = tmp->next;
	}
}
