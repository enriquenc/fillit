# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/31 01:02:24 by obamzuro          #+#    #+#              #
#    Updated: 2018/04/01 17:52:02 by obamzuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC =	file_parser.c		\
		fillit.c			\
		fillit_file.c		\
		fillit_plus.c		\

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	gcc -Wall -Wextra -Werror $(OBJS) -o fillit

%.o:%.c
	gcc -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
