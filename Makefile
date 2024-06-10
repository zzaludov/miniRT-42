# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 21:23:06 by zzaludov          #+#    #+#              #
#    Updated: 2023/04/25 21:41:52 by zzaludov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	:= miniRT 
CFLAGS	:= -Wextra -Wall -Werror
LIBMLX	:= MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
# LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBS := $(LIBMLX)/build/libmlx42.a -L/opt/homebrew/lib -ldl -lglfw -pthread -lm # for mac compilation
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@make -C FT_LIBRARY --no-print-directory
	@$(CC) $(OBJS) $(LIBS) ft_library.a $(HEADERS) -o $(NAME)
	@echo "$(NAME) built successfully"

clean:
	@rm -f $(OBJS)
	@cd FT_LIBRARY && $(MAKE) clean --no-print-directory

fclean: clean
	@rm -f $(NAME) ft_library.a
	@cd FT_LIBRARY && $(MAKE) fclean --no-print-directory
	@cd MLX42 && rm -rf build

re: clean all

.PHONY: all, clean, fclean, re, libmlx
