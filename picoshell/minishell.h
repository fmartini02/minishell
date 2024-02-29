/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:24:31 by fmartini          #+#    #+#             */
/*   Updated: 2024/02/29 11:30:13 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHELL_H
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<readline/readline.h>
# include<readline/history.h>


typedef struct s_loc_var
{
	char	*name;//nome variabile creata sulla shell
	char	*content;//contenuto variabile da elaborare
}	t_loc_var;

int	ft_wlen(char *s, int i);


#endif
