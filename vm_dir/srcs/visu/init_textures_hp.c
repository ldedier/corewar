/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_hp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 21:21:32 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/11 16:32:56 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	free(tmp);
	return (str);
}

int		ft_init_rays(t_visu *visu, int i)
{
	char *str;

	if (!(str = get_prefixed_str(PATH"/resources/voldemort_light_", i + 1)))
		return (1);
	if (!(visu->frames[i].voldemort_ray.surface = ft_load_image(str)))
	{
		free(str);
		return (1);
	}
	visu->frames[i].voldemort_ray.screen_width = visu->frames[i].
		voldemort_ray.surface->w * visu->react.anim_ratio;
	free(str);
	if (!(str = get_prefixed_str(PATH"/resources/hp_light_", i + 1)))
		return (1);
	if (!(visu->frames[i].harry_ray.surface = ft_load_image(str)))
	{
		free(str);
		return (1);
	}
	visu->frames[i].harry_ray.screen_width = visu->frames[i].
		harry_ray.surface->w * visu->react.anim_ratio;
	free(str);
	return (0);
}

void	ft_init_hp_x_offsets(t_visu *visu)
{
	visu->frames[0].voldemort_ray.x_offset = 289 * visu->react.anim_ratio;
	visu->frames[1].voldemort_ray.x_offset = 292 * visu->react.anim_ratio;
	visu->frames[2].voldemort_ray.x_offset = 292 * visu->react.anim_ratio;
	visu->frames[3].voldemort_ray.x_offset = 291 * visu->react.anim_ratio;
	visu->frames[4].voldemort_ray.x_offset = 292 * visu->react.anim_ratio;
	visu->frames[0].harry_ray.x_offset = 740 * visu->react.anim_ratio;
	visu->frames[1].harry_ray.x_offset = 728 * visu->react.anim_ratio;
	visu->frames[2].harry_ray.x_offset = 728 * visu->react.anim_ratio;
	visu->frames[3].harry_ray.x_offset = 731 * visu->react.anim_ratio;
	visu->frames[4].harry_ray.x_offset = 728 * visu->react.anim_ratio;
}

int		ft_init_hp_surface(t_visu *visu)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < NB_FRAMES)
	{
		if (!(str = get_prefixed_str(PATH"/resources/background_", i + 1)))
			return (1);
		if (!(visu->frames[i].background = ft_load_image(str)))
		{
			free(str);
			return (1);
		}
		free(str);
	}
	visu->react.anim_ratio = (visu->center.dashboard_width - 1)
		/ (double)visu->frames[0].background->w;
	i = -1;
	while (++i < NB_FRAMES)
	{
		if (ft_init_rays(visu, i))
			return (1);
	}
	ft_init_hp_x_offsets(visu);
	return (0);
}
