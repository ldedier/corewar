/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_db.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 20:43:24 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 22:15:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		ft_process_add_to_db(char *filename, t_server *server)
{
	t_core	*core;
	char	*name;

	if (!(name = ft_strdup(filename)))
		return (1);
	if (!(core = ft_new_core(filename, -1)))
		return (ft_free_turn(name, 1));
	if (ft_add_to_list_ptr(&(server->cores), core, sizeof(t_core)))
	{
		free(name);
		free(core);
		return (1);
	}
	return (0);
}

int		ft_add_to_db(DIR *dir, struct dirent *entry, t_server *server)
{
	char			*full_path;
	struct stat		st;

	if (!(full_path = ft_strjoin(PATH"/cores/", entry->d_name)))
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
	if (S_ISREG(st.st_mode))
	{
		if (ft_process_add_to_db(entry->d_name, server))
		{
			closedir(dir);
			return (ft_free_turn(full_path, 1));
		}
	}
	free(full_path);
	return (0);
}

int		ft_init_db(t_server *server)
{
	DIR				*dir;
	struct dirent	*entry;

	server->cores = NULL;
	if (!(dir = opendir(PATH"/cores")))
	{
		perror(PATH"/cores");
		return (1);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_add_to_db(dir, entry, server))
			return (1);
	}
	closedir(dir);
	return (0);
}
