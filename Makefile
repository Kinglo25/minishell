# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwastche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 18:34:52 by cwastche          #+#    #+#              #
#    Updated: 2022/04/06 18:34:53 by cwastche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

PARS        = main.c \
              parsing/parser.c \
              parsing/ft_strtok.c \
              parsing/ft_strtok_utils.c \
              parsing/utils.c \
              parsing/utils_2.c \
              parsing/utils_3.c \
              parsing/utils_4.c \
              parsing/parser_utils.c \
              parsing/check_env_var.c \
              parsing/check_env_var_utils.c

EXE         = exec/builtins.c \
              exec/exec.c \
              exec/heredoc.c \
              exec/utils.c

BIN         = builtins/echo.c \
              builtins/cd.c \
              builtins/export.c \
              builtins/unset.c \
              builtins/env.c \
              builtins/exit.c \
              builtins/pwd.c
              
LIBFT       = ./libft/

NAMELFT     = ./libft/libft.a

OBJS        = $(PARS:.c=.o) $(EXE:.c=.o) $(BIN:.c=.o)

CC          = gcc

CFLAGS      = -Wall -Wextra -g3

INC         = -I./inc/

all:        $(OBJS) $(NAME)

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $(INC) $< -o $(<:.c=.o)
	@echo "Compiling OK!"

$(NAME): $(OBJS)
	@make -C ./libft
	@echo "Linking $^"
	@$(CC) $(CFLAGS) $(OBJS) $(NAMELFT) -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -ltermcap -o $@
	@echo "Executable created!"

clean:
	@echo "Cleaning objects..."
	@rm -f $(OBJS)
	@echo "Cleaned up!"

fclean: clean
	@make fclean -C ./libft
	@echo "Removing executable..."
	@rm -f $(NAME)
	@echo "Removed!"

re: fclean all

.PHONY: all clean fclean re
