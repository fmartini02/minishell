/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_args_pop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:30:54 by fmartini          #+#    #+#             */
/*   Updated: 2024/05/01 15:54:48 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_dq_pop_utils(int *i, char *line)//function to pop double quotes parameters
{
	int		tmp_i;
	char	*tmp;

	tmp = malloc (sizeof (char) * (ft_strlen_till_char(line, *i, '"') + 1));//allocating memory for args
	tmp_i = 0;
	(*i)++;// skip first "
	while (line[*i] != '"' && line[*i] != '\0')
		tmp[tmp_i++] = line[(*i)++];//populating args
	tmp[tmp_i] = '\0';//putting end of string
	(*i)++;//skip last "
	return (tmp);
}

char	*ft_q_pop_utils(int *i, char *line)//function to pop single quotes parameters
{
	int		tmp_i;
	char	*tmp;

	tmp_i = 0;
	tmp = malloc (sizeof (char) * (ft_strlen_till_char(line, *i, '\'') + 3));// + 3 bcs of ' char and null byte
	if (!tmp)
		return (NULL);
	(*i)++;// skip first '
	//tmp[tmp_i++] = '\'';
	while (line[*i] != '\'' && line[*i] != '\0')
		tmp[tmp_i++] = line[(*i)++];//populating args
	//tmp[tmp_i++] = '\'';
	tmp[tmp_i] = '\0';//putting end of string
	(*i)++;//skip last '
	return (tmp);
}

char	*ft_w_pop_utils(int *i, char *line)//function to pop normal parameters
{
	int		tmp_i;
	char	*tmp;

	*i = ft_skip_spaces(line, *i);// skip spaces
	if (line[*i])
		tmp = malloc (sizeof (char) * (ft_strlen_till_char(line, *i, ' ') + 1));//allocating memory for args
	else
		return (NULL);
	tmp_i = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t')//populating args
		tmp[tmp_i++] = line[(*i)++];
	tmp[tmp_i] = '\0';//putting end of string
	return (tmp);
}

char	**ft_get_cmds_names_from_line(t_tok *tok)
{
	int		i;
	int		i_mat;
	char	**cmds_name;

	i_mat = 0;
	i = 0;
	cmds_name = malloc (sizeof (char *) * (ft_count_cmds(tok) + 1));// memory allocation for cmds names
	if (!cmds_name)//memory allocation check
		ft_perror(tok, "cmds_name memory allocation failed", 1);
	while (tok->str_line[i] != '\0')
	{
		cmds_name[i_mat++] = ft_extract_cmd_name(tok->str_line, &i);
		while (tok->str_line[i] != '|' && tok->str_line[i] != '\0')// skipping till the '|' char
			i++;
	}
	cmds_name[i_mat] = '\0';// putting end of matrix
	return (cmds_name);
}
char	*ft_extract_cmd_name(const char *s, int *i)
{
	int		tmp;
	char	*name;

	tmp = 0;
	*i = ft_skip_spaces((char*)s, *i);// skipping spaces
	name = malloc (sizeof (char) * ft_word_len(s, *i) + 1);// memory allocation for cmd name
	if (!name)
		ft_perror(NULL, "name memory allocation failed", 1);
	if (s[*i] == '|')
	{
		(*i)++;
		*i = ft_skip_spaces((char*)s, *i);
	}
	while(s[*i] != '\0' && s[*i] != ' ' && s[*i] != '\t')// cycle to get cmd name
		name[tmp++] = s[(*i)++];
	name[tmp] = '\0';// putting end of string
	return (name);
}
