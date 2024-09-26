/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:57:26 by fmartini          #+#    #+#             */
/*   Updated: 2024/09/25 17:59:35 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_mem(t_tok *tok)
{
	int i = 0;
	t_tok *tmp;

	tmp = tok;
	free(tmp->str_line);
	while (tmp->cmds[i])
	{
		free(tmp->cmds[i]);
		free(tmp->cmds_args[i]);
		i++;
	}
	free(tmp->cmds);
	free(tmp->cmds_args);
	free(tmp);
}

void	ft_perror(t_tok *tok, char *s, int flag)
{
	perror(s);
	if (flag)
		ft_free_mem(tok);
	exit(EXIT_FAILURE);
}
