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

int	ft_wlen(const char *s, int i)
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

int	ft_find_dq_len(const char *s, int i)
{
	int	str_len;
	int	var_name_len;
	int	var_cont_len;
	int	j;

	str_len = ft_strlen_dquote(s, i);
	var_name_len = 0;
	var_cont_len = 0;
	j = 0;
	while (j < str_len)
	{
		if (s[i + j] == '$')
		{
			var_name_len += ft_wlen(s, i + j);
			var_cont_len += ft_strlen(ft_doll_case((char *)s, i + j));
			while (s[i + j] != ' '&& s[i + j])
				j++;
		}
		j++;
	}
	return (str_len + var_cont_len - var_name_len);
}
