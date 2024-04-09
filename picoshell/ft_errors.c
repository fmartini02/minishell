/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:57:26 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/09 16:54:42 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_mem(t_tok *tok)
{
	int i;

	i = 0;
	while (tok->cmds[i])
	{
		free(tok->cmds[i]);
		free(tok->cmds_args[i]);
		i++;
	}
	free(tok->cmds);
	free(tok->cmds_args);
	free(tok->str_line);
}

void	ft_perror(t_tok *tok, char *s, int flag)
{
	perror(s);
	if (flag)
		ft_free_mem(tok);
	exit(EXIT_FAILURE);
}
