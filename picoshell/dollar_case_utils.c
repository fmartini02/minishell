/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_case_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:08:24 by fmartini          #+#    #+#             */
/*   Updated: 2024/10/02 20:06:33 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_dq_utils(char **str, const char *s, int *i, int *j)
{
	int k;
	char *doll_cont;

	k = 0;
	doll_cont = ft_doll_case((char*)s, *i + *j);//getting var value
	if (!doll_cont)
		return ;
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

char	*ft_get_var_name(const char *s, int i)
{
	int		j;
	char	*var_name;

	j = 0;
	var_name = malloc(sizeof(char ) * (ft_word_len(s, i) + 1));
	if (!var_name)
		return (NULL);
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t' && s[i] != '"')
	{
		var_name[j] = s[i];
		i++;
		j++;
	}
	var_name[j] = '\0';
	return (var_name);//returning var name
}

char	*ft_doll_case(char *s, int i)
{
	char *var_name;
	char *var_value;

	i++;//skipping $
	var_name = ft_get_var_name(s, i);//getting var name
	if (!var_name)
		return (NULL);
	var_value = getenv(var_name);//getting env var line <var_name>=<var_value>
	free(var_name);
	if (!var_value)
		return (NULL);
	return (ft_strdup(var_value));//returning var value
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

