/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pico_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:22:36 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/04 15:50:20 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minishell.h"

volatile int sig_code = 0;

char	**ft_lexer(const char *s)
{
	int		i;
	char	**tok;
	int		i_t;

	i = 0;
	i_t = 0;
	tok = malloc(sizeof(char *) * (ft_count_words(s) + 1));
	if (!tok)
		return (NULL);
	while (s[i])
	{
		if (s[i] == 39)
			tok[i_t] = ft_sngl_q_case(s, i);
		else if (s[i] == 34)
			tok[i_t] = ft_db_q_case(s, i);
		else
		 	tok[i_t] = ft_word_case(s, i);
		i_t++;
		while (s[i] != ' ' && s[i] != '\t' && s[i])
		i++;
		while ((s[i] == ' ' || s[i] == '\t') && s[i])
		i++;
	}
	return (tok);
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

int	main(char **envp)
{
	char				*s;
	t_tok				*inputs;
	struct sigaction	sa;
	int					pipe_fd[2];

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
		inputs->line = ft_lexer(s);
		inputs->str_line = s;
		ft_pipe(inputs, envp);
		inputs->next = createNode();
	}
}
