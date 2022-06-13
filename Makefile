# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 11:44:20 by ygonzale          #+#    #+#              #
#    Updated: 2022/06/13 16:02:28 by ygonzale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRC = pipex.c test.c \

OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	@echo ✅ "\033[92;3;4mcompilation done\033[0m" ✅

$(OBJS): $(SRC)
	gcc $(CFLAGS) -c $(SRC)

clean:
	@rm -f $(OBJS)

fclean:
	@rm -f $(OBJS) $(NAME)
	@echo 🗑 "\033[34;3;4mall clean\033[0m" 🗑
	
re: fclean all

.PHONY = all clean fclean re
