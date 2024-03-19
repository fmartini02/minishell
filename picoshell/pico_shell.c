/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pico_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:22:36 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/19 18:54:36 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minishell.h"

volatile int sig_code = 0;

void	handle_signals(int signum);

char	**ft_lexer(char *s)
{
	char	*tmp;
	int		i;
	char	**tok;
	int		i_t;

	tmp = s;
	i = 0;
	i_t = 0;
	tok = malloc(sizeof(char *) * (ft_count_words(tmp) + 1));
	while (tmp[i])
	{
		if (tmp[i] == 39)
			tok[i_t] = ft_sngl_q_case(tmp, i);
		else if (tmp[i] == 34)
			tok[i_t] = ft_db_q_case(tmp, i, tok, i_t);
		else
			tok[i_t] = ft_word_case(tmp, i);
		i_t++;
		i = ft_new_word(tmp, i);
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

	inputs = createNode();
	ft_init_set(&my_set);
	ft_add_sig_to_set(&my_set);
	sa.sa_handler = &handle_signals;
	sa.sa_mask = my_set;
	if (sigaction(SIGQUIT, &sa, NULL) == -1 ||
		sigaction(SIGINT, &sa, NULL) == -1 ||
		sigaction(SIGTSTP, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		s = readline("minishell$ ");
		if (!s)
			ctrl_d_case();
		inputs->line = ft_lexer(s);
		inputs->next = createNode();
		add_history(s);
	}
}
