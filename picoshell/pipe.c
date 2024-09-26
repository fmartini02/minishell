/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:03:14 by fmartini          #+#    #+#             */
/*   Updated: 2024/09/26 15:42:51 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***ft_set_cmds_args(t_tok *tok)
{
	char	***cmds_args;
	char	**args_mat;
	int		i;
	int		i_cmd;

	i = 0;
	i_cmd = 0;
	cmds_args = malloc (sizeof (char **) * ft_count_cmds(tok) + 1);//allocating memory for cmds_args + null
	if (!cmds_args)
		ft_perror(tok, "malloc error in ft_set_cmds_args", 1);
	while (tok->str_line[i])
	{
		args_mat = malloc (sizeof (char *) * ft_args_counting(tok, i) + 1);//allocating memory for as many strings of arguments present
		if (!args_mat)
			ft_perror(tok, "malloc error in ft_set_cmds_args", 1);
		if (!ft_only_spaces(tok->str_line))
			i = ft_skip_spaces(tok->str_line, i);//skip spaces
		args_mat = ft_populate_mtx(tok, args_mat, &i);//setting args_mat
		cmds_args[i_cmd++] = args_mat;
		i++;
	}
	cmds_args[i_cmd] = NULL;
	return (cmds_args);
}

char	*get_cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");//putting '/' at the end of the path /dir/subdir + /
		command = ft_strjoin(tmp, cmd);//putting cmd at the end of the path /dir/subdir/ + cmd
		if (access(command, X_OK) == 0)//checking if the path is correct
		{
			//free(tmp);
			return (command);
		}
		//free(command);
		paths++;
	}
	return (NULL);
}

void	ft_pipe(t_tok *tok)
{
	pid_t		pid;
	int			status;
	char		*path;

	tok->cmds_args = ft_set_cmds_args(tok);//setting the commands arguments
	tok->cmds = ft_get_cmds_names_from_line(tok);//setting the commands names
	tok->pipes = ft_init_pipes(tok);//initializing the pipes
	while (tok->i < ft_matlen((void **)tok->cmds))//cycle to execute all the commands
	{
		path = get_cmd_path(ft_split(getenv("PATH"), ':'), tok->cmds[tok->i]);//getting the path of the command
		ft_builtins_cmds(tok, tok->cmds_args[tok->i]);//executing the builtins setting the flag
		pid = fork();//creating a child process
		if (pid < 0)//checking if the fork failed
			ft_perror(tok, "fork failed", 1);
		else if (pid == 0)//if it's a child process
			ft_pipe_utils(tok, path, tok->cmds_args[tok->i]);
		else
			close(tok->pipes[tok->i][WRITE_END]);
		waitpid(pid, &status, 0);// wait for the child process to finish
		if (tok->i != 0)// if not the first command, close the read end of the previous pipe
			close(tok->pipes[tok->i - 1][READ_END]);
		free(path);
		(tok->i)++;
	}
	if (tok->i != 0)// close the read end of the last pipe
		close(tok->pipes[tok->i - 1][READ_END]);
}
