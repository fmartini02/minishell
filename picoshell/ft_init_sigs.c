/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_sigs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:06:18 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/04 12:09:19 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minishell.h"

void	ft_init_set(sigset_t *my_set)
{
	if (sigemptyset(my_set) == -1)
		perror("sigemptyset failed");
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
