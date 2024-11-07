/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:57:26 by fmartini          #+#    #+#             */
/*   Updated: 2024/10/30 15:51:13 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds_args(t_tok *tok)
{
	int	i;
	int	j;

	i = 0;
	while (tok->cmds_args[i])
	{
		j = 0;
		while (tok->cmds_args[i][j])
			free(tok->cmds_args[i][j++]);
		free(tok->cmds_args[i][j]);//to free the NULL at the end of the matrix
		free(tok->cmds_args[i]);
		i++;
	}
	free(tok->cmds_args);
}

void	free_cmds(t_tok *tok)
{
	int	i;

	i = 0;
	while (tok->cmds[i])
		free(tok->cmds[i++]);
	free(tok->cmds);
}

void	ft_free_mem(t_tok *tok)
{
	int	i;

	i = 0;
	if (tok->str_line)
		free(tok->str_line);
	if (tok->cmds)
		free_cmds(tok);
	if (tok->cmds_args)
		free_cmds_args(tok);
	if (tok->pipes)
	{
		i = 0;
		while (tok->pipes[i])
			free(tok->pipes[i++]);
		free(tok->pipes);
	}
}
void	ft_perror(t_tok *tok, char *s, int flag)
{
	perror(s);
	if (flag)
		ft_free_mem(tok);
	exit(EXIT_FAILURE);
}
