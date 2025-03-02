NAME = libft.a

SRCS = ft_isalpha.c \
	   ft_isdigit.c \
	   ft_isnum.c \
	   ft_isalnum.c \
	   ft_isascii.c \
	   ft_isprint.c \
	   ft_iswhite.c \
	   ft_strlen.c \
	   ft_memset.c \
	   ft_bzero.c \
	   ft_memcpy.c \
	   ft_memmove.c \
	   ft_strlcpy.c \
	   ft_strlcat.c \
	   ft_toupper.c \
	   ft_tolower.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_strncmp.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_strnstr.c \
	   ft_atoi.c \
	   ft_calloc.c \
	   ft_strdup.c \
	   ft_strndup.c \
	   ft_substr.c \
	   ft_substr.c \
	   ft_strjoin.c \
	   ft_strtrim.c \
	   ft_split.c \
	   ft_strcat_free.c \
	   ft_itoa.c \
	   ft_strmapi.c \
	   ft_striteri.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_free_tab.c \
	   ft_lstnew.c \
	   ft_lstadd_front.c \
	   ft_lstsize.c \
	   ft_lstlast.c \
	   ft_lstadd_back.c \
	   ft_lstdelone.c \
	   ft_lstclear.c \
	   ft_lstiter.c \
	   ft_lstmap.c \
	   ft_lst_strcount.c \
	   ft_lst_to_char_tab.c \
	   get_next_line/get_next_line.c \
	   ft_printf/ft_printf.c \
	   ft_printf/get_arg.c \
	   ft_printf/utils.c \
	   ft_realloc.c \
	   ft_table_dup.c \
	   ft_strjoin_multi.c \
	   ft_table_search.c \
	   ft_table_add_back.c \
	   ft_multi_strncmp.c \
	   ft_secure_free.c \
	   ft_get_table_size.c \
	   ft_get_last_str.c


OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

$(NAME)	:	$(OBJS)
			ar -rc $(NAME) $(OBJS) 

all		:	$(NAME)

clean	:
			rm -f $(OBJS)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
