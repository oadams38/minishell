NAME		 =	minishell

DIR_SRCS	 =	srcs/
DIR_BUILTINS =	builtins/
DIR_EXECUTOR =	exec/
DIR_PARSING_EXPANDER =	parsing_expander/
DIR_SHELL =	shell/
DIR_UTILS =	utils/

SRCS		 = \
				$(DIR_BUILTINS)cd.c \
				$(DIR_BUILTINS)echo.c \
				$(DIR_BUILTINS)env.c \
				$(DIR_BUILTINS)exit.c \
				$(DIR_BUILTINS)export.c \
				$(DIR_BUILTINS)export_concat.c \
				$(DIR_BUILTINS)export_utils.c \
				$(DIR_BUILTINS)pwd.c \
				$(DIR_BUILTINS)unset.c \
				$(DIR_EXECUTOR)executor.c \
				$(DIR_EXECUTOR)executor_utils.c \
				$(DIR_EXECUTOR)parent_process.c \
				$(DIR_EXECUTOR)path.c \
				$(DIR_EXECUTOR)pipe.c \
				$(DIR_EXECUTOR)process.c \
				$(DIR_EXECUTOR)signal.c \
				$(DIR_EXECUTOR)fd.c \
				$(DIR_PARSING_EXPANDER)cmd_table.c \
				$(DIR_PARSING_EXPANDER)cmd_table_utils.c \
				$(DIR_PARSING_EXPANDER)expander.c \
				$(DIR_PARSING_EXPANDER)expander_utils.c \
				$(DIR_PARSING_EXPANDER)init.c \
				$(DIR_PARSING_EXPANDER)init_utils.c \
				$(DIR_PARSING_EXPANDER)readline.c \
				$(DIR_PARSING_EXPANDER)redirection.c \
				$(DIR_PARSING_EXPANDER)redirection_utils.c \
				$(DIR_PARSING_EXPANDER)token.c \
				$(DIR_PARSING_EXPANDER)token_utils.c \
				$(DIR_SHELL)clear.c \
				$(DIR_SHELL)error.c \
				$(DIR_SHELL)error_utils.c \
				$(DIR_SHELL)exit.c \
				$(DIR_SHELL)shell.c \
				$(DIR_SHELL)shell_utils.c \
				$(DIR_UTILS)get_next_line_signals.c \
				$(DIR_UTILS)is_1.c \
				$(DIR_UTILS)is_2.c \
				$(DIR_UTILS)is_3.c \
				$(DIR_UTILS)utils_1.c \
				$(DIR_UTILS)utils_2.c \
				main.c
				

PATH_SRCS	=	$(addprefix $(DIR_SRCS), $(SRCS))

OBJS		=	$(PATH_SRCS:.c=.o)

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra

$(NAME)		:	$(OBJS)
				make -C ./libft/
				$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME) -lreadline -fsanitize=address

all			:	$(NAME)

clean_libft	:
				make -C ./libft/ clean

fclean_libft	:
				make -C ./libft/ fclean

re_libft	:
				make -C ./libft/ re

clean		:	clean_libft
				rm -f $(OBJS)

fclean		:	fclean_libft clean
				rm -f $(NAME)

re			:	fclean all
				
.PHONY		:	all clean fclean re
