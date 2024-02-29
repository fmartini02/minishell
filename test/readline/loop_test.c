/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:02:59 by fmartini          #+#    #+#             */
/*   Updated: 2024/02/20 18:14:15 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	int	i;
	char	*line;

	i = 0;
	for(;;)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("error");
			return (0);
		}
		else
			printf("line = %s\n", line);
	}
}
