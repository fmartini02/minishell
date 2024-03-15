/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:10:31 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/15 18:36:36 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d_case(char *s)
{
	struct termios term;

	printf("exit\n");
	free(s);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	exit(EXIT_SUCCESS);
}

int	ctrl_c_case(int signum)
{
	write(1, "\n", 1);
	write(1, "minishell$ ", 11);
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

