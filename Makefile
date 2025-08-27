# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: r <gpouzet@42.fr>                          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 13:46:36 by r                 #+#    #+#              #
#    Updated: 2025/08/24 17:52:21 by gpouzet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 	= clang++

CCFLAGS = -Wall -Wextra -Werror -g

FLAGS = -lglfw -lGLEW -lGL

NAME = Scop

SRC = src/main.cpp src/window.cpp src/mesh.cpp src/objloader.cpp\

OBJ	= $(SRC:.cpp=.o)

%.o: %.cpp
	@$(CC) $(CCFLAGS) -o $@ -c $<
	@echo -n "\\r\033[2K"
	@echo -n "\\r\033[1;33m[compiling...]"$<

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CCFLAGS) $(OBJ) -o $(NAME) $(FLAGS)
	@echo -n "\\r\033[2K"
	@echo "\033[1;32m[executable created]"

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;32m[Programe deleted]"

re: fclean all

.PHONY: all clean fclean re

