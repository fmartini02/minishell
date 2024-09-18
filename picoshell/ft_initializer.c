/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initializer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:23:59 by fmartini          #+#    #+#             */
/*   Updated: 2024/09/13 16:51:48 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signum);

void	ft_init_set(sigset_t *my_set)
{
	if (sigemptyset(my_set) == -1)
		perror("sigemptyset failed");
}

void	ft_initializer(t_tok **inputs, struct sigaction *sa)
{
	sigset_t	my_set;

	*inputs = createNode();
	(*inputs)->builtin_flag = -1;
	ft_init_set(&my_set);
	ft_add_sig_to_set(&my_set);
	sa->sa_handler = &handle_signals;
	sa->sa_mask = my_set;
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
