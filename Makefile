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

# FLAGS =	-Wall -Wextra -Werror

SRC = ft_printf.c

OBJ = $(SRC:.c=.o)

HDR = -I includes/

all: $(NAME)

$(NAME):
	make re -C libft
	gcc -c $(FLAGS) $(SRC) ft_printf.h 
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re:	fclean all

.PHONY: clean fclean all re
