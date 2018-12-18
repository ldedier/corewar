/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:48:19 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/16 18:01:53 by ldedier          ###   ########.fr       */
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
# include "color.h"
# include "op.h"

# define FRAMERATE				60

# define DASHBOARD_X			1900
# define TOP_DASHBOARD_HEIGHT	580
# define FOOTER_HEIGHT			100

# define MEM_BORDER_TOP			100
# define MEM_BORDER_BOTTOM		100
# define MEM_BORDER_RIGHT		100
# define MEM_BORDER_LEFT		100

# define TITLE_BORDER_TOP		30
# define TITLE_BORDER_BOTTOM	25
# define TITLE_BORDER_SIDE		30
# define TITLE_HEIGHT			50

# define PLAYER_PADDING			50
# define PLAYER_BORDER_LEFT		50
# define PLAYER_BORDER_RIGHT	50
# define PLAYER_BORDER_BOTTOM	50

# define PLAYER_INNER_BORDER	6
# define CROSS_BORDER			PLAYER_INNER_BORDER * 3
# define CROSS_IB				0

# define S_TITLE_SIDE			100
# define S_TITLE_HEIGHT			50

# define UPLOAD_LEFT			PLAYER_BORDER_LEFT / 2
# define UPLOAD_RIGHT			PLAYER_BORDER_LEFT / 2
# define SORT_PADDING			20
# define SORT_SCORE_RIGHT		PLAYER_BORDER_LEFT / 2
# define TOOLBAR_BOTTOM			30

# define X_DIFF					7
# define X_DIFF_BYTE			0
# define Y_DIFF					7

# define MEM_COLS				64

# define NB_GLYPHS				256

# define NB_TITLES				5

# define BATTLEFIELD			0
# define LOCAL_PLAYERS			1
# define SCOREWAR				2
# define UPLOAD_HERE			3
# define COREWAR				4

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
# define UPLOAD_COLOR			PLAYER_BACKGROUND_COL
# define LINE_COL				0xffffff

# define DROP_TOLERANCE_W		100
# define DROP_TOLERANCE_H		30

typedef struct			s_vm t_vm;

typedef struct			s_atlas_char
{
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

typedef union			u_button_union
{
	char				*name;
	t_player			*player;
}						t_button_union;

typedef struct			s_xy
{
	double				x;
	double				y;
}						t_xy;

typedef struct			s_ixy
{
	int					x;
	int					y;
}						t_ixy;

typedef struct			s_button
{
	SDL_Rect			rect;
	SDL_Surface			*surface;
	t_button_union		button_union;
	char				visible;
	void				(*on_click)(t_vm *, struct s_button *, t_ixy xy);
	void				(*on_hover)(t_vm *, struct s_button *, t_ixy xy);
}						t_button;

/*
** vertical scrollbar:
** height:				the size of the section on the screen
** compressed_height:	the actual size inside it (>= height)
** state:				0 top, 1 bottom
** pos:					bar position
** y:					whole scrollbar y coordinate
*/

typedef struct			s_vscrollbar
{
	t_xy				pos;
	double				state;
	int					y;
	int					height;
	int					compressed_height;
	int					bar_width;
}						t_vscrollbar;

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
	t_atlas_char		atlas[MAX_PL_COLOR + 1][NB_GLYPHS];
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

	double				mid_dashboard_height;
	double				footer_height;
	double				footer_y;

	double				title_top;
	double				title_h;
	double				title_side;
	double				title_bottom;

	int					player_left;
	int					player_right;
	int					player_w;
	int					player_h;
	double				player_padding;
	double				player_bottom;

	int					cross_border;
	int					player_inner_border;

	double				upload_left;
	double				upload_right;
	double				sort_padding;
	double				sort_score_right;
	double				toolbar_blank;
	double				toolbar_bottom;
	double				s_title_h;
	double				s_title_side;
}						t_center;


typedef struct			s_slot
{
	t_xy				player;
	t_button			close;
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
	t_button			*close;
	t_player_source		source;
	int					x;
	int					y;
	int					diff_x;
	int					diff_y;
}						t_drag_container;

typedef struct			s_drop_container
{
	t_player			*player;
	t_button			*close;
}						t_drop_container;

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

int						ft_init_all_sdl(t_vm *vm, t_visu *v);

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
int						ft_is_on_close(t_vm *vm, t_ixy xy,
							t_button **button);
int						ft_is_on_draggable(t_vm *vm, t_ixy xy,
							t_drag_container *dc);
int						ft_is_on_droppable(t_vm *vm, t_ixy mouse,
							t_drop_container *dc);
void					ft_drop_dragged_player(t_vm *vm, t_ixy xy);
void					ft_update_cursor(t_vm *vm, t_ixy xy);
void					ft_change_cursor(t_vm *vm, int index);
int						ft_is_on_button(t_ixy xy, t_button *button,
							t_button **to_fill);
int						ft_is_on_buttons(t_vm *vm, t_ixy xy, t_button **button);
t_ixy					new_ixy(int x, int y);
int						ft_render_button(SDL_Surface *to, t_button button);
void					ft_delete_player(t_vm *vm, t_button *this, t_ixy xy);
int						ft_get_player_color(t_vm *vm, t_player *player,
							int initial_color, float value);
#endif
