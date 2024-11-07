/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_redi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:26:47 by francema          #+#    #+#             */
/*   Updated: 2024/11/05 18:19:19 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	theres_a_redi(char *s, int n_cmd)
{
	int	r_flag;
	int	i;
	int	n_count;

	i = 0;
	r_flag = 0;
	n_count = 0;
	while(s[i] && n_count <= n_cmd)
	{
		if (s[i] == '<' || s[i] == '>')
			r_flag = 1;
		else if (s[i] == '|')
			n_count++;
		i++;
	}
	return (r_flag);
}

char	*rm_redi(t_redi *redi)
{
	char	*tmp1;
	char	*ret;
	char	*s;
	int		i;

	i = 0;
	ret = NULL;
	s = redi->s;
	while (s[i])
	{
		if (theres_a_redi(s, redi->tok->i))
			tmp1 = rm_redi_utils(s, &i);
		else
		{
			tmp1 = ft_strdup(s);
			ret = ft_strjoin_free(ret, tmp1);
			free(tmp1);
			break ;
		}
		ret = ft_strjoin_free(ret, tmp1);
		free(tmp1);
	}
	return (ret);
}
