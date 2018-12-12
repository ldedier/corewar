/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:48:19 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/12 23:48:56 by ldedier          ###   ########.fr       */
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
# include "player.h"
# include "op.h"

# define FRAMERATE				60

# define DASHBOARD_X			1700
# define DASHBOARD_MID_Y		720

# define MEM_BORDER_TOP			100
# define MEM_BORDER_BOTTOM		100
# define MEM_BORDER_RIGHT		100
# define MEM_BORDER_LEFT		100


# define TITLE_BORDER_TOP		30
# define TITLE_BORDER_BOTTOM	40
# define TITLE_BORDER_SIDE		100
# define TITLE_HEIGHT			50

# define PLAYER_PADDING			50
# define PLAYER_BORDER_LEFT		50
# define PLAYER_BORDER_RIGHT	50
# define PLAYER_BORDER_BOTTOM	50

# define PLAYER_INNER_BORDER	6
# define CROSS_BORDER			PLAYER_INNER_BORDER * 3
# define CROSS_IB				CROSS_BORDER / 8

# define X_DIFF					7
# define X_DIFF_BYTE			0
# define Y_DIFF					7

# define MEM_COLS				64

# define NB_GLYPHS				256

# define NB_TITLES				5

# define BATTLEFIELD			0
# define LOCAL_PLAYERS			1
# define NET					2
# define COREWAR				3

# define NB_IMAGES				5

# define CLOSE					0

# define NB_CURSORS				5

# define GRAB					0
# define DRAGGABLE				1
# define CLICK					2
# define REGULAR				3

# define PLAYER_COL_BORDER		0x000000
# define PLAYER_COL				0x222222
# define BACKGROUND_COL			0x333333
# define PLAYER_BACKGROUND_COL	0x444444
# define PLAYER_HOVERED_BG_COL	0x666666
# define LINE_COL				0xffffff

# define DROP_TOLERANCE_W		100
# define DROP_TOLERANCE_H		30

typedef struct			s_vm t_vm;

typedef struct			s_atlas_char
{
	int					minx;
	int					maxx;
	int					miny;
	int					maxy;
	int					advance;
	SDL_Surface			*surface;
}						t_atlas_char;

typedef struct			s_cursor_packer
{
	SDL_Surface			*surface;
	SDL_Cursor			*cursor;
}						t_cursor_packer;

typedef struct          s_sdl
{
	SDL_Rect			screen;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			*w_surface;
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	SDL_Color			color;
	SDL_Surface			*images[NB_IMAGES];
	t_atlas_char		atlas[NB_GLYPHS];
	SDL_Surface			*titles[NB_TITLES];
	t_cursor_packer		cursor_packers[NB_CURSORS];
	TTF_Font			*font;
	int					current_cursor;
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

typedef struct			s_xy
{
	double				x;
	double				y;
}						t_xy;

typedef struct			s_slot
{
	t_xy				player;
	t_xy				close;
}						t_slot;

typedef struct			s_positions
{
	t_slot				arena_slots[MAX_PLAYERS];
	t_slot				local_slots[MAX_PLAYERS];
}						t_positions;

typedef struct			s_drag_container
{
	t_player			*player;
	int					x;
	int					y;
	int					diff_x;
	int					diff_y;
	char				from_arena;
}						t_drag_container;

typedef struct			s_drop_container
{
	t_player			*player;
}						t_drop_container;

typedef struct			s_event_manager
{
	Uint32				mouse_state;
	char				enable_mouse_up;
}						t_event_manager;

typedef struct			s_visu
{
	char				active;
	t_sdl				sdl;
	t_dim				dim;
	t_center			center;
	t_event_manager		event_manager;
	t_drag_container	drag_container;
	t_drop_container	drop_container;
	t_positions			positions;
	t_reactive			react;
	t_framerate			framerate;
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
int						ft_render_memory(t_vm *vm);
int						ft_render_players(t_vm *vm);
#endif
