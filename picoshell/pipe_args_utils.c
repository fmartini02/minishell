/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_args_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:24:35 by fmartini          #+#    #+#             */
/*   Updated: 2024/05/02 16:21:09 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	ft_args_counting_utils(char *s, char c, int i)
{
	i++;//skip first "
	while (s[i] != c && s[i] != '\0')
		i++;// skip chars till last "
	i++;// skip last "
	return (i);
}

int	ft_count_cmds(t_tok *tok)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 1;
	while (tok->str_line[i])
	{
		if (tok->str_line[i] == '|')// cycle to count how many cmds there are
			tmp +=1;
		i++;
	}
	return (tmp);
}

int	ft_args_counting(t_tok *tok, int i)
{
	int	n_args_str;
	char	*line;

	n_args_str = 0;
	line = tok->str_line;
	while (line[i] && (line[i] != '|'))// cycle to count args
	{
		i = ft_skip_spaces(line, i);
		while (line[i] && line[i] != ' ' && line[i] != '\t')//skip args
		{
			if (line[i] == '"')
				i = ft_args_counting_utils(line, '"', i);
			if (line[i] == '\'')
				i = ft_args_counting_utils(line, '\'', i);
			i++;
		}
		if (line[i])
			n_args_str++;
		i = ft_skip_spaces(line, i);
	}
	return (n_args_str);
}

char	**ft_populate_mtx(t_tok *tok, char **args_mat, int *i)
{
	char	*line;
	int		i_mat;

	line = tok->str_line;
	i_mat = 0;
	while (line[*i] && (line[*i] != '|'))// cycle to populate args_mat
	{
		*i = ft_skip_spaces(line, *i);// skip spaces
		if (line[*i] == '"')
			args_mat[i_mat++] = ft_dq_pop_utils(i, line);//double quotes case populating
		else if (line[*i] == '\'')
			args_mat[i_mat++] = ft_q_pop_utils(i, line);// single quotes case populating
		else if (line[*i] != '|')
			args_mat[i_mat++] = ft_w_pop_utils(i, line);// normal case populating
	}
	args_mat[i_mat] = NULL;//putting end of matrix
	return (args_mat);
}

int	**ft_init_pipes(t_tok *tok)
{
	int	**pip;
	int	i;

	i = 0;
	pip = malloc (sizeof (int *) * ft_count_cmds(tok) );//allocating memory for pipes + null(n_pip = n_cmds - 1)
	if (!pip)
		ft_perror(tok, "malloc error in ft_init_pipes", 1);
	while (i < (ft_count_cmds(tok)))
	{
		pip[i] = malloc (sizeof (int) * 2);//allocating memory for pipe
		if (!pip[i])
			ft_perror(tok, "malloc error in ft_init_pipes", 1);
		pipe(pip[i]);//creating pipe
		i++;
	}
	pip[i] = NULL;
	return (pip);
}
