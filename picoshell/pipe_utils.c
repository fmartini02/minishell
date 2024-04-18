/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:30:54 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/18 16:54:39 by fmartini         ###   ########.fr       */
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

int	ft_args_strlen(t_tok *tok)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 1;
	while (tok->str_line[i] && (tok->str_line[i] != '|'))// cycle to count args
	{
		i = ft_skip_spaces(tok->str_line, i);
		while (tok->str_line[i] && tok->str_line[i] != ' ' && tok->str_line[i] != '\t')//skip args
			i++;
		tmp++;
	}
	return (tmp);
}

char	**parse_tokens(t_tok *tok, char **args_mat, int *i, int *i_mat)
{
	int		j;
	char	*args;

	j = 0;
	while (tok->str_line[*i])
	{
		args = malloc(sizeof(char) * ft_strlen_till_char(tok->str_line, *i, ' ') + 1);
		if (!args)
			ft_perror(tok, "malloc error in parse_tokens", 1);
		while (tok->str_line[*i] && tok->str_line[*i] != '|' && tok->str_line[*i] != ' ')
			args[j++] = tok->str_line[(*i)++];
		if (j != 0)
		{
			args[j] = '\0';
			args_mat[(*i_mat)++] = args;
		}
		j = 0;
		if (tok->str_line[*i] != '\0' && tok->str_line[*i] == '|')
		{
			args_mat[*i_mat] = NULL;
			(*i)++;
			break;
		}
		if (!tok->str_line[*i])
			break;
		(*i)++;
	}
	return (args_mat);
}

void	ft_pipe_utils(t_tok *tok, int *pip, int i, char *path, char **args, char **env)
{
	//printf("|\nargs ft_pipe_utils: %s\n|\n", args[1]);
	while (1)
	{
		if (ft_matlen((void**)tok->cmds) == 1) //if there is only one command
		{
			printf("executing %s\n", path);
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

