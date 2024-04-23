/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:30:54 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/23 18:13:51 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_args_counting(t_tok *tok)
{
	int	i;
	int	n_args_str;
	char	*line;

	i = 0;
	n_args_str = 0;
	line = tok->str_line;
	while (line[i] && (line[i] != '|'))// cycle to count args
	{
		i = ft_skip_spaces(line, i);
		while (line[i] && line[i] != ' ' && line[i] != '\t')//skip args
		{
			if (line[i] == '"')
			{
				i++;//skip first "
				while (line[i] != '"')
					i++;// skip chars till last "
				i++;// skip last "
				break;// break cycle for add 1 to tmp
			}
			i++;
		}
		if (line[i])
			n_args_str++;
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

void	ft_pipe_utils(t_tok *tok, int *pip, int i, char *path, char **args, char **env)
{
	while (1)
	{
		if (ft_matlen((void**)tok->cmds) == 1) //if there is only one command
		{
			//printf("executing %s\n", path);
			execve(path, args, env);//getting args and executing
			ft_perror(tok, "execve failed", 1);
		}
		else if (i == 0 && ft_matlen((void**)tok->cmds) > 1)
			ft_first_child(tok, pip, path, args, env);
		else if (i < (ft_matlen((void**)tok->cmds) - 1))
			ft_succ_childs(tok, pip, path, args, env);
		else
			ft_last_child(tok, pip, path, args, env);
	}
}

