/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:24:31 by fmartini          #+#    #+#             */
/*   Updated: 2024/09/19 16:02:57 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<signal.h>
# include<fcntl.h>
# include<termios.h>
# include<errno.h>
# include<limits.h>
# include<sys/wait.h>
# include"libft/libft.h"
# include<readline/readline.h>
# include<readline/history.h>
# include <curses.h>
# include <term.h>

enum pipe_macro
{
	READ_END,
	WRITE_END
};

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_tok
{
	char			*str_line;
	t_env			*env;
	char			**cmds;
	char			***cmds_args;
	int				**pipes;
	struct s_tok	*next;
	int				builtin_flag;
}	t_tok;

char		*ft_db_q_case(const char *s, int *i);
char		*ft_normal_case(const char *s, int *i);
char		*ft_sngl_q_case(const char *s, int *i);
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
char		*get_cmd_path(char **paths, char *cmd);
void		ft_pipe(t_tok *tok, int i);
void		ft_first_child(t_tok *tok, char *path, char **args, char **env, int i);
void		ft_succ_childs(t_tok *tok, char *path, char **args, char **env, int i);
void		ft_last_child(t_tok *tok, char *path, char **args, char **env, int i);
int			ft_count_cmds(t_tok *tok);
int			ft_args_counting(t_tok *tok, int i);
void		ft_perror(t_tok *tok, char *s, int flag);
char		*ft_dq_pop_utils(int *i, char *line);
char		*ft_q_pop_utils(int *i, char *line);
char		*ft_w_pop_utils(int *i, char *line);
char		*ft_extract_cmd_name(const char *s, int *i);
char		**ft_get_cmds_names_from_line(t_tok *tok);
char		**ft_populate_mtx(t_tok *tok, char **args_mat, int *i);
char		***ft_set_cmds_args(t_tok *tok);
void		ft_pipe_utils(t_tok *tok, int i, char *path, char **args, char **env);
int			ft_only_spaces(char *line);
int			**ft_init_pipes(t_tok *tok);
int			ft_vars_len(const char *s);
void		ft_print_list(t_env *head);
t_env		*ft_set_env(char **envp);
char		**ft_lst_2_mtx(t_env *head);
char		*ft_init_line(const char *s, t_tok *tok);
t_env		*ft_add_var(t_env *head, char *var);
void		ft_cd_builtin(t_tok *tok, char **args);
void		handle_absolute_path(char *arg);
void		handle_parent_directory(char *path);
void		handle_parent_directory(char *path);
void		handle_env_variable(char *arg);
void		handle_relative_path(char *arg, char *path);
void		handle_default_case(char *arg);
void		ft_root_case(void);
void		ft_dotdot_case(char *path);
void		ft_same_dir_case(char *path);
void		ft_user_home_case(char **args);
void		ft_builtins_cmds(t_tok *tok, char **args);
void		ft_echo_builtin(t_tok *tok, char **args);
void		ft_pwd_builtin(t_tok *tok);
void		ft_export_builtin(t_tok *tok, char **args);
void		ft_env_builtin(t_tok *tok);
void		ft_unset_builtin(t_tok *tok, char **args);
void		ft_exit_builtin(t_tok *tok, char **args);
void		ft_clear_builtin(t_tok *tok);

#endif
