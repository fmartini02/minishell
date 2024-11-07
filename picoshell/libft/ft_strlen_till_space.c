/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_till_space.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:42:19 by francema          #+#    #+#             */
/*   Updated: 2024/10/28 16:03:52 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_till_space(const char *s, int i)
{
	while (s[i] && s[i] != ' ' && !(s[i] >= '\t' && s[i] <= '\r'))
		i++;
	return (i);
}