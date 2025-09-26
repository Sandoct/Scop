# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: r <gpouzet@42.fr>                          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 13:46:36 by r                 #+#    #+#              #
#    Updated: 2025/09/26 15:44:40 by gpouzet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC  = clang++
CCFLAGS = -Wall -Wextra -Werror -g -Iinclude

FLAGS =  -lglfw -lGL

NAME = Scop

SRC_CPP = src/main.cpp src/window.cpp src/objloader.cpp src/shaders.cpp \
          src/meshBuffer.cpp src/matrix4.cpp src/texloader.cpp
SRC_C   = src/glad.c

OBJ_CPP = $(patsubst src/%.cpp, build/%.o, $(SRC_CPP))
OBJ_C   = $(patsubst src/%.c, build/%.o, $(SRC_C))
OBJ     = $(OBJ_CPP) $(OBJ_C)

# Compile C++ files
build/%.o: src/%.cpp
	@mkdir -p build
	@$(CC) $(CCFLAGS) -o $@ -c $<
	@echo -n "\r\033[2K"
	@echo -n "\r\033[1;33m[compiling...]"$<

# Compile C files
build/%.o: src/%.c
	@mkdir -p build
	@clang $(CCFLAGS) -o $@ -c $<
	@echo -n "\r\033[2K"
	@echo -n "\r\033[1;33m[compiling...]"$<

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CCFLAGS) $(OBJ) -o $(NAME) $(FLAGS)
	@echo -n "\r\033[2K"
	@echo "\033[1;32m[executable created]"

clean:
	@rm -rf $(OBJ)
	@rm -rf build

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;32m[Program deleted]"

re: fclean all

.PHONY: all clean fclean re
