# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 11:44:20 by ygonzale          #+#    #+#              #
#    Updated: 2022/06/15 15:51:18 by ygonzale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRC = pipex.c \
	./srcs/ft_split.c  \
	./srcs/ft_strchr.c \
	./srcs/ft_strjoin.c \
	./srcs/ft_strlen.c \
	./srcs/ft_strncmp.c \
	./srcs/ft_substr.c \
	./srcs/get_path.c \
	./srcs/ft_splitcomp.c \

OBJS = $(SRC:.c=.o)

FLAGS = gcc -Wall -Werror -Wextra

$(NAME): $(OBJS)
	@echo ✅ "\033[92;3;4mcompilation done\033[0m" ✅
	@ar -rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@$(FLAGS) $(SRC) -o pipex

all: $(NAME)

clean:
	@rm -f $(OBJS)
	@echo 🗑 "\033[31;3;4mall clean\033[0m" 🗑

fclean: clean
	@rm -f $(NAME)
	@rm -rf pipex
	
re: fclean all

.PHONY = all clean fclean re
