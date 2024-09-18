/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:06:37 by francema          #+#    #+#             */
/*   Updated: 2024/09/17 17:25:26 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_dup_check(t_env *env, char *var)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, ft_strlen_till_char(var, 0, '=')) == 0)// compare the variable name
		{
			if(tmp->content[ft_strlen_till_char(var, 0, '=')] == '=')
				return (tmp);
			else
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_overwrite_env(t_env *env, char *var)
{
	free(env->content);
	env->content = ft_strdup(var);
}

int	ft_check_key_value(char *var)
{
	int		i;

	if (!var || !ft_strchr(var, '=') || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (0);
	i = 1;
	while(var[i] && var[i] != '=')
	{
		if(!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	if (var[i] == '=' && !var[i + 1])
		return (0);
	return (1);
}

void	ft_export_builtin(t_tok *tok, char **args)
{
	t_env	*tmp;

	tmp = ft_dup_check(tok->env, args[0]);
	if (ft_check_key_value(args[0])) // if args[0] isn't NULL and has '='
	{
		if (tmp)// if the variable already exists
		{
			ft_overwrite_env(tmp, args[0]);// overwrite the variable value
			printf("new var is: %s\n", args[0]);
		}
		else
		{
			ft_lstadd_back((void *)&tok->env, ft_lstnew(ft_strdup(args[0])));
			tok->builtin_flag = 1;
			printf("new var is: %s\n", args[0]);
		}
	}
}
