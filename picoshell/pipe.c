/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:03:14 by fmartini          #+#    #+#             */
/*   Updated: 2024/11/05 15:50:03 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***ft_set_cmds_args(t_tok *tok)
{
	char	***cmds_args;
	char	**args_mat;
	int		i;
	int		i_cmd;

	if (!ft_count_cmds(tok))//if only spaces or syntx error
		return (NULL);
	i = 0;
	i_cmd = 0;
	cmds_args = malloc (sizeof (char **) * (ft_count_cmds(tok) + 1));//allocating memory for cmds_args + null
	if (!cmds_args)
		perror("malloc error in ft_set_cmds_args");
	while (tok->str_line[i])
	{
		args_mat = malloc (sizeof (char *) * (ft_args_counting(tok, i) + 1));//allocating memory for args_mat + null + cmd_name
		if (!args_mat)
			perror("malloc error in ft_set_cmds_args");
		args_mat = ft_populate_mtx(tok, args_mat, &i);//setting args_mat
		cmds_args[i_cmd++] = args_mat;
		if (tok->str_line[i])
			i++;
	}
	cmds_args[i_cmd] = NULL;
	return (cmds_args);
}

char	*get_cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	if (ft_only_spaces(cmd) || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin_free(ft_strdup(paths[i]), "/");//putting '/' at the end of the path /dir/subdir + /
		cmd_path = ft_strdup(ft_strjoin_free(tmp, cmd));//putting cmd at the end of the path /dir/subdir/ + cmd
		if (access(cmd_path, X_OK) == 0)//checking if the path is correct
		{
			i = 0;
			while(paths[i])
			{
				free(paths[i]);
				i++;
			}
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void	ft_set_fields(t_tok *tok)
{
	tok->cmds_args = ft_set_cmds_args(tok);//setting the cmd_paths arguments
	tok->cmds = ft_get_cmds_names_from_line(tok);//setting the cmd_paths names
	tok->pipes = ft_init_pipes(tok);//initializing the pipes
}

void	ft_pipe_utils(pid_t pid, t_tok *tok, char *path)
{
	int			status;

	if (pid < 0)//checking if the fork failed
		perror("fork error");
	else if (pid == 0)//if it's a child process
		ft_pipe_utils_2(tok, path);
	else
		close(tok->pipes[tok->i][WRITE_END]);
	waitpid(pid, &status, 0);// wait for the child process to finish
	if (tok->i != 0)// if not the first cmd_path, close the read end of the previous pipe
		close(tok->pipes[tok->i - 1][READ_END]);
	free(path);
	(tok->i)++;
}

void	ft_pipe(t_tok *tok)
{
	pid_t		pid;
	char		*path;

	ft_set_fields(tok);//setting the fields of the struct
	while (tok->i < ft_matlen((void **)tok->cmds))//cycle to execute all the cmd_paths
	{
		ft_builtins_presence(tok, tok->i);//set builtin-presence flag for current cmd_path
		path = get_cmd_path(ft_split(getenv("PATH"), ':'), tok->cmds[tok->i]);//getting the path of the cmd_path
		if(!path)
		{
			if (tok->builtin_presence == 1)//if the cmd_path is a builtin
				ft_builtins_cmds(tok, tok->cmds_args[tok->i]);
			else if (ft_only_spaces(tok->cmds[tok->i]) && tok->pipe_flag == 1)//if there is a pipe but the cmd_path is empty
			{
				printf("bash: syntax error near unexpected token `|'\n");
				return ;
			}
			else if (ft_only_spaces(tok->cmds[tok->i]))
				return ;
			else
				printf("%s: command not found\n", tok->cmds[tok->i]);
			return ;
		}
		pid = fork();//creating a child process
		ft_pipe_utils(pid, tok, path);//handle the child process and the execution of the cmd_path
	}
	if (tok->i != 0)// close the read end of the last pipe
		close(tok->pipes[tok->i - 1][READ_END]);
}
