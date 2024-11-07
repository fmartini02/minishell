/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:48:28 by francema          #+#    #+#             */
/*   Updated: 2024/11/07 16:18:59 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redi_presence(char *args)
{
	int	j;
	int	ret;

	j = 0;
	while(args[j])
	{
		if (args[j] == '>' || args[j] == '<')
			ret = 1;
		j++;
	}
	return (ret);
}

int	ft_find_redi_indx(char *args)
{
	int	i;

	i = 0;
	while(args[i])
	{
		if (args[i] == '<' || args[i] == '>')
			return (i);
		i++;
	}
	return (-1);
}

void	redi_error_msgs(t_redi *redi)
{
	if (redi->ret_code == SYNTX)
		perror("minishell: syntax error near unexpected token `newline'\n");
	else if (redi->ret_code == OPEN_ERR)
		perror("minishell: open error");
	else if (redi->ret_code == DUP_ERR)
		perror("minishell: dup error");
	else if (redi->ret_code == DUP2_ERR)
		perror("minishell: dup2 error");
	else if (redi->ret_code == ITOA_ERR)
		perror("minishell: itoa error");
}

void	fd_bf_redi(t_redi *redi, int i)
{
	char	*s;
	int		fd;

	s = redi->s;
	fd = -1;
	while (i >= 0 && s[i] >= '0' && s[i] <= '9')
		i--;
	fd = ft_atoi(&s[i]);
	redi->fd_before = fd;
}
