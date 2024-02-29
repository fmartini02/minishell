/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_test1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:53:03 by fmartini          #+#    #+#             */
/*   Updated: 2024/02/26 18:15:24 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
int	main()
{
	char	*input;

	while(1)
	{
		rl_replace_line("porcodio infame \n", 1);
		rl_redisplay();
		usleep(1000000);
		input = readline("put odd number");
		if ((atoi(input)) & 1)
		{
			rl_replace_line("right", 1);
			rl_redisplay();
		}
		else
		{
			rl_replace_line("wrong", 1);
			rl_redisplay();
		}
		free(input);
	}
}
