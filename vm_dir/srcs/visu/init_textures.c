/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 21:26:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/06 14:38:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static inline int	ft_init_textures_1(t_visu *visu)
{
	if (!(visu->sdl.titles[ARENA] = ft_init_font_surface_sdl(
			"battlefield", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[LOCAL] = ft_init_font_surface_sdl(
			"local players", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[DOWNLOADS] = ft_init_font_surface_sdl(
			"downloaded", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[SCOREWAR] = ft_init_font_surface_sdl(
			"Scorewar server", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[UPLOAD_HERE] = ft_init_font_surface_sdl(
			"upload slot", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[SCORE] = ft_init_font_surface_sdl(
			"score:", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[NAME] = ft_init_font_surface_sdl(
			"name:", visu->sdl)))
		return (1);
	if (!(visu->sdl.titles[RANK] = ft_init_font_surface_sdl(
			"rank:", visu->sdl)))
		return (1);
	return (0);
}

static inline int	ft_init_textures_3(t_visu *visu)
{
	if (!(visu->sdl.images[SWITCH_2] = ft_load_image(
			PATH"/resources/switch_1.png")))
		return (1);
	if (!(visu->sdl.images[SWITCH_1] = ft_load_image(
			PATH"/resources/switch_2.png")))
		return (1);
	if (!(visu->sdl.images[NAME_TAKEN_NOTIF] = ft_load_image(
			PATH"/resources/already_taken.png")))
		return (1);
	if (!(visu->sdl.images[FROM_SERVER_NOTIF] = ft_load_image(
			PATH"/resources/upload_server.png")))
		return (1);
	if (!(visu->sdl.images[NAME_INVALID_NOTIF] = ft_load_image(
			PATH"/resources/invalid_name.png")))
		return (1);
	if (!(visu->sdl.images[LOST_CONNEXION_NOTIF] = ft_load_image(
			PATH"/resources/lost_connexion.png")))
		return (1);
	if (!(visu->sdl.images[OK] = ft_load_image(
			PATH"/resources/ok.png")))
		return (1);
	if (!(visu->sdl.images[BREAKDOWN_BAR] = ft_load_image(
			PATH"/resources/breakdown_bar.png")))
		return (1);
	return (0);
}

static inline int	ft_init_textures_4(t_visu *visu)
{
	if (!(visu->sdl.images[DL] = ft_load_image(PATH"/resources/download.png")))
		return (1);
	if (!(visu->sdl.images[UL] = ft_load_image(PATH"/resources/upload.png")))
		return (1);
	if (!(visu->sdl.images[SORT_ALPHA] = ft_load_image(
			PATH"/resources/alpha_sort.png")))
		return (1);
	if (!(visu->sdl.images[SORT_SCORE] = ft_load_image(
			PATH"/resources/score_sort.png")))
		return (1);
	if (!(visu->sdl.images[SCROLL_BAR] = ft_load_image(
			PATH"/resources/scroll_bar.png")))
		return (1);
	if (!(visu->sdl.images[SCROLL_DOWN] = ft_load_image(
			PATH"/resources/scroll_down.png")))
		return (1);
	if (!(visu->sdl.images[SCROLL_UP] = ft_load_image(
			PATH"/resources/scroll_up.png")))
		return (1);
	return (0);
}

static inline int	ft_init_textures_2(t_visu *visu)
{
	if (!(visu->sdl.images[TRASH] =
			ft_load_image(PATH"/resources/trash.png")))
		return (1);
	if (!(visu->sdl.images[TRASH_DISABLED] =
			ft_load_image(PATH"/resources/trash_disabled.png")))
		return (1);
	if (!(visu->sdl.images[BACK] =
			ft_load_image(PATH"/resources/back.png")))
		return (1);
	if (!(visu->sdl.images[CLOSE] = ft_load_image(PATH"/resources/close.png")))
		return (1);
	if (!(visu->sdl.images[FIGHT] = ft_load_image(PATH"/resources/fight.png")))
		return (1);
	if (!(visu->sdl.images[UL_DISABLED] =
				ft_load_image(PATH"/resources/upload_disabled.png")))
		return (1);
	if (!(visu->sdl.images[DL_DISABLED] =
				ft_load_image(PATH"/resources/download_disabled.png")))
		return (1);
	if (!(visu->sdl.images[KEYS] =
				ft_load_image(PATH"/resources/keys.png")))
		return (1);
	return (0);
}

int					ft_init_textures(t_visu *visu)
{
	if (ft_init_textures_1(visu))
		return (1);
	if (ft_init_textures_2(visu))
		return (1);
	if (ft_init_textures_3(visu))
		return (1);
	if (ft_init_textures_4(visu))
		return (1);
	return (0);
}
