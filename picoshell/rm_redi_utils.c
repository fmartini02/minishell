/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_redi_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:17:20 by francema          #+#    #+#             */
/*   Updated: 2024/11/07 19:47:19 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rm_skip_redi_stuff(char *s, int i)
{
	if (!s[i])
		return (i);
	else if (s[i] >= '0' && s[i] <= '9')
	{
		while (s[i] && s[i] != '<' && s[i] != '>')
			i++;
		while (s[i] && (s[i] == '<' || s[i] == '>'))
			i++;
		if (s[i] && s[i] == '&')
			i++;
		if (s[i] && ft_is_space(s[i]))
			i = ft_skip_spaces(s, i);
		while (s[i] && s[i] != '|' && !ft_is_space(s[i]))
			i++;
	}
	else if (s[i] == '<' || s[i] == '>')
	{
		while (s[i] && (s[i] != '<' || s[i] != '>'))
			i++;
		if (s[i] == '&')
			i++;
		if (s[i] && ft_is_space(s[i]))
			i = ft_skip_spaces(s, i);
		while (s[i] && s[i] != '|' && !ft_is_space(s[i]))
			i++;
	}
	return (i);
}

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

char *rm_redi_utils2(char *s, int *j)
{
	int		start;
	int		cur;
	char	*ret;

	start = *j;
	cur = start;
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
	cur = rm_skip_redi_stuff(s, cur);
	*j = cur;
	return (ret);
}

char	*rm_redi_utils(char *s, int *j)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = *j;
	tmp1 = rm_redi_utils2(s, &i);//i increments till redi info
	if (!tmp1)
		return (NULL);
	i = rm_skip_redi_stuff(s, i);
	if (s[i] && ft_is_space(s[i]))
		i = ft_skip_spaces(s, i);
	if (s[i] && s[i] == '|')
	{

		tmp2 = ft_strdup("|");
		tmp1 = ft_strjoin_free(tmp1, tmp2);
		free(tmp2);
		i++;
	}
	*j = i;
	return (tmp1);
}
