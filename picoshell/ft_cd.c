/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:36:53 by francema          #+#    #+#             */
/*   Updated: 2024/09/21 18:40:53 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_common_case(char **args, char *path)
{
	if (!args[1])
		return;
	if (args[1][0] == '/')// Handle absolute path (starting with '/')
		handle_absolute_path(args[1]);
	else if (args[1][0] == '.' && args[1][1] == '.')// Handle parent directory navigation (../)
		handle_parent_directory(path);
	else if (args[1][0] == '.' && args[1][1] == '/')// Handle relative path starting with ./
		handle_relative_path(args[1], path);
	else if (args[1][0] == '$')// Handle environment variables (e.g., $VAR)
		handle_env_variable(args[1]);
	else// Default case
		handle_default_case(args[1]);
}

void	ft_cd_builtin(t_tok *tok, char **args)
{
	char	path[PATH_MAX];
	(void)tok;

	path[0] = '\0';
	if (!args[1])
	{
		tok->builtin_flag = 1;
		if (chdir(getenv("HOME")) != 0)
			perror("chdir failed");
		return ;
	}
	if (!getcwd(path, sizeof(path)))
		perror("getpath failed");
	if (ft_strcmp (args[1], ".." ) == 0)
		ft_dotdot_case(path);
	else if (!ft_strcmp (args[1], ".") || !ft_strcmp (args[1], "./"))
		ft_same_dir_case(path);
	else if (args[1][0] == '~' || !args[1])
		ft_user_home_case(args);
	else if (!ft_strcmp (args[1], "/"))
		ft_root_case();
	else
		ft_common_case(args, path);
	tok->builtin_flag = 1;
}
