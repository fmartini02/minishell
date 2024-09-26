/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:33:14 by francema          #+#    #+#             */
/*   Updated: 2024/09/26 18:09:34 by francema         ###   ########.fr       */
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

	tmp = env;
	env_vars = malloc(sizeof(char) * (ft_env_vars_len(env) + ft_lstsize((void *)env) + 1));
	if (!env_vars)
		perror("malloc error in ft_env_builtin");
	env_vars[0] = '\0';
	while (tmp)
	{
		env_vars = ft_strjoin_free(env_vars, tmp->content);
		env_vars = ft_strjoin_free(env_vars, "\n"); // Add newline between nodes
		tmp = tmp->next;
	}
	return (env_vars);
}

char	*ft_env(t_tok *tok, char **args)
{
	if (tok->pipe_flag == 1)
		ft_redirect_builtin_output(tok, args);
	return (ft_strfication(tok->env));
}
