/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 22:30:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/21 16:58:41 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

int			ft_return_verbosed(char *str, int ret)
{
	ft_dprintf(2, "%s\n", str);
	return (ret);
}

/*
**check_length static function is used by read_files to check the length of
**each file before storing it inside a structure, to avoid exceeding TOT_SIZE.
*/

static int	get_length(char *path, t_player *player)
{
	char	buffer[BUFF_SIZE + 1];
	int		fd;
	int		check;

	player->file_len = 0;
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		perror(path);
		return (-1);
	}
	while ((check = read(fd, buffer, BUFF_SIZE)) && player->file_len < TOT_SIZE)
		player->file_len += check;
	close(fd);
	return (player->file_len);
}

/*
**check_magic static function is used at the end of each read_files iteration
**to check if the magic number at the beginning of the file matches the correct
**magic number for a corewar .cor file, which is 0xea83f3.
*/

static int	check_mgc(t_player *player)
{
	int		mgc;
	char	*bin;

	bin = player->bin;
	mgc = (((bin[0] & 0xFF) << 24) | ((bin[1] & 0xFF) << 16) |
				((bin[2] & 0xFF) << 8) | (bin[3] & 0xFF));
	return (mgc == COREWAR_EXEC_MAGIC);
}

int			ft_process_read_player(char *data, int length, t_player *player)
{
	ft_memcpy(player->bin, data, length);
	player->file_len = length;
	player->bin[length] = '\0';
	if (!check_mgc(player))
	{
		ft_dprintf(2,
			"File has wrong magic number and is therefore not readable\n");
		return (1);
	}
	return (ft_parse_player(player));
}

int			ft_read_player(char *path, t_player *player)
{
	int fd;
	int ret;

	if (!path)
		return (1);
	if ((player->file_len = get_length(path, player)) == -1)
		return (1);
	if (player->file_len > TOT_SIZE)
		return (ft_return_verbosed(FILE_TOO_BIG, 1));
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		perror(path);
		return (1);
	}
	if ((read(fd, player->bin, player->file_len)) == -1)
	{
		perror(path);
		return (1);
	}
	ret = ft_process_read_player(player->bin, player->file_len, player);
	close(fd);
	return (ret);
}
