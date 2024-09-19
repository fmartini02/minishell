/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:17:01 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 23:17:01 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = content;
	new->next = NULL;
	return ((void *)new);
}
