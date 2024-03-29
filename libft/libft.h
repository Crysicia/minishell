/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crysicia <crysicia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 01:17:22 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/28 16:34:33 by crysicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# define POSITIVE 1
# define NEGATIVE -1

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strnstr(const char *haystack,
						const char *needle, size_t len);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_strndup(char *str, size_t n);

/*
**	Tab utils
*/

char				**ft_tabdup(char *tab[]);

/*
** 42 functions
*/
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
** Bonus functions
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst,
						void *(*f)(void *), void (*del)(void *));

/*
** Custom functions
*/
typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*previous;
	struct s_dlist	*next;
}	t_dlist;

int					ft_max(int a, int b);
int					ft_min(int a, int b);
char				*ft_strjoin_free(char const *s1, char const *s2);
int					ft_matrix_size(void **matrix);
void				*ft_free_matrix(void **matrix, size_t size);
char				*ft_strcchr(const char *s, int c);
char				**ft_split_set(const char *s, char *set);
int					ft_in_range(int min, int max, int value);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_lstsort(t_list **head, int (*cmp)());
t_list				*ft_lstnew_safe(void *content, void (*del)(void *));
int					ft_isspace(int c);

t_dlist				*ft_dlstnew(void *content);
void				ft_dlstadd_front(t_dlist **alst, t_dlist *new);
int					ft_dlstsize(t_dlist *lst);
t_dlist				*ft_dlstlast(t_dlist *lst);
void				ft_dlstadd_back(t_dlist **alst, t_dlist *new);
void				ft_dlstdelone(t_dlist *lst, void (*del)(void *));
void				ft_dlstclear(t_dlist **lst, void (*del)(void *));

#endif
