/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_till_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:16:40 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/09 16:53:10 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy_till_char(char *dest, char *src, int i, char c)
{
	int	j;

	j = 0;
	while (src[i] && src[i] != c)
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (dest);
}
