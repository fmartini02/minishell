/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:24:31 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/26 16:15:51 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L
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

char	*ft_db_q_case(const char *s, int i);
char	*ft_word_case(const char *s, int i);
char	*ft_sngl_q_case(const char *s, int i);
void	ft_add_sig_to_set(sigset_t *my_set);
void	ft_init_set(sigset_t *my_set);
int		ft_strlen_quote(const char *s, int i);
int		ft_strlen_dquote(const char *s, int i);
int		ft_word_len(const char *s, int i);
void	ctrl_d_case(void);
int		ctrl_c_case(int signum);
int		ctrl_z_case(int signum);
int		ctrl_bckslash_case(int num);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
int		ft_new_word(const char *s, int i);
int		ft_count_words(const char *s);
t_tok	*createNode(void);
void	ft_signal_ear(struct sigaction *sa);
void	ft_initializer(t_tok **inputs, sigset_t *my_set, struct sigaction *sa);
int		ft_find_dq_len(const char *s, int i);
char	*ft_doll_case(char *s, int i);
void	ft_dq_utils(char **str, const char *s, int *i, int *j);
char	*ft_doll_case(char *s, int i);
char	*ft_get_cont_var(char *env_var_line, int j);
char	*ft_get_var_name(const char *s, char *doll_var, int i, int j);
int		ft_find_dq_len(const char *s, int i);

#endif
