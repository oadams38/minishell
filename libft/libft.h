/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:08:56 by oladams           #+#    #+#             */
/*   Updated: 2023/07/16 14:31:52 by oladams          ###   ########.fr       */
/*                                                                        	*/
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define OPEN_MAX 1024

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isnum(char *str);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_iswhite(char c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t n);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t n);
int			ft_atoi(const char *s);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *s, int max);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s, char const *set);
char		**ft_split(char const *s, char *charset);
char		*ft_strcat_free(char *a, char *b);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(char *s, int fd);
int			ft_putendl_fd(char *s, int fd);
int			ft_putnbr_fd(int n, int fd);
int			ft_free_tab(char **table);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
int			ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int			ft_lst_strcount(t_list *list, char *str);
char		**ft_lst_to_char_tab(t_list *start, t_list *end);

void		*ft_realloc(void *content, size_t size);
char		**ft_table_dup(char **table);
char		*ft_strjoin_multi(int n, ...);
int			ft_table_search(char **table, char *to_find);
char		**ft_table_add_back(char **table, char *str);
int			ft_multi_strncmp(int n_comp, ...);
int			ft_secure_free(void **ptr);
int			ft_get_table_size(char **table);
char		*ft_get_last_str(char **table);

//libft
int			ft_printf(const char *s, ...);
int			get_arg(va_list args, char conv, int *error);

//get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_buffer
{
	char	buffers[OPEN_MAX][BUFFER_SIZE + 1];
	int		index[OPEN_MAX];
}	t_buffer;

char		*get_next_line(int fd);

#endif
