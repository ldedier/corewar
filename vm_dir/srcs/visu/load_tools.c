/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:48:28 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/19 20:49:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

TTF_Font    *ft_load_font(char *str, int quality)
{
	TTF_Font *font;

	font = TTF_OpenFont(str, quality);
	if (font == NULL)
		ft_net_error();
	return (font);
}

SDL_Surface *ft_load_image(char *str)
{
	SDL_Surface *surface;

	if (!(surface = IMG_Load(str)))
		ft_net_error();
	return (surface);
}
