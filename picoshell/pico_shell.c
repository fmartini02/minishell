/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pico_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:22:36 by fmartini          #+#    #+#             */
/*   Updated: 2024/02/29 11:29:44 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_lexer(char *s, char **tok)
{
	char	*tmp;
	int		i;
	int		j;
	int		i_t;

	tmp = s;
	i = 0;
	j = 0;
	i_t = 0;
	while (tmp[i])
	{
		if (tmp[i] == '39')
			tok[i_t++] = ft_sing_q_case(tmp, i);
		else if (tmp[i] == '34')
			tok[i_t++] = ft_db_q_case(tmp, i, tok, i_t);
		else
			tok[i_t++] = ft_word_case(tmp, i);
	}
	return (tok);
}

t_loc_var	**ft_find_var(char *s)
{
	int		i;
	int		j;
	char	*buf;
	int		check;

	i = 0;
	j = 0;
	while (s[i] == ' ' || s[i] == '	')
		i++;
	buf = malloc(sizeof (char) * ft_wlen(s, i));
	while(s[i] != ' ' || s[i] != '	' && s[i])
		buf[j++] = s[i++];
	if (strrchr(s, '='))
	{
		s = strrchr(s, '=');
	}
}

int     main()
{
	char	*s;
	char	**tokens;
	t_loc_var	**vars;
	int		fpid;

	while (1)
	{
		s = readline("minishell$ ");
		if (ft_find_var(s))
		{
			vars = ft_find_vars(s);
			s = "\0";
		}
		tokens = ft_lexer(s, tokens);
		fpid = fork();
		if (fpid == 0)
		{
			execve();
			exit(EXIT_FAILURE);
		}
		wait(EXIT_SUCCESS);
	}
}
