/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:40:14 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:40:14 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(void *lst)
{
	int	i;
	t_list	*lis;

	i = 0;
	lis = (t_list *)lst;
	while (lis)
	{
		lis = lis->next;
		i++;
	}
	return (i);
}
