/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:35:46 by francema          #+#    #+#             */
/*   Updated: 2024/09/25 19:31:49 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear(t_tok *tok)
{
	char term_buffer[2048];
	char *clear_cmd;
	char *area;

	tok->builtin_flag = 1;
	area = NULL;
	if (getenv("TERM") == NULL)
	{
		perror("getenv");
		return ;
	}
	// Initialize the terminal, get its capabilities
	if (tgetent(term_buffer, getenv("TERM")) != 1)
	{
		perror("tgetent");
		return ;
	}
	// Get the clear screen command sequence
	clear_cmd = tgetstr("cl", &area);
	if (clear_cmd == NULL)
	{
		perror("tgetstr");
		return ;
	}
	// Execute the clear screen command
	tputs(clear_cmd, 1, ft_putchar);
}
