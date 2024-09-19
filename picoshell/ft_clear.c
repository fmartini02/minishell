/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:35:46 by francema          #+#    #+#             */
/*   Updated: 2024/09/19 15:38:36 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_builtin(t_tok *tok)
{
	char term_buffer[2048];
	char *clear_cmd;

	tok->builtin_flag = 1;
	// Initialize the terminal, get its capabilities
	if (tgetent(term_buffer, getenv("TERM")) != 1) {
		perror("tgetent");
		return ;
	}

	// Get the clear screen command sequence
	clear_cmd = tgetstr("cl", NULL);
	if (clear_cmd == NULL) {
		perror("tgetstr");
		return ;
	}

	// Execute the clear screen command
	tputs(clear_cmd, 1, putchar);
}
