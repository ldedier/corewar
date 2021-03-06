/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_db.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 20:43:24 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/11 15:55:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

int		ft_process_add_to_db(char *path, t_list **players_list)
{
	t_player	player;

	if (ft_read_player(path, &player))
		return (2);
	if (ft_add_to_list_back(players_list, &player, sizeof(t_player)))
		return (1);
	return (0);
}

int		ft_process_add_to_list(DIR *dir, char *full_path, struct dirent *entry,
			t_list **players_list)
{
	int ret;

	if ((ret = ft_process_add_to_db(full_path, players_list)) == 1)
	{
		closedir(dir);
		return (ft_free_turn(full_path, 1));
	}
	else if (ret == 2)
		ft_dprintf(2, "%s could not be parsed as a valid .cor\n",
				entry->d_name);
	return (0);
}

int		ft_add_to_list(char *folder_full_name, DIR *dir,
			struct dirent *entry, t_list **players_list)
{
	char			*full_path;
	struct stat		st;

	if (!(full_path = ft_strjoin_3(folder_full_name, "/", entry->d_name)))
	{
		closedir(dir);
		return (1);
	}
	if (stat(full_path, &st) == -1)
	{
		perror(entry->d_name);
		closedir(dir);
		free(full_path);
		return (1);
	}
	if (S_ISREG(st.st_mode)
			&& ft_process_add_to_list(dir, full_path, entry, players_list))
		return (1);
	free(full_path);
	return (0);
}

int		ft_parse_player_folder(char *folder_full_name, t_list **players_list)
{
	DIR				*dir;
	struct dirent	*entry;

	*players_list = NULL;
	if (!(dir = opendir(folder_full_name)))
	{
		perror(folder_full_name);
		return (1);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_add_to_list(folder_full_name, dir, entry, players_list))
			return (1);
	}
	closedir(dir);
	return (0);
}
