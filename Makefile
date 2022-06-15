# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 11:44:20 by ygonzale          #+#    #+#              #
#    Updated: 2022/06/15 11:29:43 by ygonzale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRC = pipex.c ft_split.c ft_strchr.c \
	ft_strjoin.c ft_strlen.c ft_strncmp.c \
	ft_substr.c get_path.c \

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
	@echo 🗑 "\033[31;3;4mall clean\033[0m" 🗑
	
re: fclean all

.PHONY = all clean fclean re
