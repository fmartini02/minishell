/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:56:49 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/10 17:27:40 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok *createNode(void)
{
	t_tok *newNode;

	newNode = malloc(sizeof(t_tok));
	if (newNode == NULL) {
		perror("allocation failed");
		exit(1);
	}
	newNode->next = NULL;
	return (newNode);
}


