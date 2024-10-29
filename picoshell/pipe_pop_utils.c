/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_args_pop_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:23:45 by francema          #+#    #+#             */
/*   Updated: 2024/10/14 17:35:11 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_extract_quote_case(const char *s, int *i)
{
	int		j;
	int		tmp;
	char	*cmd;

	j = *i;
	tmp = *i;
	if (s[j] == '"' || s[j] == '\'')
	{
		j = ft_skip_quoted_words((char *)s, j);
		cmd = malloc (sizeof (char) * (j - tmp + 1));//allocating memory for cmd name
		if (!cmd)
			perror("malloc error in ft_extract_cmd_name");
		while (tmp < j)
		{
			cmd[tmp - j] = s[tmp];
			tmp++;
		}
		cmd[tmp - j] = '\0';
		j += ft_strlen_till_char((char *)s, j, '|');// skipping till next '|'
		*i = j;
	}
	return (cmd);
}

char	*ft_extract_utils(const char *s, int *i)
{
	int		j;
	int		tmp;
	int		k;
	char	*cmd;

	j = *i;
	tmp = *i;
	k = 0;
	while (s[j] && s[j] >= '!' && s[j] <= '~' && s[j] != '|')
		j++;
	cmd = malloc (sizeof (char) * (j - tmp + 1));//allocating memory for cmd name
	if (!cmd)
		perror("malloc error in ft_extract_cmd_name");
	while (tmp < j)
	{
		cmd[k++] = s[tmp++];
	}
	cmd[k] = '\0';
	j += ft_strlen_till_char((char *)s, j, '|');// skipping till next '|'
	*i = j;
	return (cmd);
}
