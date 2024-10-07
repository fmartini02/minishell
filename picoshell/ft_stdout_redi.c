/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdout_redi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:43:00 by francema          #+#    #+#             */
/*   Updated: 2024/10/07 18:37:47 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_stdout_append_case(char *s, int *j, t_tok *tok)
{
	int		fd;
	char	*file;

	fd = 0;
	if (s[*j] == '>' && s[*j + 1] == '>')//stdout appending case
	{
		file = ft_redi_get_file(&s[ft_skip_spaces(s, *j)]);
		if (!file || !*file)
		{
			perror("minishell: syntax error near unexpected token `newline'");
			return (1) ;
		}
		fd = open(file , O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (fd != -1 && tok->pipe_flag == 1)
		tok->pipes[tok->i][WRITE_END] = fd;//command will write to the file instead of the pipe
	else if (fd != -1 && tok->pipe_flag == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)//command will write to the file instead of the stdout
			perror("minishell: dup2 error");
	}
	return (0);
}

int	ft_stdout_trunc_case(char *s, int *j, t_tok *tok)
{
	int		fd;
	char	*file;

	fd = 0;
	if (s[*j] == '>' && s[*j + 1] && s[*j + 1] != '>')//stdout truncating case
	{
		(*j)++;//to skip the '>'
		file = ft_redi_get_file(&s[ft_skip_spaces(s, *j)]);
		if (!file || !*file)
		{
			perror("minishell: syntax error near unexpected token `newline'");
			return (1);
		}
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd != -1 && tok->pipe_flag == 1)
		tok->pipes[tok->i][WRITE_END] = fd;//command will write to the file instead of the pipe
	else if (fd != -1 && tok->pipe_flag == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)//command will write to the file instead of the stdout
			perror("minishell: dup2 error");
	}
	else
		tok->pipes[tok->i][WRITE_END] = 0;
	return (0);
}

int	ft_stdout_fd_bf_redi(char *s, int *j, t_tok *tok)
{
	int		fd;
	int		fd_to_open;
	char	*file;

	fd = 0;
	if ((*j - 1) >= 0 && s[*j - 1] >= '0' && s[*j - 1] <= '9')//stdout fd before '>' case
	{
		while(*j >= 0 && s[*j] >= '0' && s[*j] <= '9')
			(*j)--;
		fd_to_open = ft_atoi(&s[*j]);
		file = ft_itoa(fd_to_open);
		if (!file || !*file)
		{
			perror("minishell: syntax error near unexpected token `newline'");
			return (1);
		}
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ft_fd_bf_redi_utils(tok, fd))
			return (1);
		while(s[*j] && s[*j] != '<')//setting j to the beginning of the file name
			(*j)++;
	}
	return (0);
}

int	ft_stdout_ampersand_case(char *s, int *j, t_tok *tok)
{
	int		fd;
	int		fd_to_open;
	char	*file;

	if (s[*j + 1] == '&' && s[*j + 2]
			&& s[*j + 2] >= '0' && s[*j + 2] <= '9')
		fd_to_open = ft_atoi(&s[*j + 2]);
	file = ft_itoa(fd_to_open);
	if (!file || !*file)
	{
		perror("minishell: syntax error near unexpected token `newline'");
		return (1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd != -1 && tok->pipe_flag == 1)
		tok->pipes[tok->i][WRITE_END] = fd;
	else if (fd != -1 && tok->pipe_flag == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror("minishell: dup2 error");
		return (1);
	}
	return (0);
}

int	ft_stdout_redi(t_tok *tok, char *s, int *j)
{
	int		ret;

	ret = 0;
	while (s[*j] && s[*j] != '|')//till the end of the line or the next pipe
	{
		if (s[*j] == '>' && s[*j + 1] == '>')//stdout appending case
			ret = ft_stdout_append_case(s, j, tok);
		else if (s[*j] == '>' && s[*j + 1] && s[*j + 1] != '>')//stdout truncating case
			ret = ft_stdout_trunc_case(s, j, tok);
		if (s[*j + 1] == '&' && s[*j + 2]//> & <fd> case
				&& s[*j + 2] >= '0' && s[*j + 2] <= '9')
			ret = ft_stdout_ampersand_case(s, j, tok);
		else if ((s[*j + 1] == '&' && s[*j + 2] && !(s[*j + 2] >= '0'
			&& s[*j + 2] <= '9')) || ft_atoi(&s[*j + 2]) < 0)//negative fd case
		{
			printf("%s: %s: Bad file descriptor",tok->cmds_args[tok->i][0], ft_get_word_from_indx(s, *j));
			return (1);
		}
		if ((*j - 1) >= 0 && s[*j - 1] >= '0' && s[*j - 1] <= '9')//stdout fd before '>' case
			ret = ft_stdout_fd_bf_redi(s, j, tok);
		(*j)++;
	}
	return (ret);
}
