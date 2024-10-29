/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_args_pop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:30:54 by fmartini          #+#    #+#             */
/*   Updated: 2024/10/15 16:21:30 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_dq_pop_utils(int *i, char *line)
{//function to pop double quotes parameters
	int		tmp_i;
	char	*tmp;
	int		j;

	j = *i + 1;// skip first "
	tmp = malloc (sizeof (char) * (ft_strlen_till_char(line, j, '"') + 1));//allocating memory for args
	tmp_i = 0;
	while (line[j] != '"' && line[j] != '\0')
		tmp[tmp_i++] = line[(j)++];//populating args
	tmp[tmp_i] = '\0';//putting end of string
	j++;//skip last "
	*i = j;
	return (tmp);
}

char	*ft_q_pop_utils(int *i, char *line)
{//function to pop single quotes parameters
	int		tmp_i;
	char	*tmp;
	int		j;

	tmp_i = 0;
	j = *i + 1;// skip first '
	tmp = malloc (sizeof (char) * (ft_strlen_till_char(line, j, '\'') + 3));// + 3 bcs of ' char and null byte
	if (!tmp)
		return (NULL);
	while (line[j] != '\'' && line[j] != '\0')
		tmp[tmp_i++] = line[(j)++];//populating args
	tmp[tmp_i] = '\0';//putting end of string
	j++;//skip last '
	*i = j;
	return (tmp);
}

char	*ft_w_pop_utils(int *i, char *line)
{//function to pop normal parameters
	int		tmp_i;
	char	*tmp;
	int		j;

	j = ft_skip_spaces(line, *i);// skip spaces
	if (line[j])
		tmp = malloc (sizeof (char) * (ft_strlen_till_char(line, j, ' ') + 1));//allocating memory for args
	else
		return (NULL);
	tmp_i = 0;
	while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '|')
		tmp[tmp_i++] = line[j++];//populating args
	tmp[tmp_i] = '\0';//putting end of string
	*i = j;
	return (tmp);
}

char	*ft_extract_cmd_name(const char *s, int *i)
{
	int		j;
	char	*cmd;

	j = *i;
	if (s[j])
	{
		if (s[j] == '|')
			j++;
		j = ft_skip_spaces((char *)s, j);
		if (s[j])
		{
			if (s[j] && (s[j] == '\'' || s[j] == '"'))
				cmd = ft_extract_quote_case(s, &j);
			else//in both cases j will go to the next '|'
				cmd = ft_extract_utils(s, &j);
		}
	}
	*i = j;
	return (cmd);
}

char	**ft_get_cmds_names_from_line(t_tok *tok)
{
	int		i;
	int		i_mat;
	char	**cmds_name;

	i_mat = 0;
	i = 0;
	if (!ft_count_cmds(tok))//syntax error or no cmd
	{
		cmds_name = malloc (sizeof (char *) * 2);
		if (!cmds_name)
			perror("malloc error in ft_get_cmds_names_from_line");
		cmds_name[0] = ft_strdup(" \0");
		cmds_name[1] = NULL;
		return (cmds_name);
	}
	cmds_name = malloc (sizeof (char *) * (ft_count_cmds(tok) + 1));// memory allocation for cmds names
	if (!cmds_name)
		perror("malloc error in ft_get_cmds_names_from_line");
	while (tok->str_line[i] != '\0')
	{
		cmds_name[i_mat] = ft_extract_cmd_name(tok->str_line, &i);
		i_mat++;
	}
	cmds_name[i_mat] = NULL;// putting end of matrix
	return (cmds_name);
}

