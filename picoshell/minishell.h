/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:24:31 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/15 17:43:33 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHELL_H
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<signal.h>
# include<termios.h>
# include<readline/readline.h>
# include<readline/history.h>


// typedef struct s_loc_var
// {
// 	char	*name;//nome variabile creata sulla shell
// 	char	*content;//contenuto variabile da elaborare
// }	t_loc_var;

int		ft_wlen(char *s, int i);
char	*ft_db_q_case(char *s, int i, char **tok, int i_t);
char	*ft_word_case(char *s, int i);
char	*ft_sngl_q_case(char *s, int i);
void	ft_add_sig_to_set(sigset_t *my_set);
void	ft_init_set(sigset_t *my_set);
int		ft_strlen_quote(char *s, int i);
int		ft_strlen_dquote(char *s, int i);
int		ft_wlen(char *s, int i);
void	ctrl_d_case(char *s);
int		ctrl_c_case(int signum);
int		ctrl_z_case(int signum);
int		ctrl_bckslash_case(int num);
void	ft_set_raw(void);
void

#endif
