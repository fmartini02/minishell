/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:39:30 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:39:30 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstlast(void *lst)
{
	t_list	*tmp;

	tmp = (t_list *)lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return ((void *)tmp);
}
