/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:38:01 by francema          #+#    #+#             */
/*   Updated: 2024/09/26 17:05:23 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_slash(char *path)
{
	int		i;
	int		n_slash;

	i = 0;
	n_slash = 0;
	while (path[i])
	{
		if (path[i] == '/')
			n_slash++;
		i++;
	}
	return (n_slash);
}

void	ft_root_case(void)
{
	if (chdir("/") != 0)
		perror("chdir failed");
}

void	ft_dotdot_case(char *path)
{
	int		len;
	int		slash_count;

	len = 0;
	slash_count = 0;
	if(ft_count_slash(path) == 1)
	{
		ft_root_case();
		return ;
	}
	while(path[len])
	{
		if(slash_count == (ft_count_slash(path) - 1))
		{
			if (chdir(ft_substr(path, 0, len)) != 0)
				perror("chdir failed");
			break;
		}
		if (path[len] == '/')
		{
			slash_count++;
			len++;
		}
		while(path[len] != '/' && path[len])
				len++;
	}
}

void	ft_same_dir_case(char *path)
{
	if (chdir(path) != 0)
		perror("chdir failed");
}

void	ft_user_home_case(char **args)
{
	char	*home;
	char	*path;

	home = getenv("HOME");
	if (!home)
	{
		perror("getenv failed");
		return;
	}
	if (!ft_strcmp(args[1], "~") || !ft_strcmp(args[1], "~/"))
	{
		if (chdir(home) != 0)
			perror("chdir failed");
	}
	else if (args[1][1] >= ' ' && args[1][1] <= '~')
	{
		path = ft_strjoin(home, args[1] + 1);// +1 to skip ~
		if (!path || chdir(path) != 0)
			perror("chdir failed");
		free(path);
	}
}
