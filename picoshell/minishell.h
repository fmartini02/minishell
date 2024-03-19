/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:24:31 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/19 18:14:25 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHELL_H
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<signal.h>
# include<termios.h>
# include"libft/libft.h"
# include<readline/readline.h>
# include<readline/history.h>


typedef struct s_tok
{
	char			**line;
	struct s_tok	*next;
}	t_tok;

int		ft_wlen(char *s, int i);
char	*ft_db_q_case(char *s, int i, char **tok, int i_t);
char	*ft_word_case(char *s, int i);
char	*ft_sngl_q_case(char *s, int i);
void	ft_add_sig_to_set(sigset_t *my_set);
void	ft_init_set(sigset_t *my_set);
int		ft_strlen_quote(char *s, int i);
int		ft_strlen_dquote(char *s, int i);
int		ft_wlen(char *s, int i);
void	ctrl_d_case(void);
int		ctrl_c_case(int signum);
int		ctrl_z_case(int signum);
int		ctrl_bckslash_case(int num);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
int		ft_new_word(char *s, int i);
int		ft_count_words(char *s);
t_tok	*createNode(void);

#endif
