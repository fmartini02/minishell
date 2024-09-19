/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:42:16 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:42:16 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		ii;
	int		lensub;
	//char	*n;

	//n = 0;
	res = (char **)ft_calloc(sizeof(char *), (ft_strlen(s) / 2) + 8);
	//res[0] = n;
	i = 0;
	ii = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		lensub = i;
		while (s[lensub] != c && s[lensub])
			lensub++;
		lensub -= i;
		if (lensub)
			res[ii] = ft_substr(s, i, lensub);
		ii++;
		i += lensub;
	}
	return (res);
}
