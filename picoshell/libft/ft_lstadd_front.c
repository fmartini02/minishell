/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:38:50 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:38:50 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(void **lst, void *new)
{
	t_list	*n;
	t_list	**lis;

	lis = (t_list **)lst;
	n = new;
	n->next = *lis;
	*lis = n;
}
