# **************************************************************************** #

NAME = picoshell

SRC = pico_shell.c lexer_utils.c ft_init_sigs.c strlens.c signal_handling.c ft_putstr_fd.c ft_putchar_fd.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
