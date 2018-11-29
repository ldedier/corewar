/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:37:14 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/23 13:13:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# define BUFF_SIZE 4096

typedef struct	s_fd_buffer
{
	int			fd;
	char		*buffer;
}				t_fd_buffer;

int				get_next_line(int const fd, char **line);

#endif
