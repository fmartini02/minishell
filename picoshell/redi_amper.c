/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_amper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:40:17 by francema          #+#    #+#             */
/*   Updated: 2024/11/07 18:12:52 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	amper_utils_2(t_redi *redi)
{
	char	*s;
	int		fd;
	int		id;

	s = redi->file;
	fd = -1;
	id = redi->id;
	if (id == STDIN_FILENO && ft_atoi(s) != STDIN_FILENO)
		fd = open((const char *)s, O_RDONLY);
	else if (id == STDOUT_FILENO && ft_atoi(s) != STDOUT_FILENO)
		fd = open((const char *)s, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	else
		fd = ft_atoi(s);
	redi->fd_after = fd;
}
void	amper_utils(t_redi *redi, int i)
{// s[i] is '&'
	char	*s;

	s = redi->s;
	redi->file = ft_get_word_from_indx(s, i + 1);
	if (ft_atoi(redi->file) < 0)
	{// if the fd is neg ; if its a word atoi returns 0
		printf("minishell: %s: Bad file descriptor\n", redi->file);
		redi->ret_code = INPUTS_ERR;
		return ;
	}
	if (!redi->file || !redi->file[0])
		redi->ret_code = SYNTX;//check if the file name is valid
	amper_utils_2(redi);
	if (!redi->ret_code && redi->fd_after == -1)//fd check
		redi->ret_code = OPEN_ERR;
	close(redi->fd_before);
	if (dup(redi->fd_after) == -1)//dup2 check
		redi->ret_code = DUP2_ERR;
	if (!redi->ret_code)
		redi->cur_i = i;
	free(redi->file);
}

void	amper_neg_sign(t_redi *redi, int i)
{
	char	*s;

	s = redi->s;
	if (!ft_is_space(s[i + 2]))
	{
		printf("minishell: bad file descriptor\n");
		redi->ret_code = INPUTS_ERR;
		return ;
	}
	if (ft_is_space(s[i + 2]))
	{
		i = ft_skip_spaces(s, i + 2);
		if (s[i] && s[i] != '|')
		{
			printf("minishell: bad file descriptor\n");
			redi->ret_code = INPUTS_ERR;
			return ;
		}
	}
	close(redi->fd_before);
}

void	ampersand_case(t_redi *redi , int i)
{//i is to '&'
	char	*s;

	s = redi->s;
	if (ft_is_space(s[i + 1]))
		i = ft_skip_spaces(s, i + 1);
	if (s[i + 1] == '-' || s[i] == '-')// '&-' and '& -' case
	{
		amper_neg_sign(redi, i);
		return ;
	}
	amper_utils(redi, i);
}
