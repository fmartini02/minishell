/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:44:31 by francema          #+#    #+#             */
/*   Updated: 2024/09/25 19:31:08 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_node(t_env **head, t_env *node)
{
	t_env	*tmp;

	if (*head == node)
	{
		*head = node->next;
		free(node->content);
		free(node);
		return ;
	}
	tmp = *head;
	while(tmp->next && tmp)
	{
		if (tmp->next == node)
		{
			tmp->next = node->next;
			free(node->content);
			free(node);
		}
		tmp = tmp->next;
	}
}

void	ft_unset(t_tok *tok, char **args)
{
	t_env	*tmp;

	tmp = tok->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, args[0], ft_strlen(args[0])) == 0)
		{
			ft_delete_node(&tok->env, tmp);
			return ;
		}
		tmp = tmp->next;
	}
}
