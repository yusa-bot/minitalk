# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/15 19:43:43 by ayusa             #+#    #+#              #
#    Updated: 2025/07/15 21:59:37 by ayusa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server

NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_CLIENT = client.c
SRC_SERVER = server.c

SRC_BONUS_CLIENT = client_bonus.c
SRC_BONUS_SERVER = server_bonus.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

OBJ_BONUS_CLIENT = $(SRC_BONUS_CLIENT:.c=.o)
OBJ_BONUS_SERVER = $(SRC_BONUS_SERVER:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

LIBFT_DIR = libft
FT_PRINTF_DIR = ft_printf

LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/ft_printf.a

all: $(LIBFT) $(FT_PRINTF) $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $@ $(OBJ_CLIENT) $(FT_PRINTF) $(LIBFT)

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $@ $(OBJ_SERVER) $(FT_PRINTF) $(LIBFT)

$(NAME_CLIENT_BONUS): $(OBJ_BONUS_CLIENT)
	$(CC) $(CFLAGS) -o $@ $(OBJ_BONUS_CLIENT) $(FT_PRINTF) $(LIBFT)

$(NAME_SERVER_BONUS): $(OBJ_BONUS_SERVER)
	$(CC) $(CFLAGS) -o $@ $(OBJ_BONUS_SERVER) $(FT_PRINTF) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

bonus: $(LIBFT) $(FT_PRINTF) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

clean:
	$(RM) $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_BONUS_CLIENT) $(OBJ_BONUS_SERVER)
	make -C $(LIBFT_DIR) clean
	make -C $(FT_PRINTF_DIR) clean

fclean: clean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)
	make -C $(LIBFT_DIR) fclean
	make -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
