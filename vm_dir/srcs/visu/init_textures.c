/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:02:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/04 03:13:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_init_textures_1(t_visu *visu)
{
	if (!(visu->sdl.titles[ARENA] =
				ft_init_font_surface_sdl("battlefield", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[LOCAL] =
				ft_init_font_surface_sdl("local players", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[DOWNLOADS] =
				ft_init_font_surface_sdl("downloaded", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[SCOREWAR] =
				ft_init_font_surface_sdl("Scorewar server", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[UPLOAD_HERE] =
				ft_init_font_surface_sdl("upload slot", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[SCORE] =
				ft_init_font_surface_sdl("score:", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[NAME] =
				ft_init_font_surface_sdl("name:", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[RANK] =
				ft_init_font_surface_sdl("rank:", visu->sdl)))
		return (1);
	if (!(visu->sdl.images[CLOSE] = ft_load_image(PATH"/resources/close.png")))
		return (1);
	return (0);
}

int		ft_init_textures_2(t_visu *visu)
{
	if (!(visu->sdl.images[DL] = ft_load_image(PATH"/resources/download.png")))
		return (1);
	if (!(visu->sdl.images[UL] = ft_load_image(PATH"/resources/upload.png")))
		return (1);
	if (!(visu->sdl.images[SORT_ALPHA] =
			ft_load_image(PATH"/resources/alpha_sort.png")))
		return (1);
	if (!(visu->sdl.images[SORT_SCORE] =
			ft_load_image(PATH"/resources/score_sort.png")))
		return (1);
	if (!(visu->sdl.images[SCROLL_BAR] =
			ft_load_image(PATH"/resources/scroll_bar.png")))
		return (1);
	if (!(visu->sdl.images[SCROLL_DOWN] =
			ft_load_image(PATH"/resources/scroll_down.png")))
		return (1);
	if (!(visu->sdl.images[SCROLL_UP] =
			ft_load_image(PATH"/resources/scroll_up.png")))
		return (1);
	if (!(visu->sdl.images[TRASH] =
			ft_load_image(PATH"/resources/trash.png")))
		return (1);
	if (!(visu->sdl.images[TRASH_DISABLED] =
			ft_load_image(PATH"/resources/trash_disabled.png")))
		return (1);
	if (!(visu->sdl.images[SWITCH_2] =
			ft_load_image(PATH"/resources/switch_1.png")))
		return (1);
	if (!(visu->sdl.images[SWITCH_1] =
			ft_load_image(PATH"/resources/switch_2.png")))
		return (1);
	if (!(visu->sdl.images[NAME_TAKEN_NOTIF] =
			ft_load_image(PATH"/resources/already_taken.png")))
		return (1);
	if (!(visu->sdl.images[FROM_SERVER_NOTIF] =
			ft_load_image(PATH"/resources/upload_server.png")))
		return (1);
	if (!(visu->sdl.images[OK] =
			ft_load_image(PATH"/resources/ok.png")))
		return (1);
	if (!(visu->sdl.images[BREAKDOWN_BAR] =
			ft_load_image(PATH"/resources/breakdown_bar.png")))
		return (1);
	if (!(visu->sdl.images[BACK] =
			ft_load_image(PATH"/resources/back.png")))
		return (1);
	return (0);
}

char	*get_prefixed_str(char *prefix, int i)
{
	char *str;
	char *tmp;

	if (!(tmp = ft_itoa(i)))
		return (NULL);
	if (!(str = ft_strjoin_3(prefix, tmp, ".png")))
	{
		free(tmp);
		return (NULL);
	}
	return (str);
}


int		ft_init_hp_surface(t_visu *visu)
{
	int i;
	char *str;

	i = 0;
	while (i < NB_FRAMES)
	{
		if (!(str = get_prefixed_str(PATH"/resources/background_", i + 1)))
			return (1);
		if (!(visu->frames[i].background = ft_load_image(str)))
		{
			free(str);
			return (1);
		}
		free(str);
		if (!(str = get_prefixed_str(PATH"/resources/voldemort_light_", i + 1)))
			return (1);
		if (!(visu->frames[i].voldemort_ray = ft_load_image(str)))
		{
			free(str);
			return (1);
		}
		free(str);
		if (!(str = get_prefixed_str(PATH"/resources/hp_light_", i + 1)))
			return (1);
		if (!(visu->frames[i].harry_ray = ft_load_image(str)))
		{
			free(str);
			return (1);
		}
		free(str);
		i++;
	}
	return (0);
}

int		ft_init_textures(t_visu *visu)
{
	if (ft_init_textures_1(visu))
		return (1);
	if (ft_init_textures_2(visu))
		return (1);
	if (ft_init_hp_surface(visu))
	{
		ft_printf("OLALALAb\n");
		return (1);
	}
	if (!(visu->sdl.images[FIGHT] = ft_load_image(PATH"/resources/fight.png")))
		return (1);
	if (!(visu->sdl.images[UL_DISABLED] =
				ft_load_image(PATH"/resources/upload_disabled.png")))
		return (1);
	if (!(visu->sdl.images[DL_DISABLED] =
				ft_load_image(PATH"/resources/download_disabled.png")))
		return (1);
	return (0);
}

int		ft_populate_cursor(t_cursor_packer *cp, char *str, int hot_x, int hot_y)
{
	if (!(cp->surface = ft_load_image(str)))
		return (1);
	if (!(cp->cursor = SDL_CreateColorCursor(cp->surface, hot_x, hot_y)))
	{
		//free ?
		return (1);
	}
	return (0);
}

int		ft_init_cursors(t_visu *v)
{
	if (ft_populate_cursor(&(v->sdl.cursor_packers[GRAB]),
				PATH"/resources/grab.png", 7, 3))
		return (1);
	if (ft_populate_cursor(&(v->sdl.cursor_packers[DRAGGABLE]),
				PATH"/resources/draggable.png", 7, 5))
		return (1);
	if (ft_populate_cursor(&(v->sdl.cursor_packers[CLICK]),
				PATH"/resources/click.png", 5, 0))
		return (1);
	if (ft_populate_cursor(&(v->sdl.cursor_packers[REGULAR]),
				PATH"/resources/regular.png", 0, 0))
		return (1);
	return (0);
}
