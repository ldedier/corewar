/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:48:19 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 17:38:37 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <SDL2/SDL.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_ttf/SDL_ttf.h>
# include <SDL2_mixer/SDL_mixer.h>
# include <SDL2_net/SDL_net.h>
# include "libft.h"

# define NB_TEXTURES	10

typedef struct          s_sdl
{
	SDL_Rect			screen;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			*w_surface;
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	SDL_Color			color;
	SDL_Texture			*textures[NB_TEXTURES];
	TTF_Font			*font;
}						t_sdl;

typedef struct			s_dim
{
	int					width;
	int					height;
}						t_dim;

typedef struct          s_reactive
{
	double              w_scale;
	double              h_scale;
	int                 grass_border;
}                       t_reactive;

typedef struct			s_visu
{
	char				active;
	t_sdl				sdl;
	t_dim				dim;
	t_reactive			react;
}						t_visu;

#endif
