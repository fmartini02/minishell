/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:12 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/04 15:28:39 by fmartini         ###   ########.fr       */
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

int	ft_word_len(const char *s, int i)
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

int	ft_strlen_till_char(char *s, int i, char c)
{
	int	r;

	r = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		r++;
		i++;
	}
	return (r);
}

int	ft_matlen(char **s)
{
	int	i;

	i = 0;
	while(s[i] != '\0')
		i++;
	return (i);
}
