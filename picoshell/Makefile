# **************************************************************************** #

NAME = picoshell

SRC = pico_shell.c \
      lexer_utils.c \
      ft_init_sigs.c \
      strlens.c \
      signal_handling.c \
      ft_putstr_fd.c \
      token_utils.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

LDFLAGS = -lreadline

LIBFT = libft/libft.a

all: $(NAME)

$(LIBFT):
	@make -s -C ./libft

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	@$(CC) -c $(CFLAG) -I. $< -o $@ -s
clean:
	@rm -f $(OBJ)
	@make -s -C libft clean
fclean: clean
	@rm -f $(NAME)
	@make -s -C libft fclean
re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
