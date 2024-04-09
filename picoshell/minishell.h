/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:24:31 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/09 17:42:52 by fmartini         ###   ########.fr       */
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

enum pipe_macro
{
	READ_END,
	WRITE_END
};

typedef struct s_tok
{
	char			**line;
	char			*str_line;
	struct s_tok	*next;
	char			**cmds;
	char			**env;
	char			**cmds_args;
}	t_tok;

char		*ft_db_q_case(const char *s, int i);
char		*ft_word_case(const char *s, int i);
char		*ft_sngl_q_case(const char *s, int i);
void		ft_add_sig_to_set(sigset_t *my_set);
void		ft_init_set(sigset_t *my_set);
void		ctrl_d_case(void);
int			ctrl_c_case(int signum);
int			ctrl_z_case(int signum);
int			ctrl_bckslash_case(int num);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
int			ft_count_words(const char *s);
t_tok		*createNode(void);
void		ft_signal_ear(struct sigaction *sa);
void		ft_initializer(t_tok **inputs, struct sigaction *sa);
int			ft_find_dq_len(const char *s, int i);
char		*ft_doll_case(char *s, int i);
void		ft_dq_utils(char **str, const char *s, int *i, int *j);
char		*ft_doll_case(char *s, int i);
char		*ft_get_cont_var(char *env_var_line, int j);
char		*ft_get_var_name(const char *s, char *doll_var, int i, int j);
int			ft_find_dq_len(const char *s, int i);
char		**ft_get_cmds_names(t_tok *tok);
char		*get_cmd_path(char **paths, char *cmd);
char		**ft_get_cmds_args(t_tok *tok);
void		ft_pipe(t_tok *tok, char **env);
void		ft_first_child(t_tok *tok, int *pipe, int i, char **env);
void		ft_succ_childs(t_tok *tok, int *pipe, int i, char **env);
void		ft_last_child(t_tok *tok, int *pipe, int i, char ** env);
int			ft_count_cmds(t_tok *tok);
int			ft_count_args_str(t_tok *tok);
int			ft_skip(char *s, int i);
char*const*	ft_exec_args(char *args, t_tok *tok);
void		ft_perror(t_tok *tok, char *s, int flag);
void		ft_pipe_utils(t_tok *tok, int *pip, int *i, char **env);

#endif
