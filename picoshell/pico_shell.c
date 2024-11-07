/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pico_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:22:36 by fmartini          #+#    #+#             */
/*   Updated: 2024/11/05 19:56:55 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minishell.h"

volatile int sig_code;

char	*ft_lexer(const char *s, t_tok *tok)
{
	int		i;
	char	*line;
	char	*temp;

	i = 0;
	line = ft_init_line(s);
	while (s[i])
	{
		if (s[i] == '\'')
			temp = ft_sngl_q_case(s, &i);
		else if (s[i] == '"')
			temp = ft_db_q_case(s, &i);
		else if (s[i] == '>' || s[i] == '<')
			temp = ft_lexer_redi_case(s, &i, tok);//set redi_flag to 1 and return the redirection string
		else
		 	temp = ft_strdup(ft_normal_case(s, &i));
		line = ft_strjoin_free(line, temp);
		free(temp);
		while (s[i] != ' ' && s[i] != '\t' && s[i] && s[i] != '"'
				&& s[i] != '\'' && s[i] != '>' && s[i] != '<')
			i++;
	}
	return (line);
}

void	handle_signals(int signum)
{
	if (signum == SIGINT)//ctrl + c
		sig_code = ctrl_c_case(signum);
	else if (signum == SIGQUIT)//ctrl + '\'
		sig_code = ctrl_bckslash_case(signum);
	else if (signum == SIGTSTP)//ctrl + z
		sig_code = ctrl_z_case(signum);
}

char	*ft_select_prompt(void)
{
	char	tmp[PATH_MAX];
	char	*prompt;
	char	*home;

	prompt = NULL;
	home = getenv("HOME");
	if (getcwd(tmp, PATH_MAX))
	{
		if (!ft_strcmp(tmp, home))
			prompt = ft_strdup("~");
		else if(!ft_strncmp(tmp, home, ft_strlen(home)))
			prompt = ft_strjoin_free(ft_strdup("~"), tmp + ft_strlen(home) + 1);
		else
			prompt = ft_strdup(tmp);
	}
	else
		perror("getcwd() error");
	prompt = ft_strjoin_free(prompt, "$ ");
	return (prompt);
}

void	ft_reset_std_fds(t_tok *tok)
{
	if (dup2(tok->stdin_fd, STDIN_FILENO) == -1)
		perror("minishell: dup2 error");
	if (dup2(tok->stdout_fd, STDOUT_FILENO) == -1)
		perror("minishell: dup2 error");
	if (dup2(tok->stderr_fd, STDERR_FILENO) == -1)
		perror("minishell: dup2 error");
}

int	main(int ac, char **av, char **envp)
{
	struct sigaction	sa;
	t_tok				*inputs;
	char				*s;
	char				*prompt;

	(void)ac;
	(void)av;
	ft_initializer(&inputs,&sa);
	ft_signal_ear(&sa);
	while (1)
	{
		inputs->env = ft_set_env(envp);
		prompt = ft_select_prompt();
		s = readline(prompt);
		if (!s)
		{
			free(prompt);
			ctrl_d_case(inputs);
		}
		add_history(s);
		inputs->str_line = ft_strdup(ft_lexer(s, inputs));
		ft_pipe(inputs);
		ft_free_mem(inputs);
		ft_reset_std_fds(inputs);
		ft_initializer(&inputs, &sa);
		free(s);
	}
	return (0);
}
