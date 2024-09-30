/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pico_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:22:36 by fmartini          #+#    #+#             */
/*   Updated: 2024/09/27 17:52:46 by francema         ###   ########.fr       */
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
	line = ft_init_line(s, tok);
	while (s[i])
	{
		if (s[i] == 39)
			temp = ft_sngl_q_case(s, &i);
		else if (s[i] == 34)
			temp = ft_db_q_case(s, &i);
		else
		 	temp = ft_normal_case(s, &i);
		line = ft_strjoin(line, temp);
		free(temp);
		while (s[i] != ' ' && s[i] != '\t' && s[i] && s[i] != '"' && s[i] != '\'')
			i++;
	}
	line[i] = '\0';
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
			prompt = ft_strjoin("~", tmp + ft_strlen(home) + 1);
		else
			prompt = ft_strdup(tmp);
	}
	else
		perror("getcwd() error");
	ft_strlcat(prompt, "$ ", ft_strlen(prompt) + 3);
	return (prompt);
}

int	main(int ac, char **av, char **envp)
{
	char				*s;
	t_tok				*inputs;
	struct sigaction	sa;
	int					pipe_fd[2];

	(void)ac;
	(void)av;
	ft_initializer(&inputs,&sa);
	ft_signal_ear(&sa);
	pipe(pipe_fd);
	inputs->env = ft_set_env(envp);
	while (1)
	{
		s = readline(ft_select_prompt());
		if (!s)
			ctrl_d_case();
		add_history(s);
		inputs->str_line = ft_lexer(s, inputs);
		ft_pipe(inputs);
		inputs->i = 0;
		inputs->last_child_flag = 0;
		inputs->builtin_flag = 0;
	}
	return (0);
}
