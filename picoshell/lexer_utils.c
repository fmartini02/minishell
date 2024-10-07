/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:58:42 by fmartini          #+#    #+#             */
/*   Updated: 2024/10/07 18:28:36 by francema         ###   ########.fr       */
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
	str = malloc (sizeof (char) * ( ft_strlen_till_char((char *)s, *i, '"') + 1));//allocating memory for string, eventual variables and null byte
	if (!str)
		return NULL;
	while (s[*i] && s[*i] !='"')
	{
		if (s[*i] == '$')
			ft_dq_utils(&str, s, i, &j);//if variable exist swap it for its value
		else
		{
			str[j++] = s[(*i)];//copying "string"
			(*i)++;
		}
	}
	if (s[*i] == '"')
		(*i)++;// skip last "
	str[j] = '\0';
	str = ft_strjoin_free(str, ft_strdup("\""));//adding " at the end of the string
	str = ft_strjoin_free(ft_strdup("\""), str);//adding " at the beginning of the string
	return (str);
}

char	*ft_norm_case_utils(const char *s, int *i)
{
	int		j;
	char	*doll;
	char	*temp;

	j = 0;
	temp = str_init_in_normal_case(s);
	while (s[*i] && s[*i] != '"' && s[*i] != 39)
	{
		if (s[*i] == '$')
		{
			doll = ft_doll_case((char *)s, *i);
			temp = ft_strjoin_free(temp, doll);//str is freed in ft_strjoin_free
			*i += ft_word_len(s, *i) - 1;//skip variable name
			j += ft_strlen(doll);//add variable value len
			free(doll);//doll is malloced in ft_doll_case
		}
		else if (s[*i] == '\n')
			handle_nwline_in_norm_case(temp, i, &j);
		else if (s[*i] == '>' || s[*i] == '<')
			break ;
		else
			temp[j++] = s[(*i)++];
	}
	temp[j] = '\0';
	return (temp);
}

char	*ft_normal_case(const char *s, int *i)
{
	char	*str;
	char	*temp;

	temp = ft_norm_case_utils(s, i);
	str = ft_strdup(temp);//in case of a redi case there is more memory allocated in temp than needed
	free(temp);
	return (str);
}

char	*ft_init_line(const char *s)
{
	char	*line;
	int		vars_len;

	if (ft_strlen(s) == 0)
	{
		line = malloc(sizeof(char) * 2);
		if (!line)
		{
			perror("malloc error in ft_init_line");
			return (NULL);
		}
		line = ft_strcpy(line, "\n\0");
	}
	else
	{
		vars_len = ft_vars_len(s);
		line = malloc(sizeof(char) * (ft_strlen(s) + vars_len + 1));
		if (!line)
		{
			perror("malloc error in ft_init_line");
			return (NULL);
		}
		line[0] = '\0';
	}
	return (line);
}
