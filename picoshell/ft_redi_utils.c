/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redi_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:51:10 by francema          #+#    #+#             */
/*   Updated: 2024/10/07 17:39:49 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_redi_get_file(char *s)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ret)
		return (NULL);
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
		ret[j++] = s[i++];
	ret[j] = '\0';
	return (ret);
}

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

int	ft_fd_bf_redi_utils(t_tok *tok, int fd)
{
	if (fd != -1 && tok->pipe_flag == 1)
		tok->pipes[tok->i][READ_END] = fd;
	else if (fd != -1 && tok->pipe_flag == 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("minishell: dup2 error");
		return (1);
	}
	return (0);
}
