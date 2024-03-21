/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pico_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:22:36 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/21 17:17:53 by fmartini         ###   ########.fr       */
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
		i = ft_new_word(s, i);
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

int     main()
{
	char				*s;
	t_tok				*inputs;
	struct sigaction	sa;
	sigset_t			my_set;

	ft_initializer(&inputs, &my_set, &sa);
	ft_signal_ear(&sa);
	while (1)
	{
		s = readline("minishell$ ");
		if (!s)
			ctrl_d_case();
		add_history(s);
		inputs->line = ft_lexer(s);
		inputs->next = createNode();
	}
}
