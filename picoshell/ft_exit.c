/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:16:14 by francema          #+#    #+#             */
/*   Updated: 2024/09/25 19:31:33 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_args_check(char **args)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	if (ft_matlen((void**)args) > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		ret  = 1;//too many arguments
	}
	else if (ft_matlen((void**)args) == 2)
	{
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
				ret = 2;//there is a non digit character
			i++;
		}
		if (ret == 0)
			ret = 3;//all characters are digits
	}
	return (ret);
}

int	ft_non_digit_exit(char **args)
{
	int	exit_val;

	exit_val = 0;
	if (args[1][0] == '-')
	{
		exit_val = atoi(args[1]);
		while (exit_val < 256)//clamping negative values
			exit_val %= 256;
		exit_val += 256;
	}
	else
	{
		if (args[1][0] >= '0' && args[1][0] <= '9')
			exit_val = atoi(args[1]);
		else
			exit_val = args[1][0];
	}
	return (exit_val);
}

void	ft_exit(t_tok *tok, char **args)
{
	int	ret_err;
	int	exit_val;

	ret_err = ft_exit_args_check(args);
	if (ret_err == 0)//no arguments std exit
		exit_val = 0;
	else if (ret_err == 1)//too many arguments stderr exit
		return ;
	else if (ret_err == 2)//non full digit character exit or negative number
		exit_val = ft_non_digit_exit(args);
	else if (ret_err == 3)//full digit character exit
		exit_val = atoi(args[1]);
	tok->builtin_flag = 1;//to stop execve
	while(exit_val > 255)//if exit value is greater than 255
		exit_val %= 256;
	exit(exit_val);
}
