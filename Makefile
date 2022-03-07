NAME		=	minishell

SRCS		=	srcs/main.c srcs/parser.c srcs/ft_strtok.c \
				srcs/ft_strtok_utils.c srcs/utils.c \
				srcs/parser_utils.c \
				
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
