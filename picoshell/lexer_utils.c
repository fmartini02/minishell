/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:58:42 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/25 16:07:48 by fmartini         ###   ########.fr       */
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

char	*ft_var_name(const char *s, char *doll_var, int i, int j)
{
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
	{
		doll_var[j] = s[i];
		i++;
		j++;
	}
	doll_var[j] = '\0';
	return (doll_var);//returning var name
}

char	*ft_cont_var(char *env_var_line, int j)
{
	int		index;
	char	*ret_str;

	index = 0;
	while (env_var_line[j] != '=' && env_var_line[j] != '\0')//skipping var name
		j++;
	if (env_var_line[j] == '=')//skipping '='
		j++;
	ret_str = malloc(sizeof(char) * (ft_wlen(env_var_line, j) + 1));
	if (!ret_str)
		return NULL;
	while (env_var_line[j] != '\0')
		ret_str[index++] = env_var_line[j++];//copying var value
	ret_str[index] = '\0';//ending string
	return (ret_str);
}

char	*ft_doll_case(char *s, int i)
{
	int k;
	char *doll_var;
	char *env_var_line;
	char *var_value;

	i++;//skipping $
	k = ft_wlen(s, i);//var_name_len
	var_value = NULL;//if var is not found
	doll_var = malloc(sizeof(char) * (k + 1));
	if (!doll_var)
		return NULL;
	doll_var = ft_var_name(s, doll_var, i, 0);//getting var name
	env_var_line = getenv(doll_var);//getting env var line
	if (env_var_line)//if var is found
	{
		var_value = ft_cont_var(env_var_line, 0);
		free(env_var_line);
	}
	free(doll_var);
	return (var_value);
}

void	ft_dq_utils(char **str, const char *s, int *i, int *j)
{
	int k;
	char *doll_cont;

	k = 0;
	doll_cont = ft_doll_case(s, *i + *j);//getting var value
	while (doll_cont[k] != '\0')
		*str[(*j)++] = doll_cont[k++];//swapping var name for var value
	while (s[*i + *j] != ' ' && s[*i + *j])//skipping var name
		(*i)++;
	free(doll_cont);//freeing var value
}

char	*ft_db_q_case(const char *s, int i)
{
	int		j;
	int		k;
	int		*doll_cont;
	char	*str;

	i++;
	j = 0;
	k = 0;
	str = malloc (sizeof (char) * (ft_find_dq_len(s, i)+ 1));//allocating memory for string and eventual variables
	if (!str)
		return NULL;
	while (s[i] && s[i] !='"')
	{
		if (s[i + j] == '$')
			ft_dq_utils(&str, s, &i, &j);
		str[j] = s[i];//copying "string"
		i++;
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

