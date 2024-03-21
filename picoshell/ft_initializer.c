/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initializer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:23:59 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/21 17:16:26 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signum);

void	ft_initializer(t_tok **inputs, sigset_t *my_set, struct sigaction *sa)
{
	*inputs = createNode();
	ft_init_set(my_set);
	ft_add_sig_to_set(my_set);
	sa->sa_handler = &handle_signals;
	sa->sa_mask = *my_set;
}

void	ft_signal_ear(struct sigaction *sa)
{
	int i;
	int	signals[3] = {SIGINT, SIGQUIT, SIGTSTP};

	i = 0;
	while (i < (sizeof(signals) / sizeof(signals[0])))
	{
		if (sigaction(signals[i], sa, NULL) == -1)
		{
			perror("sigaction");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
