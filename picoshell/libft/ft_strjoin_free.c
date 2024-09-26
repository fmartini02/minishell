/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:24:06 by francema          #+#    #+#             */
/*   Updated: 2024/09/26 18:02:36 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;

	if (s1 == NULL && s2 == NULL)
		return NULL;
	if (s1 == NULL)
		return (ft_strdup(s2)); // Duplicate s2 if s1 is NULL
	if (s2 == NULL)
		return s1;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	ft_strcpy(str, (const char*)s1);
	ft_strcat_smart(str, (char *)s2);
	free(s1);
	return (str);
}
