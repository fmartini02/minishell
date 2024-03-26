/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:58:42 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/26 17:49:31 by fmartini         ###   ########.fr       */
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
	int		j;
	char	*str;

	i++;
	j = 0;
	str = malloc (sizeof (char) * (ft_find_dq_len(s, i)+ 1));//allocating memory for string and eventual variables
	if (!str)
		return NULL;
	while (s[i] && s[i] !='"')
	{
		if (s[i + j] == '$')
			ft_dq_utils(&str, s, &i, &j);//if variable exist swap it for its value
		str[j] = s[i];//copying "string"
		i++;
		j++;
	}
	str[j] = '\0';
	//printf("str: %s\n", str);
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
	word_len = ft_word_len(s, i);
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

