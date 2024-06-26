# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomajeru <lomajeru@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 18:34:52 by cwastche          #+#    #+#              #
#    Updated: 2024/06/04 16:36:38 by lomajeru         ###   ########.fr        #
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

CFLAGS      = -Wall -Wextra -Werror

INC         = -I./inc/

all:        $(OBJS) $(NAME)

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $(INC) $< -o $(<:.c=.o)
	@echo "Compiling OK!"

$(NAME): $(OBJS)
	@make -C ./libft
	@echo "Linking $^"
	@$(CC) $(CFLAGS) $(OBJS) $(NAMELFT) -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/include/readline/ -ltermcap -o $@
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
