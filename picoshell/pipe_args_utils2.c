/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_args_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:58:40 by francema          #+#    #+#             */
/*   Updated: 2024/10/01 15:30:46 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0')
		return (1);
	else
		return (0);
}

char	**ft_populate_mtx(t_tok *tok, char **args_mat, int *i)
{
	char	*line;
	int		i_mat;

	line = tok->str_line;
	i_mat = 0;
	if (ft_only_spaces(line))
	{
		args_mat[i_mat] = ft_strdup(" \0");
		args_mat[i_mat + 1] = NULL;
		return (args_mat);
	}
	while (line[*i] && (line[*i] != '|'))// cycle to populate args_mat
	{
		*i = ft_skip_spaces(line, *i);// skip spaces
		if (line[*i] == '"')
			args_mat[i_mat] = ft_dq_pop_utils(i, line);//double quotes case populating
		else if (line[*i] == '\'')
			args_mat[i_mat] = ft_q_pop_utils(i, line);// single quotes case populating
		else if (line[*i] != '|')
			args_mat[i_mat] = ft_w_pop_utils(i, line);// normal case populating
		i_mat++;
	}
	args_mat[i_mat] = NULL;//putting end of matrix
	return (args_mat);
}

int	**ft_init_pipes(t_tok *tok)
{
	int	**pip;
	int	i;

	i = 0;
	pip = malloc (sizeof (int *) * (ft_count_cmds(tok) + 1));//allocating memory for pipes + null
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
