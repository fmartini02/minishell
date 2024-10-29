/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_amper_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:40:17 by francema          #+#    #+#             */
/*   Updated: 2024/10/29 18:37:40 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	amper_utils(t_redi *redi, int i, int id)
{
	char	*s;

	s = redi->s;
	redi->file = ft_get_word_from_indx(s, i + 1);
	if (ft_atoi(redi->file) < 0)
	{
		printf("minishell: %s: Bad file descriptor\n", redi->file);
		redi->ret_code = INPUTS_ERR;
		return ;
	}
	if (!redi->file || !redi->file[0])
		redi->ret_code = SYNTX;//check if the file name is valid
	if (!redi->ret_code && id == STDIN_FILENO)//< case
		redi->fd = open((const char *)redi->file, O_RDONLY);
	else if (!redi->ret_code && id == STDOUT_FILENO)//> case
		redi->fd = open((const char *)redi->file, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (!redi->ret_code && redi->fd == -1)//fd check
		redi->ret_code = OPEN_ERR;
	if (!redi->ret_code)
		redi->cur_i = ft_next_char_indx(s, i, ' ');
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
	if (s[i - 2] >= '0' && s[i - 2] <= '9')
		close(STDIN_FILENO);//previusly opened fd is now in stdin
}
