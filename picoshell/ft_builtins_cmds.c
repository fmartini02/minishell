/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:28:03 by francema          #+#    #+#             */
/*   Updated: 2024/09/05 16:52:49 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtins_cmds(t_tok *tok, char **args)
{
	if (!ft_strcmp(args[0], "cd"))
		ft_cd_builtin(tok, args);
}


