/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:33:14 by francema          #+#    #+#             */
/*   Updated: 2024/09/23 15:07:42 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long int	ft_env_vars_len(t_env *env)
{
	long int	len;
	t_env		*tmp;

	len = 0;
	tmp = env;
	while (tmp)
	{
		len += ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	return (len + 1);
}

char	*ft_strfication(t_env *env)
{
	char	*env_vars;
	t_env	*tmp;
	long int	i;
	long int	j;
	long int	l;

	i = 0;
	j = 0;
	tmp = env;
	env_vars = malloc(sizeof(char) * (ft_env_vars_len(env) + ft_lstsize((void *)env))) + 1;
	if (!env_vars)
		perror("malloc error in ft_env_builtin");
	while (tmp)
	{
		l = ft_strlen(tmp->content);
		ft_strlcpy(env_vars + i, tmp->content, l + 1);
		j += l;
		env_vars[j++] = '\n'; // Add newline between nodes
		tmp = tmp->next;
	}
	env_vars[j] = '\0';
	return (env_vars);
}

void	ft_env_builtin(t_tok *tok)
{
	if (tok->pipe_flag == 1)
		tok->builtin_flag = 0;
	else
	{
		ft_print_list(tok->env);
		tok->builtin_flag = 1;
	}
}
