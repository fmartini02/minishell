# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmartini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 16:18:30 by fmartini          #+#    #+#              #
#    Updated: 2024/04/09 16:18:30 by fmartini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		  ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
		  ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		  ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
		  ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		  ft_atoi.c ft_calloc.c ft_strdup.c ft_strcat.c ft_strncpy.c \
		  ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
		  ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		  ft_putchar.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		  ft_strcpy_till_char.c ft_strlen_till_char.c ft_matlen.c \
		  ft_word_len.c ft_skip_spaces.c ft_print_mat.c ft_strcmp.c \
		  ft_print_list.c ft_putstr.c ft_strjoin_free.c ft_strcpy.c \
		  ft_get_word_from_indx.c ft_is_space.c ft_strlen_till_space.c\
		  ft_next_char_indx.c

SRCS_BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c \

OBJS		= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

NAME		= libft.a

CC		= cc
RM		= rm -f

CFLAGS		= -Wall -Wextra -Werror

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -s

$(NAME):	$(OBJS)
		ar rc $(NAME) $(OBJS)

all:		$(NAME)

bonus:		all $(OBJS_BONUS)
		ar rc $(NAME) $(OBJS_BONUS)

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re bonus
