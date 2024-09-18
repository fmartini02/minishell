/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:34:20 by francema          #+#    #+#             */
/*   Updated: 2024/09/18 17:01:57 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd_builtin(t_tok *tok)
{
	char	buf[PATH_MAX];

	if (!tok)
	{
		perror("ft_pwd_builtin: tok is NULL");
		return ;
	}
	if(!getcwd(buf, sizeof(buf)))
	{
		perror("getcwd failed");
		tok->builtin_flag = 1;
	}
	else
		printf("%s\n", buf);
	tok->builtin_flag = 1;
}
