/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:58:42 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/21 17:18:00 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_sngl_q_case(const char *s, int i)
{
	int		q_len;
	int		j;
	char	*str;

	j = 0;
	q_len = 0;
	while (s[i+q_len] && s[i + q_len] != 39)
		q_len++;
	str = malloc (sizeof(char) * q_len + 1);
	if (!str)
		return NULL;
	while (j < q_len)
	{
		str[j] = s[i];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_db_q_case(const char *s, int i)
{
	int		dq_len;
	int		j;
	char	*str;

	j = 0;
	dq_len = 0;
	while (s[i + dq_len] != '\0' && s[i + dq_len] != '"')
		dq_len++;
	str = malloc (sizeof (char) * dq_len + 1);
	if (!str)
		return NULL;
	while (j < dq_len)
	{
		// if (s[i] == '$')
		// {
		// 	tok[i_t] = ft_doll_case();
		// 	i_t++;
		// }
		str[j] = s[i + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char *ft_word_case(const char *s, int i)
{
	if (s == NULL || s[i] == '\0')
		return NULL;
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t'))
		i++;
	int j;
	int k;
	int	word_len;

	k = i;
	j = 0;
	word_len = ft_wlen(s, i);
	i = k;
	char *str = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!str)
		return NULL;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}

int ft_count_words(const char *s)
{
	int i = 0;
	int word_count = 0;

	while (*s)
	{
		while (*s == ' ' || *s == '\t')
			s++;
		if (*s)
			word_count++;
		while (*s && *s != ' ' && *s != '\t')
			s++;
	}
	return (word_count);
}


int	ft_new_word(const char *s, int i)
{
	while (s[i] != ' ' && s[i] != '\t' && s[i])
		i++;
	while ((s[i] == ' ' || s[i] == '\t') && s[i])
		i++;
	return (i);
}
