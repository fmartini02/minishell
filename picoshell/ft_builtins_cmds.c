/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:28:03 by francema          #+#    #+#             */
/*   Updated: 2024/10/30 17:03:56 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_a_builtin(t_tok *tok, int i)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(tok->cmds_args[i][0], "cd") || !ft_strcmp(tok->cmds_args[i][0], "echo")
		|| !ft_strcmp(tok->cmds_args[i][0], "pwd") || !ft_strcmp(tok->cmds_args[i][0], "export")
		|| !ft_strcmp(tok->cmds_args[i][0], "env") || !ft_strcmp(tok->cmds_args[i][0], "unset")
		|| !ft_strcmp(tok->cmds_args[i][0], "exit") || !ft_strcmp(tok->cmds_args[i][0], "clear"))
		ret = 1;
	return (ret);
}

void	ft_redirect_last_child(t_tok *tok, char **args)
{
	int i;

	i = 0;
	if (!ft_strcmp(args[i], "echo"))
			printf("%s", ft_echo(tok, args));
		else if (!ft_strcmp(args[i], "pwd"))
			printf("%s", ft_pwd(tok));
		else if (!ft_strcmp(args[i], "env"))
			printf("%s", ft_env(tok, args));
		else if (!ft_strcmp(args[i], "cd") || !ft_strcmp(args[i], "export")
			|| !ft_strcmp(args[i], "unset") || !ft_strcmp(args[i], "exit")
			|| !ft_strcmp(args[i], "clear"))
		{
			tok->builtin_flag = 0;
			return ;
		}
}

char	*ft_redirect_utils(t_tok *tok, char **args)
{
	char	*output;
	int		j;

	j = 0;
	if (!ft_strcmp(args[j], "echo"))
			output = ft_echo(tok, args);
	else if (!ft_strcmp(args[j], "pwd"))
		output = ft_pwd(tok);
	else if (!ft_strcmp(args[j], "env"))
		output = ft_env(tok, args);
	else if (!ft_strcmp(args[j], "cd") || !ft_strcmp(args[j], "export")
		|| !ft_strcmp(args[j], "unset") || !ft_strcmp(args[j], "exit")
		|| !ft_strcmp(args[j], "clear"))
	{
		tok->builtin_flag = 0;
		return (NULL);
	}
	else
		return (NULL);
	return (output);
}

void	ft_redirect_builtin_output(t_tok *tok, char **args)
{
	char	*output;

	if (tok->last_child_flag == 1)
		ft_redirect_last_child(tok, args);
	else
	{
		output = ft_redirect_utils(tok, args);
		if (output)
		{
			write(tok->pipes[tok->i][WRITE_END], output, ft_strlen(output));
			free(output);
		}
	}
}

int	ft_builtins_cmds(t_tok *tok, char **args)
{
	if (tok->pipe_flag == 1)
		return (0);
	if (!ft_strcmp(args[0], "echo") && args[1] && !ft_strcmp(args[1], "-n"))
		ft_putstr(ft_echo(tok, args));
	else if (!ft_strcmp(args[0], "pwd"))
		printf("%s\n", ft_pwd(tok));
	else if (!ft_strcmp(args[0], "env"))
		printf("%s", ft_env(tok, args));
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(tok, args);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(tok, args);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(tok, args);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(tok, args);
	else if (!ft_strcmp(args[0], "clear"))
		ft_clear(tok);
	else
	{
		tok->builtin_flag = 0;
		return (0);
	}
	return (1);
}


