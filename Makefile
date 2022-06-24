# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 11:44:20 by ygonzale          #+#    #+#              #
#    Updated: 2022/06/24 12:47:28 by ygonzale         ###   ########.fr        #
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

SRCS_BONUS = pipex_bonus.c \
		./srcs/ft_strchr.c \
		./srcs/ft_strjoin.c \
		./srcs/ft_strlen.c \
		./srcs/ft_strncmp.c \
		./srcs/ft_substr.c \
		./srcs/get_path.c \

OBJS = $(SRC:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

FLAGS = gcc -Wall -Werror -Wextra -g

$(NAME): $(OBJS)
	@echo ✅ "\033[92;3;4mcompilation done\033[0m" ✅
	@ar -rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@$(FLAGS) $(SRC) -o pipex

all: $(NAME)

bonus: $(OBJS) $(OBJS_BONUS)
	@echo ✅ "\033[92;3;4mbonus compilation done\033[0m" ✅
	@ar -rc $(NAME) $(OBJS_BONUS)
	@$(FLAGS) $(SRC_BONUS) -o pipex

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@echo 🗑 "\033[31;3;4mall clean\033[0m" 🗑

fclean: clean
	@rm -f $(NAME)
	@rm -rf pipex
	@rm -f outfile
	@rm -f output
	
re: fclean all

.PHONY = all clean fclean re
