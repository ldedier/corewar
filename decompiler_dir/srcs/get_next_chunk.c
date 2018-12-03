/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_chunk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:16:24 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/03 17:31:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

int			get_next_chunk(int fd, t_chunk *chunk)
{
	chunk->size = read(fd, chunk->buf, CHUNK_SIZE);
	return (chunk->size );
}
