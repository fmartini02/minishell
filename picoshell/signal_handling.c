/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:10:31 by fmartini          #+#    #+#             */
/*   Updated: 2024/11/05 19:45:33 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d_case(t_tok *tok)
{
	ft_free_mem(tok);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

int	ctrl_c_case(int signum)
{
	write(1, "\n", 1);
	return (signum);
}

int	ctrl_z_case(int signum)
{
	write (1, "minishell$   \b\b", 15);
	return (signum);
}

int	ctrl_bckslash_case(int signum)
{
	write (1, "minishell$   \b\b", 15);
	return (signum);
}

