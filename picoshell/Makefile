# **************************************************************************** #

NAME = picoshell

SRC = pico_shell.c \
      lexer_utils.c \
      signal_handling.c \
      token_utils.c \
	  ft_initializer.c \
	  dollar_case_utils.c \
	  pipe.c \
	  pipe_exe_utils.c \
	  pipe_args_pop.c \
	  pipe_args_utils.c \
	  ft_errors.c \
	  ft_env_shits.c \
	  ft_utils.c \

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
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)

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
