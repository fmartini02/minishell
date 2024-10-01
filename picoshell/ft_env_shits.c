/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_shits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:39:26 by fmartini          #+#    #+#             */
/*   Updated: 2024/10/01 15:30:03 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_set_env(char **envp)
{
	t_env *head;
	t_env *prev;
	t_env *env;
	int i;

	i = 0;
	prev = NULL;
	head = NULL;
	while (envp[i])
	{
		env = ft_lstnew(envp[i]);
		if (prev == NULL)
		{
			head = env;
			prev = env;
		}
		else
		{
			prev->next = env;
			prev = env;
		}
		i++;
	}
	return (head);
}

t_env *add_env_var_to_list(t_env *head, t_env *prev, const char *var_name)
{
	char *var_value;
	t_env *env;

	var_value = getenv(var_name);
	if (var_value != NULL)
	{
		env = (t_env *)ft_lstnew(var_value);
		if (prev == NULL)
		{
			head = env;
			prev = env;
		}
		else
		{
			prev->next = env;
			prev = env;
		}
	}

	return head;
}

char	**ft_lst_2_mtx(t_env *head)
{
	int		i;
	char	**env;
	t_env	*tmp;

	i = 0;
	tmp = head;
	env = malloc(sizeof(char *) * (ft_lstsize((void *)head) + 1));
	while (tmp)
	{
		env[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

t_env	*ft_add_var(t_env *head, char *var)
{
	t_env *tmp;
	t_env *new;

	tmp = head;
	new = ft_lstnew(var);
	ft_lstadd_back((void **)&tmp, (void *)new);
	return (head);
}
