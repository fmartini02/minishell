/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:28:03 by francema          #+#    #+#             */
/*   Updated: 2024/09/21 18:10:40 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtins_cmds(t_tok *tok, char **args)
{
	if (!ft_strcmp(args[0], "cd"))
		ft_cd_builtin(tok, args);
	else if (!ft_strcmp(args[0], "echo") && args[1])
		ft_echo_builtin(tok, args);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd_builtin(tok);
	else if (!ft_strcmp(args[0], "export"))
		ft_export_builtin(tok, args);
	else if (!ft_strcmp(args[0], "env"))
		ft_env_builtin(tok);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset_builtin(tok, args);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit_builtin(tok, args);
	else if (!ft_strcmp(args[0], "clear"))
		ft_clear_builtin(tok);
	else
	{
		tok->builtin_flag = 0;
		return (0);
	}
	return (1);
}


