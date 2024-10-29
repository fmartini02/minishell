/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_word_from_indx.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:27:19 by francema          #+#    #+#             */
/*   Updated: 2024/10/22 19:28:57 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_word_from_indx(char *s, int i)
{
	int		j;
	char	*ret;

	j = 0;
	ret = malloc(sizeof(char) * (ft_strlen_till_char(s, i, ' ') + 1));
	if (!ret)
		return (NULL);
	while (s[i] && s[i] != ' ')
	{
		ret[j++] = s[i++];
	}
	ret[j] = '\0';
	return (ret);
}
