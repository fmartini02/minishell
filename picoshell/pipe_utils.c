/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:30:54 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/09 17:43:30 by fmartini         ###   ########.fr       */
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

int	ft_count_args_str(t_tok *tok)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 1;
	while (tok->str_line[i])
	{
		while(tok->str_line[i] && (tok->str_line[i] == ' ' || tok->str_line[i] == '\t')) // skipping spaces
			i++;
		while(tok->str_line[i] && (tok->str_line[i] != ' ' && tok->str_line[i] != '\t'))// skipping first word
			i++;
		while(tok->str_line[i] && (tok->str_line[i] != '|'))// skipping till '|' char
			i++;
		if (tok->str_line[i] == '|')
		{
			tmp += 1;
			i++;
		}
	}
	return (tmp);
}

int	ft_give_num_args(char *line, int i)
{
	int	tmp;

	tmp = 0;
	while(line[i] && (line[i] != '|'))// cycle to count args
	{
		while(line[i] && (line[i] == ' ' || line[i] == '\t'))// skipping spaces
			i++;
		while(line[i] && (line[i] != ' ' && line[i] != '\t'))// counting args
		{
			tmp++;
			while(line[i] && (line[i] != ' ' && line[i] != '\t'))// skipping args
				i++;
		}
	}
	return (tmp);
}

void	ft_pipe_utils(t_tok *tok, int *pip, int *i, char **env)
{
	while (1)
	{
		if (ft_matlen((void**)tok->cmds) == 1) //if there is only one command
		{
			ft_last_child(tok, pip, *i, env);
			break;
		}
		else if (*i == 0)
			ft_first_child(tok, pip, *i, env);
		else if (*i < (ft_matlen((void**)tok->cmds) - 1))
			ft_succ_childs(tok, pip, *i, env);
		else
		{
			ft_last_child(tok, pip, *i, env);
			break;
		}
		(*i)++;
	}
}

char *const *ft_exec_args(char *args, t_tok *tok)
{
	char	**exec;
	char	*tmp;
	int		i;
	int		y;

	i = 0;
	y = 0;
	exec = malloc(sizeof(char *) * ft_give_num_args(args, 0) + 1);// memory allocation for exec args
	if (!exec)
		ft_perror(tok, "exec memory allocation failed", 1);
	while (args[i])
	{
		i = ft_skip_spaces(args, i);
		tmp = malloc(sizeof(char) * ft_strlen_till_char(args, 0, ' ') + 1);// memory allocation for tmp
		if (!tmp)
			ft_perror(tok, "tmp (ft_exec_args) memory allocation failed", 1);
		tmp = ft_strcpy_till_char(tmp, args, i, ' ');// copying args in tmp
		exec[y++] = tmp;// putting args in exec
	}
	exec[y] = NULL;
	return ((char*const*)exec);
}
