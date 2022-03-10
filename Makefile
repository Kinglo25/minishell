NAME		=	minishell

SRCS		=	main.c \
				srcs/parsing/parser.c \
				srcs/parsing/ft_strtok.c \
				srcs/parsing/ft_strtok_utils.c \
				srcs/parsing/utils.c \
				srcs/parsing/parser_utils.c \
				srcs/parsing/check_env_var.c \
				
OBJS		=	$(SRCS:c=o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

INC			= 	-I./inc/

all:			$(OBJS) $(NAME)

%.o:		%.c
				@echo "Compiling $<"
				@$(CC) $(CFLAGS) -c $(INC) $< -o $(<:c=o)
				@echo "Compiling OK!"

$(NAME):	$(OBJS)
				@echo "Linking $^"
				@cc $(CFLAGS) $^ -o $@ -lreadline
				@echo "Executable created!"
clean:
				@echo "Cleaning objects..."
				@rm -f $(OBJS) $(BONUS_OBJS)
				@echo "Cleaned up!"

fclean:		clean
				@echo "Removing executable..."
				@rm -f $(NAME)
				@echo "Removed!"

re:			fclean all

.PHONY:		all clean fclean re
