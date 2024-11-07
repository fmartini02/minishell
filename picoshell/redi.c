/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:09:21 by francema          #+#    #+#             */
/*   Updated: 2024/11/07 15:47:00 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_redi(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '<' || s[i] == '>')
			count++;
		i++;
	}
	return (count);
}

t_redi	*init_redi(t_tok *tok)
{
	t_redi	*redi;
	char	*s;

	s = tok->str_line;
	redi = malloc(sizeof(t_redi));
	if (!redi)
	{
		perror("minishell: malloc error");
		return (NULL);
	}
	redi->fd_after = -1;
	redi->fd_before = -1;
	redi->id = -1;
	redi->tok = tok;
	redi->file = NULL;
	redi->ret_code = 0;
	redi->s = ft_strdup(s);
	redi->n_redi = ft_count_redi(s);
	redi->cur_i = ft_find_redi_indx(s);
	return (redi);
}

int	redi_exe_utils(t_redi *redi, int i)
{
	if (redi->s[i] == '<')
	{
		redi->fd_before = STDIN_FILENO;
		redi->id = STDIN_FILENO;
		if (redi_stdin(redi))
			return (1);
	}
	else if (redi->s[i] == '>')
	{
		redi->fd_before = STDOUT_FILENO;
		redi->id = STDOUT_FILENO;
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


int	redi_case(t_tok *tok)
{
	int		i;
	t_redi	*redi;

	i = 0;
	redi = init_redi(tok);
	if (redi_exe(redi))
		return (1);
	tok->str_line = rm_redi(redi);
	i = redi->cur_i;
	if (redi->s[i] != '<' && redi->s[i] != '>')
	{
		free_cmds_args(tok);
		free_cmds(tok);
		tok->cmds_args = ft_set_cmds_args(tok);
		tok->cmds = ft_get_cmds_names_from_line(tok);
	}
	return (0);
}
