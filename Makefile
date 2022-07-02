# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/02 11:47:41 by anarodri          #+#    #+#              #
#    Updated: 2022/07/02 13:07:14 by anarodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

SRC		=	$(addprefix src/, pipex.c process.c utils.c)

OBJ		=	$(SRC:.c=.o)

CC		=	gcc
RM		=	rm -f
CFLAGS	=	-Wall -Wextra -Werror -g -I./include/

LIBFT	=	cd ./libft && make
LIBINC	=	./libft/libft.a

all:		$(NAME)

$(NAME):	$(OBJ)
			$(LIBFT)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBINC)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re