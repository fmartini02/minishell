/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:09:21 by francema          #+#    #+#             */
/*   Updated: 2024/10/07 18:18:10 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_lexer_redi_case(const char *s, int *i, t_tok *tok)
{
	char	*ret;
	int		j;

	j = 0;
	tok->redi_flag = 1;
	ret = malloc(sizeof(char) * (ft_strlen_till_char((char *)s, *i, ' ') + 1));
	if (!ret)
		return (NULL);
	while (s[*i] && s[*i] != ' ')
	{
		ret[j++] = s[(*i)++];
	}
	ret[j] = '\0';
	return (ret);
}

int	ft_rm_redi_utils(char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != '<' && s[i] != '>')
	{
		if (s[i + 1] == '<' || s[i + 1] == '>')//if next char is a redi
		{
			if (s[i] == ' ' || s[i] == '\t')//if the current char is a space
				i++;
			else if (s[i] >= '0' && s[i] <= '9')//if the current car is a fd number
			{
				while (s[i] && s[i] >= '0' && s[i] <= '9')//go to the start of the fd number
					i--;
			}
			break ;//return the index of the beginning of the redi info
		}
		i++;
	}
	return (i);
}

char	*ft_rm_redi(char *s)
{
	char	*ret;
	int		j;

	ret = malloc(sizeof(char) * (ft_rm_redi_utils(s) + 1));
	if (!ret)
		return (NULL);
	j = 0;
	while (s[j] && s[j] != '<' && s[j] != '>')
	{
		ret[j] = s[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

int	ft_redi_case_utils(t_tok *tok, char *args_mat, int *i)
{
	if (args_mat[*i] == '<')
	{
		if (ft_stdin_redi(tok, args_mat, i))
			return (1);
	}
	else if (args_mat[*i] == '>')
	{
		if (ft_stdout_redi(tok, args_mat, i))
			return (1);
	}
	return (0);
}

void	ft_redi_case(t_tok *tok)
{
	char	*line;
	int		i;

	line = tok->str_line;
	i = 0;
	if (!ft_redi_presence(line))
		return ;
	else
	{
		i = ft_find_redi_indx(line);
		if (i < 0)
			return ;
		while(line[i])
		{
			if (ft_redi_case_utils(tok, line, &i))// j increments in the functions
				return ;
		}
		tok->str_line = ft_rm_redi(line);
		if (line[i] != '<' && line[i] != '>')
		{
			ft_free_cmds_args(tok);
			tok->cmds_args = ft_set_cmds_args(tok);
		}
	}
}
