/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 15:42:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/14 20:30:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# define BUFF_SIZE 4096

typedef struct	s_list	t_list;

typedef struct	s_gnl
{
	int			fd;
	int			size;
	char		*rest;
	char		*whole_buffer;
}				t_gnl;

typedef enum	e_separator
{
	E_SEPARATOR_ZERO = '\0',
	E_SEPARATOR_NL = '\n',
	E_SEPARATOR_EOF = EOF
}				t_separator;

typedef struct	s_gnl_info
{
	t_separator	separator;
	char		*line;
}				t_gnl_info;

int				ft_may_free_node(int ret, t_list **gnls, t_gnl *to_del);
t_gnl			*ft_get_gnl(int fd, t_list **gnls);
int				get_next_line(int const fd, char **line);
int				get_next_line2(int const fd, t_gnl_info *info);

#endif
