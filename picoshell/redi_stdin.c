/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:44:46 by francema          #+#    #+#             */
/*   Updated: 2024/10/29 18:39:37 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stdin_ampersand(t_redi *redi, int i)
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
		amper_utils(redi, i, STDIN_FILENO);
	if (!redi->ret_code)
	{
		close(STDIN_FILENO);
		if (dup(redi->fd) == -1)
			redi->ret_code = DUP_ERR;
	}
}

void	stdin_normal(t_redi *redi)
{
	char	*s;
	int		i;

	s = redi->s;
	i = redi->cur_i;
	if (ft_is_space(s[i + 1]))
		i = ft_skip_spaces(s, i + 1);
	redi->file = ft_get_word_from_indx(s, i);//checks are inside function
	if (!redi->file)
		redi->ret_code = INPUTS_ERR;
	if (!redi->ret_code)
		redi->fd = open((const char *)redi->file, O_RDONLY);
	if (!redi->ret_code && redi->fd < 0)
		redi->ret_code = OPEN_ERR;
	if (read(redi->fd, NULL, 0) == -1)
	{
		printf("minishell: %s: Bad file descriptor\n", redi->file);
		redi->ret_code = INPUTS_ERR;
	}
	if (!redi->ret_code)
	{
		redi->cur_i = ft_next_char_indx(s, i, ' ');
		free(redi->file);
		close(STDIN_FILENO);
		if (redi->ret_code || dup(redi->fd) == -1)
			redi->ret_code = DUP_ERR;
	}
}

int	redi_stdin(t_redi *redi)
{
	char	*s;
	int		i;

	s = redi->s;
	i = redi->cur_i;
	if (redi_check_inputs(redi, i))
		return (1);
	if (s[i - 1] >= '0' && s[i - 1] <= '9')
		fd_bf_redi(redi, i);
	if (s[i] == '<' && s[i + 1] != '<')//stdin normal case
		stdin_normal(redi);
	if (s[i] == '<' && s[i + 1] == '&')
		stdin_ampersand(redi, i + 1);
	if (redi->ret_code)
	{
		redi_error_msgs(redi);
		return (1);
	}
	redi->ret_code = 0;
	return (0);
}
