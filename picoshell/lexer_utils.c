/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:58:42 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/19 15:41:15 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_sngl_q_case(char *s, int i)
{
	int		q_len;
	int		j;
	char	*str;

	j = 0;
	i++;
	q_len = ft_strlen_quote(s, i);
	str = malloc (sizeof(char) * q_len);
	while (s[i] != 39)
	{
		str[j] = s[i];
		j++;
		i++;
	}
	return (str);
}

char	*ft_db_q_case(char *s, int i, char **tok, int i_t)
{
	int		q_len;
	int		j;
	char	*str;

	j = 0;
	i++;
	q_len = ft_strlen_dquote(s, i);
	str = malloc (sizeof (char) * q_len);
	while (s[i] != 34)
	{
		// if (s[i] == '$')
		// {
		// 	tok[i_t] = ft_doll_case();
		// 	i_t++;
		// }
		str[j++] = s[i++];
		tok[i_t++] = str;
	}
	return (str);
}

char	*ft_word_case(char *s, int i)
{
	int		w_len;
	int		j;
	char	*str;

	j = 0;
	w_len = ft_wlen(s, i);
	str = malloc (sizeof(char) * w_len);
	while (s[i] != ' ' || s[i] != '\t')
	{
		str[j] = s[i];
		i++;
		j++;
	}
	return (str);
}

int	ft_count_words(char *s)
{
	int	i;
	int	w_c;

	i = 0;
	w_c = 0;
	while (*s)
	{
		while(*s == ' ' || *s == '\t')
			s++;
		while(*s && (*s != ' ' || *s != '\t'))
		{
			i++;
			s++;
		}
		if (i)
			w_c++;
		i = 0;
	}
	return (w_c);
}

int	ft_new_word(char *s, int i)
{
	while ((s[i] != ' ' || s[i] != '\t') && s[i])
		i++;
	return (i);
}
