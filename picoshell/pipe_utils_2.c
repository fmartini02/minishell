/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:09:08 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/23 16:25:43 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_first_child(t_tok *tok, int *pipe, char *path, char **args, char **env)
{
	//printf("args first child: %s\n", args[1]);
	//printf("arg 0: %s\n", args[0]);
	//printf("path: %s\n", path);
	if (dup2(pipe[WRITE_END], STDOUT_FILENO) == -1)
		ft_perror(tok, "dup2 failed", 1);
	close(pipe[0]);
	close(pipe[1]);
	execve(path, args, env);
	ft_perror(tok, "execve failed", 1);
	exit(EXIT_FAILURE);
}

void	ft_succ_childs(t_tok *tok, int *pipe, char *path, char **args, char **env)
{
	//printf("args succ child: %s\n", args[1]);
	if (dup2(pipe[READ_END], STDIN_FILENO) == -1 || dup2(pipe[WRITE_END], STDOUT_FILENO) == -1)
		ft_perror(tok, "dup2 failed", 1);
	close(pipe[0]);
	close(pipe[1]);
	execve(path, args , env);
	ft_perror(tok, "execve failed", 1);
	exit(EXIT_FAILURE);
}

void	ft_last_child(t_tok *tok, int *pipe, char *path, char **args, char **env)
{
	//printf("args last child: %s\n", args[1]);
	if (dup2(pipe[READ_END], STDIN_FILENO) == -1)
		ft_perror(tok, "dup2 failed", 1);
	close(pipe[0]);
	close(pipe[1]);
	execve(path, args, env);
	ft_perror(tok, "execve failed", 1);
	exit(EXIT_FAILURE);
}

char	*ft_dq_pop_utils(int *i, char *line)
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

char	*ft_q_pop_utils(int *i, char *line)
{
	int		tmp_i;
	char	*tmp;

	tmp = malloc (sizeof (char) * (ft_strlen_till_char(line, *i, '\'') + 1));//allocating memory for args
	tmp_i = 0;
	(*i)++;// skip first '
	while (line[*i] != '\'' && line[*i] != '\0')
		tmp[tmp_i++] = line[(*i)++];//populating args
	tmp[tmp_i] = '\0';//putting end of string
	(*i)++;//skip last '
	return (tmp);
}

char	*ft_w_pop_utils(int *i, char *line)
{
	int		tmp_i;
	char	*tmp;

	tmp = malloc (sizeof (char) * (ft_strlen_till_char(line, *i, ' ') + 1));//allocating memory for args
	tmp_i = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t')//populating args
		tmp[tmp_i++] = line[(*i)++];
	tmp[tmp_i] = '\0';//putting end of string
	return (tmp);
}
