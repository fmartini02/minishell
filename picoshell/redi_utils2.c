/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:51:10 by francema          #+#    #+#             */
/*   Updated: 2024/11/07 17:31:12 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_lexer_redi_case(const char *s, int *i, t_tok *tok)
{
	char	*ret;
	int		j;
	int		y;

	j = 0;
	y = *i;
	tok->redi_flag = 1;
	ret = malloc(sizeof(char) * (ft_strlen_till_char((char *)s, y, ' ') + 1));
	if (!ret)
		return (NULL);
	while (s[y] && !ft_is_space(s[y]))
	{
		ret[j++] = s[y++];
	}
	ret[j] = '\0';
	*i = y;
	return (ret);
}
