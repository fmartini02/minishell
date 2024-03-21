/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:12 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/20 11:19:31 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_quote(const char *s, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != 39)
	{
		len++;
		i++;
	}
	return (len);
}

int	ft_strlen_dquote(const char *s, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != 34)
	{
		len++;
		i++;
	}
	return (len);
}

int ft_wlen(const char *s, int i)
{
	int len;

	len = 0;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
	{
		i++;
		len++;
	}
	return (len);
}
