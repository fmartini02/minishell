/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:34:42 by francema          #+#    #+#             */
/*   Updated: 2024/09/25 19:40:03 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_list(void *head)
{
	t_list *tmp;

	tmp = (t_list *)head;
	while (tmp)
	{
		ft_putstr((const char *)tmp->content);
		tmp = tmp->next;
	}
}
