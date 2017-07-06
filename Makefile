# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchow <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/21 22:34:31 by jchow             #+#    #+#              #
#    Updated: 2017/06/21 22:34:32 by jchow            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libftprintf.a

FLAGS =	-Wall -Wextra -Werror

SRC = 	ft_printf.c \
		helpers.c \
		identifiers.c \
		postprocess.c \
		postprocess2.c \
		process_big_d.c \
		process_big_d2.c \
		process_d.c \
		process_d2.c \
		process_cs.c \
		process_ox.c \
		process_up.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_isdigit.c \
		ft_itoa.c \
		ft_putchar.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strnew.c \
		ft_strsub.c \
		ft_ulltoa_base.c

SRCDIR = src

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OBJ = $(SRC:.c=.o)

HDR = -I includes/

all: $(NAME)

$(NAME):
	gcc -c $(FLAGS) $(SRCS) $(HDR)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re:	fclean all

.PHONY: clean fclean all re
