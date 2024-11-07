/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:44:46 by francema          #+#    #+#             */
/*   Updated: 2024/11/07 16:19:44 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		redi->fd_after = open((const char *)redi->file, O_RDONLY);
	if (!redi->ret_code && redi->fd_after < 0)
		redi->ret_code = OPEN_ERR;
	if (!redi->ret_code)
	{
		redi->cur_i = ft_next_char_indx(s, i, ' ');
		free(redi->file);
		close(redi->fd_before);
		if (redi->ret_code || dup(redi->fd_after) == -1)
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
	if ( i - 1 >= 0 && s[i - 1] >= '0' && s[i - 1] <= '9')
		fd_bf_redi(redi, i - 1);
	if (s[i] == '<' && s[i + 1] != '<')//stdin normal case
		stdin_normal(redi);
	if (s[i] == '<' && s[i + 1] == '&')
		ampersand_case(redi, i + 1);
	if (redi->ret_code)
	{
		redi_error_msgs(redi);
		return (1);
	}
	return (0);
}
