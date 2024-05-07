/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:58:42 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/24 18:30:11 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_sngl_q_case(const char *s, int *i)
{
	int		j;
	char	*str;

	j = 0;
	(*i)++;// skip first '
	str = malloc (sizeof(char) * ft_strlen_till_char((char *)s, *i, '\'') + 3);// + 3 bcs of ' char and null byte
	if (!str)
		return NULL;
	str[j++] = '\'';
	while (s[*i] && s[*i] != '\'')
		str[j++] = s[(*i)++];
	str[j++] = '\'';
	str[j] = '\0';
	(*i)++;// skip last '
	return (str);
}

char	*ft_db_q_case(const char *s, int *i)
{
	int		j;
	char	*str;

	j = 0;
	(*i)++;// skip first "
	str = malloc (sizeof (char) * ft_strlen_till_char((char*)s, *i, '"') + 1);//allocating memory for string, eventual variables and null byte
	if (!str)
		return NULL;
	while (s[*i] && s[*i] !='"')
	{
		if (s[*i + j] == '$')
			ft_dq_utils(&str, s, i, &j);//if variable exist swap it for its value
		str[j++] = s[(*i)++];//copying "string"
	}
	(*i)++;// skip last "
	str[j] = '\0';
	return (str);
}

char *ft_normal_case(const char *s, int *i)
{
	int j;
	int k;

	k = *i;
	j = 0;
	*i = k;
	char *str = (char *)malloc(sizeof(char) * (ft_strlen(s)+ 1));
	if (!str)
		return NULL;
	while (s[*i] != '\0' && s[*i] != '"' && s[*i] != 39)
		str[j++] = s[(*i)++];
	str[j] = '\0';
	return (str);
}

int ft_count_words(const char *s)
{
	int word_count;

	word_count = 0;
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

int	ft_vars_len(const char *s)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '"')
			len += ft_strlen(ft_db_q_case(s, &i));
		i++;
	}
	return (len);
}
