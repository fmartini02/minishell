/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:12 by fmartini          #+#    #+#             */
/*   Updated: 2024/02/28 15:57:50 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_quote(char *s, int i)
{
	int	len;

	len = 0;
	while (s[i] != '39')
		len++;
	return (len);
}

int	ft_strlen_dquote(char *s, int i)
{
	int	len;

	len = 0;
	while (s[i] != '34')
		len++;
	return (len);
}

int	ft_wlen(char *s, int i)
{
	int	len;

	len = 0;
	while(s[i] != ' ' || s[i] != '	')
		len++;
	return (len);
}
