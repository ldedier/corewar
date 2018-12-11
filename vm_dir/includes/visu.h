/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:48:19 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/11 14:27:09 by ldedier          ###   ########.fr       */
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
# define NB_TEXTURES		10
# define FRAMERATE			60

# define DASHBOARD_X		1700
# define DASHBOARD_MID_Y	720

# define MEM_BORDER_TOP		100
# define MEM_BORDER_BOTTOM	100
# define MEM_BORDER_RIGHT	100
# define MEM_BORDER_LEFT	100


# define TITLE_BORDER_TOP		40
# define TITLE_BORDER_BOTTOM	30
# define TITLE_BORDER_SIDE		100
# define TITLE_HEIGHT			50

# define PLAYER_PADDING			50
# define PLAYER_BORDER_LEFT		50
# define PLAYER_BORDER_RIGHT	50
# define PLAYER_BORDER_BOTTOM	50

# define X_DIFF				7
# define X_DIFF_BYTE		0
# define Y_DIFF				7

# define MEM_COLS			64
# define NB_GLYPHS			256
# define NB_TITLES			5

# define BATTLEFIELD		0
# define LOCAL_PLAYERS		1
# define NET				2
# define COREWAR			3


typedef struct			s_vm t_vm;

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
	SDL_Surface			*atlas[NB_GLYPHS];
	SDL_Surface			*titles[NB_TITLES];
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

typedef struct          s_framerate
{
	Uint64				current;
	Uint64				previous;
	double				delta;
	int					fps_counter;
	Uint32				ms_counter;
}                       t_framerate;

typedef struct			s_center
{
	double				dashboard_x;
	double				dashboard_mid_y;
	double				dashboard_mid_x;
	double				left_margin;
	double				right_margin;
	double				top_margin;
	double				bottom_margin;
	double				x_diff;
	double				x_diff_byte;
	double				y_diff;
	double				glyph_width;
	double				glyph_height;
	int					nb_cols;
	int					nb_lines;
	double				dashboard_mid_width;
	double				title_top;
	double				title_h;
	double				title_side;
	double				title_bottom;

	double				player_left;
	double				player_right;
	double				player_w;
	double				player_h;
	double				player_padding;
	double				player_bottom;
}						t_center;

typedef struct			s_visu
{
	char				active;
	t_sdl				sdl;
	t_dim				dim;
	t_center			center;
	t_reactive			react;
	t_framerate			framerate;
	SDL_Rect			mem;
}						t_visu;

int						ft_init_all_sdl(t_visu *v);

/*
** framerate functions
*/

void					ft_process_delta_first(t_framerate *framerate);
void					ft_process_delta(t_framerate *framerate);
void					ft_print_fps(t_framerate *framerate);
int						ft_process_events(t_vm *vm);
int						ft_render(t_vm *vm, t_sdl *sdl);
#endif
