/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:51:10 by francema          #+#    #+#             */
/*   Updated: 2024/10/26 17:17:22 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_lexer_redi_case(const char *s, int *i, t_tok *tok)
{
	char	*ret;
	int		j;

	j = 0;
	tok->redi_flag = 1;
	ret = malloc(sizeof(char) * (ft_strlen_till_char((char *)s, *i, ' ') + 1));
	if (!ret)
		return (NULL);
	while (s[*i] && s[*i] != ' ')
	{
		ret[j++] = s[(*i)++];
	}
	ret[j] = '\0';
	return (ret);
}
