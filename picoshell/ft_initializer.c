/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initializer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:23:59 by fmartini          #+#    #+#             */
/*   Updated: 2024/11/05 19:49:17 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signum);

int	find_redi_indx(char *s)
{
	int	i;
	int	redi_indx;
	int	pipe_num;

	i = 0;
	pipe_num = 0;
	redi_indx = -1;
	while (s[i] && redi_indx < 0)
	{
		while(s[i] && s[i] != '|')
		{
			if (s[i] == '<' || s[i] == '>')
				redi_indx = pipe_num;
			i++;
		}
		if (s[i] == '|')
			pipe_num++;
		if (s[i])
			i++;
	}
	return (redi_indx);
}

void	ft_initializer(t_tok **inputs, struct sigaction *sa)
{
	sigset_t	my_set;

	*inputs = malloc(sizeof(t_tok));
	if (!*inputs)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	(*inputs)->i = 0;
	(*inputs)->str_line = NULL;
	(*inputs)->cmds = NULL;
	(*inputs)->cmds_args = NULL;
	(*inputs)->pipes = NULL;
	(*inputs)->builtin_flag = -1;
	(*inputs)->last_child_flag = 0;
	(*inputs)->pipe_flag = 0;
	(*inputs)->builtin_presence = 0;
	(*inputs)->redi_flag = 0;
	(*inputs)->stdin_fd = dup(STDIN_FILENO);
	(*inputs)->stdout_fd = dup(STDOUT_FILENO);
	(*inputs)->stderr_fd = dup(STDERR_FILENO);
	if (sigemptyset(&my_set) == -1)
		perror("sigemptyset failed");
	ft_add_sig_to_set(&my_set);
	memset(sa, 0, sizeof(struct sigaction));//initialize all fields to 0
	sa->sa_handler = &handle_signals;
	sa->sa_mask = my_set;
	sa->sa_flags = 0;
}

void	ft_add_sig_to_set(sigset_t *my_set)
{
	if (sigaddset(my_set, SIGINT) == -1)
		perror("sigaddset failed");
	if (sigaddset(my_set, SIGTERM) == -1)
		perror("sigaddset failed");
	if (sigaddset(my_set, SIGKILL) == -1)
		perror("sigaddset failed");
	if (sigaddset(my_set, SIGQUIT) == -1)
		perror("sigaddset failed");
	if (sigaddset(my_set, SIGTSTP) == -1)
		perror("sigaddset failed");
}

void	ft_signal_ear(struct sigaction *sa)
{
	int i;
	int	signals[3] = {SIGINT, SIGQUIT, SIGTSTP};

	i = 0;
	while (i < (int)(sizeof(signals) / sizeof(signals[0])))
	{
		if (sigaction(signals[i], sa, NULL) == -1)
		{
			perror("sigaction");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
