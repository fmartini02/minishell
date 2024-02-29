/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:20:02 by fmartini          #+#    #+#             */
/*   Updated: 2024/02/26 15:15:07 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<readline/readline.h>
#include<readline/history.h>

int	main()
{
	char	*str;
	int		i;
	char	*str2;
	int		tempo;
	HIST_ENTRY **history_matrix;

	i = 0;
	tempo = 5;
	while (tempo--)
	{
		str = readline("minshit$ ");
		if (str)
		{
			add_history(str);
			history_matrix = history_list();
			i++;
		}
		else
			return (0);
	}
	i = 0;
	while (history_matrix[i])
	{
		printf("command: %s\ttimestamp: %s\n", history_matrix[i]->line, history_matrix[i]->timestamp);
		i++;
	}
	rl_clear_history();
	free(str);
	i = 0;
	printf("line = %p\n", history_matrix[i]->line);
	printf("line = %c\n", history_matrix[i]->line[0]);
	printf("timestamp = %p\n", history_matrix[i]->timestamp);
	return(0);
}
