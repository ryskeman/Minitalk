# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fernando <fernafer@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/17 02:31:13 by fernando          #+#    #+#              #
#    Updated: 2025/08/18 20:50:08 by fernando         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_S = server
NAME_C = client

NAME_S_BONUS = server_bonus
NAME_C_BONUS = client_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -Includes/
FSANITIZE = -fsanitize=address -g3

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE = -I$(LIBFT_DIR)/

SRC_S = server.c
SRC_C = client.c

SRC_S_BONUS = server_bonus.c
SRC_C_BONUS = client_bonus.c

OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)

OBJ_S_BONUS = $(SRC_S_BONUS:.c=.o)
OBJ_C_BONUS = $(SRC_C_BONUS:.c=.o)

all: $(NAME_S) $(NAME_C)

$(NAME_S): $(LIBFT) $(OBJ_S)
	@echo "Linking $(NAME_S)..."
	$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ_S) $(LIBFT) -o $(NAME_S)
	@echo "$(NAME_S) Compiled succesfully!"

$(NAME_C): $(LIBFT) $(OBJ_C)
	@echo "Linking $(NAME_C)..."
	$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ_C) $(LIBFT) -o $(NAME_C)
	@echo "$(NAME_C) Compiled succesfully!"

bonus: $(NAME_S_BONUS) $(NAME_C_BONUS)

$(NAME_S_BONUS): $(LIBFT) $(OBJ_S_BONUS)
	@echo "Linking $(NAME_S_BONUS)..."
	$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ_S_BONUS) $(LIBFT) -o $(NAME_S_BONUS)
	@echo "$(NAME_S_BONUS) Compiled succesfully!"

$(NAME_C_BONUS): $(LIBFT) $(OBJ_C_BONUS)
	@echo "Linking $(NAME_C_BONUS)..."
	$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ_C_BONUS) $(LIBFT) -o $(NAME_C_BONUS)
	@echo "$(NAME_C_BONUS) Compiled succesfully!"

%.o: %.c
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) $(FSANITIZE) $(LIBFT_INCLUDE) -c $< -o $@

$(LIBFT):
	@echo "Compiling libft..."
	@make -C $(LIBFT_DIR)

clean:
	@echo "Cleaning project objects..."
	@rm -f $(OBJ_S) $(OBJ_C) $(OBJ_S_BONUS) $(OBJ_C_BONUS)
	@echo "Cleaning libft completed!"
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Deep cleaning project executables..."
	@rm -f $(NAME_S) $(NAME_C) $(NAME_S_BONUS) $(NAME_C_BONUS)
	@echo "Deep cleaning libft archive..."
	@make -C $(LIBFT_DIR) fclean

re: fclean all
	@echo "Rebuilding project..."

.PHONY: all bonus clean fclean re $(LIBFT_DIR)/clean $(LIBFT_DIR)/fclean
