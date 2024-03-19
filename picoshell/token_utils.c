/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prova.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:56:49 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/18 16:55:22 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok *createNode(void)
{
	t_tok *newNode = (t_tok*)malloc(sizeof(t_tok));
	if (newNode == NULL) {
		perror("allocation failed");
		exit(1);
	}
	newNode->line = ft_calloc(0,0);
	newNode->next = NULL;
	return newNode;
}
void freeList(t_tok *head)
{
	int i = 0;
	while (head != NULL)
	{
		t_tok *temp = head;
		head = head->next;
		while (temp->line[i])
		{
			free(temp->line[i]);
			i++;
		}
		i = 0;
		free(temp->line);
		free(temp);
	}
}


