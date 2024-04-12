/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pico_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:22:36 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/12 19:57:43 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minishell.h"

volatile int sig_code = 0;

char	*ft_lexer(const char *s)
{
	int		i;
	char	*line;
	char	*temp;

	i = 0;
	line = malloc(sizeof(char) * (ft_strlen(s) + ft_line_len(s) + 1));
	line = "";
	while (s[i])
	{
		if (s[i] == 39)
			temp = ft_sngl_q_case(s, i);
		else if (s[i] == 34)
			temp = ft_db_q_case(s, i);
		else
		 	temp = ft_normal_case(s, i);
		line = ft_strjoin(line, temp);
		free(temp);
		while (s[i] != ' ' && s[i] != '\t' && s[i])
			i++;
		i = ft_skip_spaces((char*)s, i);
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
	inputs->env = envp;
	while (1)
	{
		s = readline("minishell$ ");
		if (!s)
			ctrl_d_case();
		add_history(s);
		inputs->str_line = ft_lexer(s);
		ft_pipe(inputs);
		inputs->next = createNode();
	}
}
