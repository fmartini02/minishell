/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:35:02 by fmartini          #+#    #+#             */
/*   Updated: 2024/10/24 16:33:13 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_skip_spaces(char *s, int i)
{
	while(s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))// cycle to skip spaces
		i++;
	return (i);
}
