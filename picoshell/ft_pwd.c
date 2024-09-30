/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:34:20 by francema          #+#    #+#             */
/*   Updated: 2024/09/30 15:12:05 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd(t_tok *tok)
{
	char	*buf;

	if (!tok)
	{
		perror("ft_pwd: tok is NULL");
		return (NULL);
	}
	buf = malloc(sizeof(char) * PATH_MAX);
	if (!buf)
	{
		perror("malloc failed");
		tok->builtin_flag = 0;
		return (NULL);
	}
	if(!getcwd(buf, PATH_MAX))
	{
		perror("getcwd failed");
		tok->builtin_flag = 0;
		free(buf);
		return (NULL);
	}
	tok->builtin_flag = 1;
	return (buf);
}
