/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:21:30 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/29 14:45:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "ft_printf.h"
# include "get_next_line.h"
# define MAX_INT 	2147483647

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_tree
{
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, void const *src, size_t n);
void				*ft_memccpy(void *dest, void const *src, int c, size_t n);
void				*ft_memmove(void *dest, void const *src, size_t n);
void				*ft_memchr(void const *s, int c, size_t n);
int					ft_memcmp(void const *s1, void const *s2, size_t n);
size_t				ft_strlen(char const *s);
char				*ft_strdup(char const *s);
char				*ft_strndup(char const *s, int n);
char				*ft_strcpy(char *dest, char const *src);
char				*ft_strncpy(char *dest, char const *src, size_t n);
char				*ft_strcat(char *dest, char const *src);
char				*ft_strncat(char *dest, char const *src, size_t n);
size_t				ft_strlcat(char *dest, char const *src, size_t n);
char				*ft_strchr(char const *s, int c);
char				*ft_strrchr(char const *s, int c);
char				*ft_strstr(char const *haystack, char const *needle);
char				*ft_strnstr(char const *hay, char const *ndle, size_t n);
int					ft_strcmp(char const *s1, char const *s2);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
int					ft_atoi(char const *s);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstnew_ptr(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *newelem);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_isseparator(int c);
int					ft_isseparator_light(int c);
void				ft_lstpushback(t_list **alst, t_list *newelem);
void				*ft_lstpop_ptr(t_list **lst);
void				ft_lstpop(t_list **lst);
int					ft_lstlength(t_list *list);
int					ft_add_to_list_ptr(t_list **list, void *content,
						size_t size);
int					ft_add_to_list_ptr_back(t_list **list, void *content,
						size_t size);
int					ft_add_to_list_back(t_list **list, void *content,
						size_t size);
void				ft_lstdel_ptr(t_list **list);
void				ft_lstdel_value(t_list **list);
int					ft_delete_node(t_list **prev, t_list **ptr, t_list **vs);
int					ft_delete_node_ptr(t_list **prv, t_list **ptr, t_list **vs);
void				ft_lst_mergesort(t_list **list,
						int (*sort)(void *, void *), int rev);

void				ft_sort_tab(int *tab, size_t size);

t_tree				*ft_tree_new_ptr(void *content);
void				ft_infix(t_tree *tree, void (*f)(t_tree *));
void				ft_prefix(t_tree *tree, void (*f)(t_tree *));
void				ft_postfix(t_tree *tree, void (*f)(t_tree *));
int					ft_tree_add_sorted_mul(t_tree **tree, void *content,
						int (*sort)(void *, void *), int mul);
int					ft_tree_add_sorted(t_tree **tree, void *content,
						int (*sort)(void *, void *));
void				ft_tree_del(t_tree **tree, void (*free_func)(void *));
void				ft_tree_del_value(t_tree **tree);
void				ft_tree_del_ptr(t_tree **tree);
int					ft_treelen(t_tree *tree);
void				*ft_tree_at_infix(t_tree *tree, int index);
int					get_next_line(const int fd, char **line);

void				ft_free_split(char **split);
int					ft_abs(int a);
int					ft_min(int a, int b);
int					ft_max(int a, int b);
double				ft_fmin(double a, double b);
double				ft_fmax(double a, double b);
int					ft_splitlen(char **split);
int					ft_clamp(int min, int val, int max);
float				ft_fclamp(float min, float val, float max);
float				ft_atof(char const *s);
double				ft_patof(char **str, int *scss);
int					ft_patoi(char **str);
unsigned int		ft_patoi_hex(char **str, int *scss);
int					ft_isspace(int c);
int					ft_onesign(int n);
void				ft_print_line(char *str);
char				*ft_strjoin_3(char const *s1, char const *s2,
						char const *s3);
int					ft_free_turn(void *to_free, int ret);
#endif
