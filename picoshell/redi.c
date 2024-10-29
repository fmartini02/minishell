/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:09:21 by francema          #+#    #+#             */
/*   Updated: 2024/10/29 18:21:03 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	redi_exe_utils(t_redi *redi, int i)
{
	if (redi->s[i] == '<')
	{
		if (redi_stdin(redi))
			return (1);
	}
	else if (redi->s[i] == '>')
	{
		if (redi_stdout(redi))
			return (1);
	}
	return (0);
}

int	redi_exe(t_redi *redi)
{
	int		i;
	char	*s;

	i = redi->cur_i;
	s = redi->s;
	while(s[i] && s[i] != '|')
	{
		if (redi_exe_utils(redi, i))
			return (1);
		i = redi->cur_i;//to update the index
		if(s[i] && !ft_is_space(s[i]))
			i++;
		if (s[i] && ft_is_space(s[i]))
			i = ft_skip_spaces(s, i);
		while (s[i] && s[i] >= '0' && s[i] <= '9')
			i++;
		if ((s[i] && s[i] != '<' && s[i] != '>') || !s[i])
			return (0);
		else
			redi->cur_i = i;
	}
	return (0);
}

t_redi	*init_redi(t_tok *tok)
{
	t_redi	*redi;

	redi = malloc(sizeof(t_redi));
	if (!redi)
	{
		perror("minishell: malloc error");
		return (NULL);
	}
	redi->fd = -1;
	redi->cur_i = ft_find_redi_indx(tok->str_line);
	redi->ret_code = 0;
	redi->s = ft_strdup(tok->str_line);
	redi->file = NULL;
	redi->tok = tok;
	return (redi);
}

int	redi_case(t_tok *tok)
{
	int		i;
	t_redi	*redi;

	i = 0;
	redi = init_redi(tok);
	if (redi_exe(redi))
		return (1);
	tok->str_line = rm_redi(redi);
	if (redi->s[i] != '<' && redi->s[i] != '>')
	{
		ft_free_cmds_args(tok);
		tok->cmds_args = ft_set_cmds_args(tok);
	}
	return (0);
}
