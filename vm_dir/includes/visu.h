/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:48:19 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/13 21:26:39 by ldedier          ###   ########.fr       */
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

# define DASHBOARD_X			1900
# define TOP_DASHBOARD_HEIGHT	600

# define MEM_BORDER_TOP			100
# define MEM_BORDER_BOTTOM		100
# define MEM_BORDER_RIGHT		100
# define MEM_BORDER_LEFT		100

# define TITLE_BORDER_TOP		30
# define TITLE_BORDER_BOTTOM	40
# define TITLE_BORDER_SIDE		30
# define TITLE_HEIGHT			50

# define PLAYER_PADDING			50
# define PLAYER_BORDER_LEFT		50
# define PLAYER_BORDER_RIGHT	50
# define PLAYER_BORDER_BOTTOM	50

# define PLAYER_INNER_BORDER	6
# define CROSS_BORDER			PLAYER_INNER_BORDER * 3
# define CROSS_IB				CROSS_BORDER / 8

# define S_TITLE_SIDE			100
# define S_TITLE_HEIGHT			50

# define UPLOAD_LEFT			PLAYER_BORDER_LEFT / 2
# define UPLOAD_RIGHT			PLAYER_BORDER_LEFT / 2
# define SORT_PADDING			50
# define SORT_SCORE_RIGHT		PLAYER_BORDER_LEFT / 2

# define X_DIFF					7
# define X_DIFF_BYTE			0
# define Y_DIFF					7

# define MEM_COLS				64

# define NB_GLYPHS				256

# define NB_TITLES				5

# define BATTLEFIELD			0
# define LOCAL_PLAYERS			1
# define SCOREWAR				2
# define COREWAR				3

# define NB_IMAGES				10

# define CLOSE					0
# define DL						1
# define UL						2
# define SORT_ALPHA				3
# define SORT_SCORE				4

# define NB_CURSORS				5

# define GRAB					0
# define DRAGGABLE				1
# define CLICK					2
# define REGULAR				3

# define NB_BUTTONS				3

# define UPLOAD_BUTTON			0
# define ALPHA_SORT_BUTTON		1
# define SCORE_SORT_BUTTON		2

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

typedef enum			e_player_source
{
	ARENA,
	LOCAL,
	UPLOAD,
	SERVER
}						t_player_source;

typedef struct			s_button
{
	SDL_Rect			rect;
	void				(*action)();
}						t_button;

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
	t_button			buttons[NB_BUTTONS];
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

	double				dashboard_x;
	double				top_dashboard_height;
	double				dashboard_mid_x;
	double				dashboard_mid_width;
	double				dashboard_width;
	double				bottom_dash_height;

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

	double				upload_left;
	double				upload_right;
	double				sort_padding;
	double				sort_score_right;
	double				toolbar_blank;
	double				s_title_h;
	double				s_title_side;
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
	t_slot				upload_slot;
}						t_positions;

typedef struct			s_drag_container
{
	t_player			*player;
	t_player_source		source;
	int					x;
	int					y;
	int					diff_x;
	int					diff_y;
}						t_drag_container;

typedef struct			s_drop_container
{
	t_player			*player;
}						t_drop_container;

typedef enum			e_clickable_nature
{
	BUTTON,
	PLAYER_CROSS
}						t_clickable_nature;

typedef struct			s_clickable_container
{
	t_clickable_nature	clickable_nature;
	void				*clickable;
}						t_clickable_container;

typedef struct			s_event_manager
{
	Uint32				mouse_state;
	char				enable_mouse_up;
}						t_event_manager;

typedef struct			s_color_manager
{
	int					color;
	char				r;
	char				g;
	char				b;
}						t_color_manager;

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
int						ft_render_online(t_vm *vm);
int						ft_render_offline(t_vm *vm);
t_color_manager			ft_get_color(int color);
t_color_manager			ft_scale_color(t_color_manager color, double scale);
int						ft_render_player(t_vm *vm, t_player *player, t_xy xy,
							t_player_source source);
int						ft_render_dragged_player(t_vm *vm);
int						ft_is_on_close(t_vm *vm, int x, int y,
							t_player **player);
int						ft_is_on_draggable(t_vm *vm, int x, int y,
							t_drag_container *dc);
int						ft_is_on_droppable(t_vm *vm, int x, int y,
							t_player **to_drop_on);
void					ft_drop_dragged_player(t_vm *vm, int x, int y);
void					ft_update_cursor(t_vm *vm, int x, int y);
void					ft_change_cursor(t_vm *vm, int index);
int						ft_is_on_clickable(t_vm *vm, int x, int y,
							t_player **player);
#endif
