/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:02:10 by francema          #+#    #+#             */
/*   Updated: 2024/09/25 19:27:41 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_space(char *str)
{
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = ft_strcat_smart(str, " ");
	if (!tmp)
	{
		free(str);
		return (NULL);
	}
	str = tmp;
	return (str);
}

char	*ft_echo_flag_n(char **args)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 2;
	str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	while (args[i])
	{
		tmp = ft_strcat_smart(str, args[i]);
		if (!tmp)
		{
			free(str);
			return (NULL);
		}
		str = tmp;
		if (args[i + 1])
			str = ft_add_space(str);
		i++;
	}
	return (str);
}

char	*ft_echo(t_tok *tok, char **args)
{
	if(!args[0] || !args[1])
		return (NULL);
	if(!ft_strcmp(args[0], "echo") && !ft_strcmp(args[1], "-n"))
	{
		tok->builtin_flag = 1;
		if (args[2])
			return (ft_echo_flag_n(args));
		else
			return (ft_strdup(""));
	}
	tok->builtin_flag = 1;
	return(NULL);
}
