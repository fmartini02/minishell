/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:35:02 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/09 17:35:09 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_skip_spaces(char *s, int i)
{
	while(s[i] == ' ' || s[i] == '\t')// cycle to skip spaces
		i++;
	return (i);
}