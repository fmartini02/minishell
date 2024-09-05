/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:43:48 by francema          #+#    #+#             */
/*   Updated: 2024/09/05 17:15:19 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_absolute_path(char *arg)
{
	if (chdir(arg) != 0)
		perror("chdir failed");
}

void	handle_parent_directory(char *path)
{
	char	*tmp;

	ft_dotdot_case(path);
	tmp = ft_strtrim(path, ".");
	if (chdir(tmp) != 0)
		perror("chdir failed");
	free(tmp);
}

void	handle_relative_path(char *arg, char *path)
{
	char	*tmp;

	tmp = ft_strjoin(path, arg + 1); // Skip leading '.'
	if (chdir(tmp) != 0)
		perror("chdir failed");
	free(tmp);
}

void	handle_env_variable(char *arg)
{
	char	*tmp;
	char	*doll;

	doll = ft_doll_case(arg, 0);
	if (doll)
	{
		tmp = ft_strjoin(doll, arg + ft_strlen(doll)); // Concatenate expanded value
		if (chdir(tmp) != 0)
			perror("chdir failed");
		free(tmp);
	}
}

void	handle_default_case(char *arg)
{
	if (chdir(arg) != 0)
		perror("chdir failed");
}
