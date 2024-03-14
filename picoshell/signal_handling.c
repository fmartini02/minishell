/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:10:31 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/14 15:22:29 by fmartini         ###   ########.fr       */
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

int	ctrl_z_case(int signum)
{
	write(1, "", 0);
	return(signum);
}

int	ctrl_bckslash_case(int signum)
{
	write(1, "", 0);
	return(signum);
}

int	ctrl_c_case(int signum)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return (signum);
}
