# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/02 11:47:41 by anarodri          #+#    #+#              #
#    Updated: 2022/07/08 17:39:27 by anarodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

SRC		=	$(addprefix src/, pipex.c process.c utils.c free.c error.c)

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
			@make clean -C ./libft
			$(RM) $(OBJ)

fclean:		clean
			@make fclean -C ./libft
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re