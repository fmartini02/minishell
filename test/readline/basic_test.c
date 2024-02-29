/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:39:39 by fmartini          #+#    #+#             */
/*   Updated: 2024/02/20 15:41:28 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*line;
	int		i;

	i = 0;
	line = readline("minishell$");
	if (line == NULL)
	{
		printf("EOF\n");
		return (0);
	}
	printf("line: %s\n", line);
	free(line);
}
