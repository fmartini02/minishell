/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:39:12 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:39:12 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(void *lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst == NULL)
		return;
	tmp = (t_list *)lst;
	(*del)(tmp->content);
}
