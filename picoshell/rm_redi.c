/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_redi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:26:47 by francema          #+#    #+#             */
/*   Updated: 2024/10/29 18:31:32 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_segment(const char *s, int start, int end)
{
	char *ret = malloc(sizeof(char) * (end - start + 1));
	if (!ret)
	{
		perror("minishell: malloc error");
		return NULL;
	}
	strncpy(ret, &s[start], end - start);
	ret[end - start] = '\0';
	return ret;
}

char *rm_redi_utils(char *s, int *j)
{
	int		start;
	int		cur;
	char	*ret;

	start = *j;
	cur = *j;
	while (s[cur] && s[cur] != '<' && s[cur] != '>' && s[cur] != '|')
		cur++;
	if (cur > start && ft_isdigit(s[cur - 1]) && s[cur] != '|')
	{
		while (cur > start && ft_isdigit(s[cur - 1]))
			cur--;
	}
	ret = copy_segment(s, start, cur);
	if (!ret)
		return NULL;
	*j = cur;
	return (ret);
}

char	*rm_redi(t_redi *redi)
{
	char	*s;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	s = redi->s;
	while (s[i])
	{
		tmp1 = rm_redi_utils(s, &i);//i increments till redi info
		if (!tmp1)
			return (NULL);
		if (s[i] && s[i] == '|')
		{
			tmp2 = ft_strdup(&s[i]);
			tmp1 = ft_strjoin_free(tmp1, tmp2);
			ret = ft_strjoin_free(ret, tmp1);
			free(tmp2);
			free(tmp1);
			return (ret);
		}
		else if (s[i] && s[i] != '|')
			i = ft_next_char_indx(s, i, ' ');//to skip till next space
		if (s[i - 1] == '<' || s[i - 1] == '>' || s[i - 1] == '&')
		{
			i = ft_skip_spaces(s, i);
			while (s[i] && !ft_is_space(s[i]) && s[i] != '|')
				i++;
		}
		if (!s[i])
		{
			ret = ft_strjoin_free(ret, tmp1);
			free(tmp1);
			return (ret);
		}
		if (s[i])
		{
			tmp2 = rm_redi_utils(s, &i);
			if (s[i] && s[i] == '|')
			{
				ret = ft_strjoin_free(ret, tmp1);
				free(tmp1);
				ret = ft_strjoin_free(ret, tmp2);
				free(tmp2);
				tmp3 = ft_strdup(&s[i]);
				ret = ft_strjoin_free(ret, tmp3);
				free(tmp3);
				return (ret);
			}
			if (s[i] && s[i] != '|')
				i = ft_next_char_indx(s, i, ' ');
			tmp1 = ft_strjoin_free(tmp1, tmp2);
			ret = ft_strjoin_free(ret, tmp1);
			free(tmp2);
			free(tmp1);
		}
	}
	return (ret);
}
