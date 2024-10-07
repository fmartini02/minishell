/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin_redi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:44:46 by francema          #+#    #+#             */
/*   Updated: 2024/10/07 16:30:15 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_stdin_fd_bf_redi(char *s, int *j, t_tok *tok)
{
	int		fd;
	int		fd_to_open;
	char	*file;

	fd = 0;
	if (s[*j - 1] >= '0' && s[*j - 1] <= '9')//check to se fd's before '<'
	{
		while(*j >= 0 && s[*j] >= '0' && s[*j] <= '9')//setting i to the beginning of the fd
			(*j)--;
		fd_to_open = ft_atoi(&s[*j]);
		file = ft_itoa(fd_to_open);
		if (!file || !*file)
		{
			perror("minishell: syntax error near unexpected token `newline'");
			return (1);
		}
		fd = open(file, O_RDONLY);
		if (ft_fd_bf_redi_utils(tok, fd))
			return (1);
		while(s[*j] && s[*j] != '<')//setting j to the beginning of the file name
			(*j)++;
	}
	return (0);
}

int	ft_stdin_ampersand_case(char *s, int *j, t_tok *tok)
{
	int		fd;
	int		fd_to_open;
	char	*file;

	if (s[*j + 1] == '&' && s[*j + 2]//> & <fd> case
		&& s[*j + 2] >= '0' && s[*j + 2] <= '9')
		fd_to_open = ft_atoi(&s[*j + 2]);
	file = ft_itoa(fd_to_open);
	if (!file || !*file)
	{
		perror("minishell: syntax error near unexpected token `newline'");
		return (1);
	}
	fd = open(file, O_RDONLY);
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

int	ft_stdin_normal_case(char *s, int *j, t_tok *tok)
{
	int		fd;
	char	*file;

	fd = 0;
	if (s[*j] == '<' && s[*j + 1] && s[*j + 1] != '<')//stdin normal case
	{
		file = ft_redi_get_file(&s[ft_skip_spaces(s, *j)]);
		if (!file || !*file)
		{
			perror("minishell: syntax error near unexpected token `newline'");
			return (1);
		}
		fd = open(file, O_RDONLY);
	}
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

int	ft_stdin_redi(t_tok *tok, char *s, int *j)
{
	int	ret;

	if (s[*j - 1] >= '0' && s[*j - 1] <= '9')
		ret = ft_stdin_fd_bf_redi(s, j, tok);
	while (s[*j] && s[*j] != '|')//till the end of the line or the next pipe
	{
		if (s[*j + 1] == '&' && s[*j + 2]//< & <fd> case
			&& s[*j + 2] >= '0' && s[*j + 2] <= '9')
			ret = ft_stdin_ampersand_case(s, j, tok);
		else if ((s[*j + 1] == '&' && s[*j + 2] && !(s[*j + 2] >= '0'
			&& s[*j + 2] <= '9')) || ft_atoi(&s[*j + 2]) < 0)//negative fd case
		{
			printf("minishell: %s Bad file descriptor", ft_get_word_from_indx(s, *j));
			return (1);
		}
		if (s[*j] == '<' && s[*j + 1] && s[*j + 1] != '<')//stdin normal case
			ret = ft_stdin_normal_case(s, j, tok);
		(*j)++;
	}
	return (ret);
}
