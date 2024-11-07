/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_args_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:58:40 by francema          #+#    #+#             */
/*   Updated: 2024/11/05 18:46:24 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_populate_mtx(t_tok *tok, char **args_mat, int *j)
{
	char	*line;
	int		i_mat;
	int		i;

	line = tok->str_line;
	i_mat = 0;
	i = *j;
	while (line[i] && (line[i] != '|'))// cycle to populate args_mat
	{
		i = ft_skip_spaces(line, i);// skip spaces
		if (line[i] == '"')
			args_mat[i_mat] = ft_dq_pop_utils(&i, line);//double quotes case populating
		else if (line[i] == '\'')
			args_mat[i_mat] = ft_q_pop_utils(&i, line);// single quotes case populating
		else if (line[i] != '|')
			args_mat[i_mat] = ft_w_pop_utils(&i, line);// normal case populating
		i_mat++;
		i = ft_skip_spaces(line, i);// skip spaces
	}
	*j = i;
	args_mat[i_mat] = NULL;//putting end of matrix
	return (args_mat);
}

int	**ft_init_pipes(t_tok *tok)
{
	int	**pip;
	int	i;

	i = 0;
	//printf("ft_count_cmds(tok) = %d + 1 \n", ft_count_cmds(tok));
	pip = malloc (sizeof (int *) * (ft_count_cmds(tok) + 1));//allocating memory for pipes + null
	if (!pip)
		perror("malloc error in ft_init_pipes");
	while (i < (ft_count_cmds(tok)))
	{
		pip[i] = malloc (sizeof (int) * 2);//allocating memory for pipe
		if (!pip[i])
			perror("malloc error in ft_init_pipes");
		pipe(pip[i]);//creating pipe
		i++;
	}
	pip[i] = NULL;
	return (pip);
}
