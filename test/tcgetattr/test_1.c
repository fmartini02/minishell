/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:35:25 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/14 15:01:51 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>

volatile sig_atomic_t should_exit = 0;

void	handle_sigquit(int signum)
{
	write(1, "", 0);
	should_exit = signum;
}

void	handle_sigtstp(int signum)
{
	write(1, "", 0);
	should_exit = signum;
}

int	main ()
{
	int	i=0;
	struct termios term;
	signal(SIGQUIT, handle_sigquit);
    signal(SIGTSTP, handle_sigtstp);
	tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
	while (!should_exit)
	{
		i++;
	}
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
