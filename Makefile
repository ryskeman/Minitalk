# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fernando <fernafer@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/17 02:31:13 by fernando          #+#    #+#              #
#    Updated: 2025/08/17 17:04:50 by fernando         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_S = server
NAME_C = client
CC = cc
CFLAGS = -Wall -Wextra -Werror -Includes/
FSANITIZE = -fsanitize=address -g3

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE = -I$(LIBFT_DIR)/

SRC_S = server.c
SRC_C = client.c

OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)

all: $(NAME_S) $(NAME_C)

$(NAME_S): $(LIBFT) $(OBJ_S)
	@echo "Linking $(NAME_S)..."
	$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ_S) $(LIBFT) -o $(NAME_S)
	@echo "$(NAME_S) Compiled succesfully!"

$(NAME_C): $(LIBFT) $(OBJ_C)
	@echo "Linking $(NAME_C)..."
	$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ_C) $(LIBFT) -o $(NAME_C)
	@echo "$(NAME_C) Compiled succesfully!"

%.o: %.c
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) $(FSANITIZE) $(LIBFT_INCLUDE) -c $< -o $@

$(LIBFT):
	@echo "Compiling libft..."
	@make -C $(LIBFT_DIR)

clean:
	@echo "Cleaning project objects..."
	@rm -f $(OBJ_S) $(OBJ_C)
	@echo "Cleaning libft completed!"
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Deep cleaning project executables..."
	@rm -f $(NAME_S) $(NAME_C)
	@echo "Deep cleaning libft archive..."
	@make -C $(LIBFT_DIR) fclean

re: fclean all
	@echo "Rebuilding project..."

.PHONY: all clean fclean re $(LIBFT_DIR)/clean $(LIBFT_DIR)/fclean
