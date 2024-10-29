/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_stdout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:43:00 by francema          #+#    #+#             */
/*   Updated: 2024/10/29 18:17:26 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stdout_append_case(t_redi *redi, int i)
{
	char	*s;

	s = redi->s;
	redi->file = ft_get_word_from_indx(s, i + 1);
	if (!redi->file || !redi->file[0])//STANDARD FILE CHECK
		redi->ret_code = SYNTX;
	if (!redi->ret_code)
		redi->fd = open(redi->file, O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (!redi->ret_code && redi->fd == -1)//STANDARD FD CHECK
		redi->ret_code = OPEN_ERR;
	if (read(redi->fd, NULL, 0) == -1)
	{
		printf("minishell: %s: Bad file descriptor\n", redi->file);
		redi->ret_code = INPUTS_ERR;
	}
	else if (!redi->ret_code && redi->fd != -1)
	{
		close(STDOUT_FILENO);
		if (dup(redi->fd) == -1)//command will write to the file instead of the stdout
			redi->ret_code = DUP_ERR;
	}
	free(redi->file);
	redi->cur_i = ft_next_char_indx(s, i, ' ');
}

void	stdout_trunc_case(t_redi *redi, int i)
{
	char	*s;

	s = redi->s;
	if (ft_is_space(s[i]))
		i = ft_skip_spaces(s, i);
	redi->file = ft_get_word_from_indx(s, i);
	if (!redi->file || !redi->file[0])//STANDARD FILE CHECK
		redi->ret_code = SYNTX;
	if (!redi->ret_code)
		redi->fd = open(redi->file, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (!redi->ret_code && redi->fd == -1)//STANDARD FD CHECK
		redi->ret_code = OPEN_ERR;
	else if (!redi->ret_code && redi->fd != -1)
	{
		close(STDOUT_FILENO);
		if (dup(redi->fd) == -1)//command will write to the file instead of the stdout
			redi->ret_code = DUP_ERR;
	}
	free(redi->file);
	redi->cur_i = ft_next_char_indx(s, i, ' ');
}

void	stdout_ampersand_case(t_redi *redi , int i)
{//i is to '&'
	char	*s;

	s = redi->s;
	if (ft_is_space(s[i + 1]))
		i = ft_skip_spaces(s, i + 1);
	if (s[i + 1] == '-')
	{
		amper_neg_sign(redi, i);
		if (redi->ret_code)
			return ;
	}
	if (s[i])
		amper_utils(redi, i, STDOUT_FILENO);
	if (!redi->ret_code)
	{
		close(STDIN_FILENO);
		if (dup(redi->fd) == -1)
			redi->ret_code = DUP_ERR;
	}
}

int	redi_stdout(t_redi *redi)
{
	char	*s;
	int		i;

	i = redi->cur_i;
	s = redi->s;
	if (redi_check_inputs(redi, i))
		return (1);
	if (s[i - 1] >= '0' && s[i - 1] <= '9')
		fd_bf_redi(redi, i);
	if (s[i] == '>' && s[i + 1] && s[i + 1] == '>')//>> case
		stdout_append_case(redi, i + 1);
	else if (s[i + 1] && s[i + 1] == '&' )//>& case
		stdout_ampersand_case(redi, i + 1);
	else if (s[i] == '>' && s[i + 1] && s[i + 1] != '>')//> case
		stdout_trunc_case(redi, i + 1);
	if (redi->ret_code)
	{
		redi_error_msgs(redi);
		return (1);
	}
	redi->ret_code = 0;
	return (0);
}
