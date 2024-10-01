/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_case_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:08:24 by fmartini          #+#    #+#             */
/*   Updated: 2024/09/30 18:11:24 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_dq_utils(char **str, const char *s, int *i, int *j)
{
	int k;
	char *doll_cont;

	k = 0;
	doll_cont = ft_doll_case((char*)s, *i + *j);//getting var value
	while (doll_cont[k])
	{
		(*str)[*j] = doll_cont[k];//swapping var name for var value
		(*j)++;
		k++;
	}
	*j -= k;//going back to the end of the var value
	while (s[*i + *j] != ' ' && s[*i + *j])//skipping var name
		(*i)++;
	*j += k;//adding var value len
}

char	*ft_doll_case(char *s, int i)
{
	int k;
	char *doll_var;
	char *var_value;

	i++;//skipping $
	k = ft_word_len(s, i);//var_name_len
	var_value = NULL;//if var is not found
	doll_var = malloc(sizeof(char) * (k + 1));
	if (!doll_var)
		return NULL;
	doll_var = ft_get_var_name(s, doll_var, i, 0);//getting var name
	var_value = getenv(doll_var);//getting env var line <var_name>=<var_value>
	free(doll_var);
	if (!var_value)
		return (NULL);
	return (ft_strdup(var_value));//returning var value
}

char	*ft_get_var_name(const char *s, char *doll_var, int i, int j)
{
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t' && s[i] != '"')
	{
		doll_var[j] = s[i];
		i++;
		j++;
	}
	doll_var[j] = '\0';
	return (doll_var);//returning var name
}

int	ft_find_dq_len(const char *s, int i)
{
	int	str_len;
	int	var_name_len;
	int	var_cont_len;
	int	j;

	str_len = ft_strlen_till_char((char*)s, i, '"');//len of string without var content
	var_name_len = 0;//len of var name
	var_cont_len = 0;//len of var content
	j = 0;
	while (j < str_len)
	{
		if (s[i + j] == '$')
		{
			var_name_len += ft_word_len(s, i + j) - 1;//getting var name len, -1 for " at the end
			var_cont_len += ft_strlen(ft_doll_case((char *)s, i + j));//getting var content len
			while (s[i + j] != ' '&& s[i + j])//skipping var name
				j++;
		}
		j++;
	}
	return (str_len + var_cont_len - var_name_len);//returning len of string with var content but without var name len
}

