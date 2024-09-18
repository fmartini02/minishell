/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:02:10 by francema          #+#    #+#             */
/*   Updated: 2024/09/18 17:11:54 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo_flag_n(char **args)
{
	int	i;

	i = 2;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

void	ft_echo_builtin(t_tok *tok, char **args)
{
	if(!args[0] || !args[1])
		return ;
	if(!ft_strcmp(args[0], "echo") && !ft_strcmp(args[1], "-n"))
	{
		if (args[2])
			ft_echo_flag_n(args);
		tok->builtin_flag = 1;
	}
}
