/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:03:52 by rchallie          #+#    #+#             */
/*   Updated: 2023/11/06 11:06:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define OPEN_MAX 
# define ALOT 99999

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stddef.h>

/* *********************************** */
/*                                     */
/*           libft regular             */
/*                                     */
/* *********************************** */
int		ft_isalnum(const int c);
int		ft_isalpha(const int c);
int		ft_isascii(const int c);
int		ft_isdigit(const int c);
int		ft_isprint(const int c);
int		ft_isnumber(const char *str);

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
double	ft_atod(const char *str);

int		ft_putstr_fd_1(char *str, int fd);
int		ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_putstr(char *s);
int		ft_putchar(char c);
int		ft_putnbr(int n);
int		ft_putullnbr(unsigned long long int n);
int		ft_puthexnbr(long long int n, int t);
int		ft_putptradd(void *p);

int		ft_pow(int base, int power);

void	*ft_memset(void *str, int c, size_t n);
void	ft_bzero(void *str, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
void	*ft_calloc(size_t count, size_t size);

int		ft_intlen(int nbr);
int		ft_longlen(long nbr);
int		shft_istab(char c);

char	*ft_strchr(const char *str, char c);
long	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(char *str, const char *needle, size_t len);
char	*ft_strrchr(const char *str, char c);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strdup(const char *str);
char	*ft_strdup_fr_to(const char *src, int from, int to);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strreplace(char *original, const char *new_value);
char	*ft_strncpy(char *dst, const char *src, int len);
int		ft_strcpy(char *dst, const char *src);

/* *********************************** */
/*                                     */
/*           libft bonus               */
/*                                     */
/* *********************************** */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *));

/* -------------------------------------------------------------------------- */
/*                                get_next_line                               */
/* -------------------------------------------------------------------------- */

int		has_char(char *test, char a);
char	*ft_my_strdup(char *todo);
int		ft_insert(char *dest, char *soos, int *i);
int		ft_charge_buff(char	*toch, int fd);
char	*get_next_line(int fd);

#endif
