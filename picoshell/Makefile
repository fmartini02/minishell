# **************************************************************************** #

NAME = picoshell

SRC = pico_shell.c lexer_utils.c signal_handling.c  ft_initializer.c  dollar_case_utils.c pipe.c \
	  pipe_exe.c pipe_args_utils.c  pipe_args_utils2.c  ft_errors.c \
	  ft_env_shits.c ft_utils.c ft_builtins_cmds.c ft_cd_utils.c ft_cd_utils2.c ft_cd.c ft_echo.c \
	  ft_pwd.c ft_export.c ft_env.c ft_unset.c ft_exit.c ft_clear.c redi_utils.c \
	  redi_stdin.c redi_stdout.c pipe_utils.c pipe_pop_utils.c pipe_pop.c \
	  redi_amper_utils.c redi_edge_cases.c redi_utils2.c redi.c rm_redi.c \

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LDFLAGS = -lreadline

LIBFT = libft/libft.a

all: $(NAME)

$(LIBFT):
	@make -s -C ./libft
	@make -s -C ./libft bonus

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS) -ltinfo

%.o: %.c
	@$(CC) -c $(CFLAGS) -I. $< -o $@ -s
clean:
	@rm -f $(OBJ)
	@make -s -C libft clean
fclean: clean
	@rm -f $(NAME)
	@make -s -C libft fclean
re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
