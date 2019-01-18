/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:48:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/18 19:54:31 by uboumedj         ###   ########.fr       */
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

# define INIT_MAX_PLAYERS		4
# define INIT_CYCLES_PER_TURN	1
# define GLYPH_W_H_RATIO		0.5
# define ABBREV_LEN				8

# define FRAMERATE				60

# define DASHBOARD_X			1950
# define TOP_DASHBOARD_HEIGHT	530
# define TOP_DASHBOARD_FHEIGHT	40
# define SPEC_VBORDER			8

# define FOOTER_HEIGHT			120

# define FIGHT_TOP				30
# define FIGHT_BOTTOM			30
# define FIGHT_LEFT				200
# define FIGHT_RIGHT			200

# define MEM_BORDER_TOP			100
# define MEM_BORDER_BOTTOM		100
# define MEM_BORDER_RIGHT		100
# define MEM_BORDER_LEFT		100

# define TITLE_BORDER_TOP		15
# define TITLE_BORDER_BOTTOM	10
# define TITLE_BORDER_SIDE		30
# define TITLE_HEIGHT			50

# define PLAYER_PADDING			40
# define PLAYER_TOP				30
# define PLAYER_BORDER_LEFT		50
# define PLAYER_BORDER_RIGHT	50
# define PLAYER_BORDER_BOTTOM	30

# define PLAYER_HEIGHT			74
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

# define LABSCORE_LEFT			20
# define LABSCORE_WIDTH			90
# define LABSCORE_RIGHT			20
# define SCORE_WIDTH			100
# define SCORE_RIGHT			20

# define SCROLLBAR_WIDTH		25
# define SCROLLBAR_BTTN_HEIGHT	25

# define X_DIFF					7
# define X_DIFF_BYTE			0
# define Y_DIFF					7

# define NOTIF_PANEL_W			400
# define NOTIF_PANEL_H			250

# define NB_ENTRIES				7

# define STATE_TOP				40
# define STATE_H				60
# define STATE_BOTTOM			30
# define ENTRY_H				30
# define GAME_ENTRIES_H		 	425
# define PLAY_FOOTER_H			180
# define LIVE_BREAKDOWN_H		150

# define NB_PLAYER_ENTRIES		3
# define PLAYER_ENTRY_LEFT		50
# define PLAYER_ENTRY_SPACE		20
# define PLAYER_TITLE_HEIGHT	30
# define PLAYER_ENTRY_HEIGHT	25
# define PLAYER_TITLE_TOP		20
# define PLAYER_TITLE_BOTTOM	20

# define LIST_PLAYER_ENTRIES_B	20
# define PLAYER_ENTRY_IPADDING	8

# define ENTRY_BOTTOM			20
# define ENTRY_SPACE			30
# define ENTRY_LEFT				20
# define ENTRY_RIGHT			20
# define ENTRY_SPACE			30

# define LIVE_BREAKDOWN_HP_TITLE_TOP	30
# define LIVE_BREAKDOWN_HP_TITLE_BOTTOM	30

# define LIVE_BREAKDOWN_HP_PLAYERS_H		30

# define LIVE_BREAKDOWN_HP_PLAYERS_SIDE		40

# define LIVE_BREAKDOWN_HP_PLAYERS_BOTTOM	20

# define WINNER_HEIGHT			20
# define WINNER_TOP				30
# define WINNER_BOTTOM			60

# define BACK_WIDTH				50
# define BACK_HEIGHT			50

# define LIVE_BREAKDOWN_TITLE_H		34
# define LIVE_BREAKDOWN_TITLE_TOP	34

# define LIVE_BREAKDOWN_BAR_H	30

# define MEM_COLS				64

# define NB_GLYPHS				256

# define NB_FRAMES				5

# define NB_TITLES				10

/*
**								0 = ARENA
**								1 = LOCAL
**								2 = DOWNLOADS
*/

# define SCOREWAR				3
# define UPLOAD_HERE			4
# define SCORE					5
# define NAME					6
# define RANK					7
# define COREWAR				8

# define NB_IMAGES				22

# define CLOSE					0
# define DL						1
# define UL						2
# define SORT_ALPHA				3
# define SORT_SCORE				4
# define SCROLL_BAR				5
# define SCROLL_UP				6
# define SCROLL_DOWN			7
# define FIGHT					8
# define UL_DISABLED			9
# define DL_DISABLED			10
# define TRASH					11
# define TRASH_DISABLED			12
# define SWITCH_1				13
# define SWITCH_2				14
# define NAME_TAKEN_NOTIF		15
# define FROM_SERVER_NOTIF		16
# define NAME_INVALID_NOTIF		17
# define LOST_CONNEXION_NOTIF	18
# define OK						19
# define BREAKDOWN_BAR			20
# define BACK					21

# define NB_CURSORS				5

# define GRAB					0
# define DRAGGABLE				1
# define CLICK					2
# define REGULAR				3

# define NB_BUTTONS				8

# define UPLOAD_BUTTON			0
# define ALPHA_SORT_BUTTON		1
# define SCORE_SORT_BUTTON		2

# define NB_ONLINE_BUTTONS		3

# define FIGHT_BUTTON			3
# define SWITCH_LOCAL_BUTTON	4
# define CLEAN_ARENA_BUTTON		5
# define OK_BUTTON				6
# define BACK_BUTTON			7

# define PLAYER_COL_BORDER		0x000000
# define PLAYER_COL				0x222222
# define BACKGROUND_COL			0x333333
# define PLAYER_BACKGROUND_COL	0x444444
# define PLAYER_HOVERED_BG_COL	0x666666
# define UPLOAD_COLOR			PLAYER_BACKGROUND_COL
# define LINE_COL				0xffffff
# define LINE_COL_DARKER		0x666666

# define DROP_TOLERANCE_W		100
# define DROP_TOLERANCE_H		30

# define MAX_FADE				60
# define FADE_LEN				5

typedef struct s_vm				t_vm;
typedef struct s_visu			t_visu;
typedef struct s_vscrollbar		t_vscrollbar;
typedef struct s_client_slot	t_client_slot;

typedef struct			s_atlas_char
{
	SDL_Surface			*surface;
}						t_atlas_char;

typedef struct			s_cursor_packer
{
	SDL_Surface			*surface;
	SDL_Cursor			*cursor;
}						t_cursor_packer;

typedef struct			s_sort_button
{
	char				on;
}						t_sort_button;

typedef union			u_button_union
{
	char				*name;
	t_player			*player;
	t_client_slot		*client_slot;
	t_vscrollbar		*vscrollbar;
	t_sort_button		sort;
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

typedef enum			e_phase
{
	PHASE_INIT,
	PHASE_PLAY,
	PHASE_END
}						t_phase;

typedef struct			s_button
{
	SDL_Rect			rect;
	SDL_Surface			*surface;
	t_button_union		button_union;
	char				visible;
	char				enabled;
	t_phase				phase;
	int					(*on_click)(t_vm *, struct s_button *, t_ixy xy);
	void				(*on_press)(t_vm *, struct s_button *);
	int					(*render)(t_vm *, struct s_button *);
	void				(*on_hover)(t_vm *, struct s_button *, t_ixy xy);
	t_vscrollbar		*vscrollbar;
}						t_button;

/*
** vertical scrollbar:
** height:				the size of the section on the screen
** compressed_height:	the actual size inside it (>= height)
** state:				0 top, 1 bottom
** pos:					whole scrollbar x and y coordinate
*/

struct					s_vscrollbar
{
	t_ixy				pos;
	int					pos_x;
	double				state;
	int					height;
	int					compressed_height;
	int					bar_width;
	t_button			up_button;
	t_button			down_button;
	char				relevant;
};

typedef enum			e_player_source
{
	ARENA,
	LOCAL,
	DOWNLOADS,
	UPLOAD,
	SERVER,
	NB_SOURCES,
	GRAB_ARENA,
	GRAB_LOCAL,
	GRAB_DOWNLOADS,
	GRAB_UPLOAD,
	GRAB_SERVER,
}						t_player_source;

typedef struct			s_player_list
{
	t_player_source		source;
	t_vscrollbar		vscrollbar;
}						t_player_list;

typedef struct			s_sdl
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

typedef struct			s_reactive
{
	double				w_scale;
	double				h_scale;
	double				anim_ratio;
}						t_reactive;

typedef struct			s_framerate
{
	Uint64				current;
	Uint64				previous;
	double				delta;
	int					fps_counter;
	Uint32				ms_counter;
}						t_framerate;

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
	double				top_dashboard_fheight;
	double				dashboard_mid_x;
	double				dashboard_mid_width;
	double				dashboard_width;
	double				bottom_dash_height;

	double				mid_dashboard_height;
	double				footer_height;
	double				footer_y;

	int					title_top;
	int					title_h;
	double				title_side;
	int					title_bottom;

	int					player_top;
	int					player_left;
	int					player_right;
	int					player_w;
	double				player_h;
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

	double				toolbar_y;

	double				labscore_left;
	double				labscore_width;
	double				labscore_right;

	double				score_width;
	double				score_right;

	double				download_side;
	double				scrollbar_width;
	double				scrollbar_buttons_height;

	double				spec_h;
	double				spec_left;
	double				spec_vborder;

	double				switch_w;
	double				switch_left;

	int					fight_top;
	int					fight_bottom;
	int					fight_left;
	int					fight_right;
	int					fight_height;
	int					fight_width;

	int					notif_panel_w;
	int					notif_panel_h;
	int					notif_panel_left;
	int					notif_panel_top;

	int					game_entries_h;
	int					play_footer_h;
	int					player_entries_h;
	int					list_player_entries_h;

	int					player_entry_left;
	int					player_entry_space;
	double				player_title_height;
	double				player_entry_height;
	int					player_title_top;
	int					player_title_bottom;

	int					player_entry_padding;
	int					player_entry_ipadding;
	int					list_player_entries_bottom;

	int					live_breakdown_h;
	int					state_top;
	int					state_h;
	int					state_bottom;
	int					entry_h;
	int					entry_bottom;
	int					entry_padding;
	int					entry_left;
	int					entry_space;
	int					entry_max_w;
	int					entry_value_max_w;
	int					entry_right;

	int					live_breakdown_title_h;
	int					live_breakdown_title_w;
	int					live_breakdown_title_left;
	int					live_breakdown_title_top;
	int					live_breakdown_bar_w;
	int					live_breakdown_bar_h;
	int					live_breakdown_bar_left;
	int					live_breakdown_bar_top;

	int					live_breakdown_hp_y;
	int					live_breakdown_hp_h;

	int					live_breakdown_hp_anim_h;
	int					live_breakdown_hp_anim_y;

	int					live_breakdown_hp_title_top;
	int					live_breakdown_hp_title_bottom;
	int					live_breakdown_hp_players_h;
	int					live_breakdown_hp_players_bottom;

	int					live_breakdown_hp_players_side;

	int					winner_height;
	int					winner_top;
	int					winner_bottom;
	int					winner_left;

	int					back_width;
	int					back_height;
	int					back_left;
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

typedef enum			e_drag_enum
{
	DRAG_PLAYER,
	DRAG_VSCROLLBAR
}						t_drag_enum;

typedef struct			s_drag_player
{
	t_player			*player;
	t_client_slot		*client_slot;
	t_button			*close;
	t_player_source		source;
}						t_drag_player;

typedef union			s_drag_union
{
	t_vscrollbar		*vscrollbar;
	t_drag_player		drag_player;
}						t_drag_union;

typedef struct			s_drag_container
{
	t_drag_union		drag_union;
	t_drag_enum			drag_enum;
	int					x;
	int					y;
	int					diff_x;
	int					diff_y;
	t_visu				*parent;
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
	t_button			*pressed_button;
}						t_event_manager;

typedef struct			s_color_manager
{
	int					color;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_color_manager;

typedef enum			e_local_type
{
	LOCAL_LOCAL,
	LOCAL_DOWNLOAD
}						t_local_type;

typedef struct			s_time_manager
{
	char				pause;
	double				cycles_per_turn;
}						t_time_manager;

typedef struct			s_notification
{
	int					image_index;
}						t_notification;

typedef struct			s_ray
{
	SDL_Surface			*surface;
	int					screen_width;
	int					x_offset;
}						t_ray;

typedef struct			s_hp_frame
{
	SDL_Surface			*background;
	t_ray				harry_ray;
	t_ray				voldemort_ray;
}						t_hp_frame;

typedef enum			e_sort_type
{
	SORT_TYPE_ALPHA,
	SORT_TYPE_SCORE
}						t_sort_type;

struct					s_visu
{
	char				active;
	t_phase				phase;
	int					(*sort_cs_func)(void *, void *);
	unsigned char		inv_sort;
	t_sort_type			sort_type;
	t_local_type		local_type;
	t_sdl				sdl;
	t_dim				dim;
	t_center			center;
	t_event_manager		event_manager;
	t_drag_container	drag_container;
	t_drop_container	drop_container;
	t_positions			positions;
	t_reactive			react;
	t_framerate			framerate;
	t_button			buttons[NB_BUTTONS];
	t_player_list		players_list[NB_SOURCES];
	t_list				*downloaded_players;
	t_notification		notification;
	t_time_manager		time_manager;
	t_hp_frame			frames[NB_FRAMES];
	int					animation_index;
};

int						ft_init_all_visu(t_vm *vm, t_visu *v);

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
int						ft_render_init_online(t_vm *vm);
int						ft_render_offline(t_vm *vm);
t_color_manager			ft_get_color(int color);
t_color_manager			ft_get_color_sdl(int color);
t_color_manager			ft_scale_color(t_color_manager color, double scale);
t_color_manager			ft_scale_color_sdl(t_color_manager color, double scale);
t_color_manager			ft_interpolate_color(int col1, int col2, double t);
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
int						ft_is_on_button(t_vm *vm, t_ixy xy, t_button *button,
							t_button **to_fill);
int						ft_is_on_buttons(t_vm *vm, t_ixy xy, t_button **button);
t_ixy					new_ixy(int x, int y);
int						ft_render_button(t_vm *vm, t_button *button);
int						ft_process_render_button(t_vm *vm, SDL_Rect rect,
							SDL_Surface *surface, t_vscrollbar *vscrollbar);
int						ft_delete_player(t_vm *vm, t_button *this, t_ixy xy);
int						ft_get_player_color(t_vm *vm, t_player *player,
							int initial_color, float value);
void					ft_render_horizontal_line_dashboard(t_vm *vm, int y,
							int col);
int						ft_copy_str_to_surface(t_vm *vm, char *str,
							SDL_Rect rect, t_ixy col_source);
int						ft_get_vscrollbar_compressed_height(t_visu *v,
							int nb_players);
void					ft_init_players_list(t_vm *vm, t_visu *v);
void					ft_init_vscrollbars_compressed_size(t_vm *vm,
							t_visu *v);
int						ft_blit_scaled_scrollbar(t_sdl *sdl, SDL_Surface *from,
							SDL_Rect rect, t_vscrollbar v);
int						ft_fill_rect_scrollbar(SDL_Surface *from, SDL_Rect *rct,
							int color, t_vscrollbar vscrollbar);
t_ixy					ft_get_vscrollbar_bar_height_y(t_vscrollbar vscrollbar);
double					ft_get_vscrollbar_bar_height(t_vscrollbar vscrollbar);
int						ft_to_print_scrollbar(t_vscrollbar vscrollbar);
void					ft_update_scrollbar(t_vm *vm, t_vscrollbar *vscrollbar);
int						get_vscrollbar(t_vm *vm, t_ixy mouse,
							t_vscrollbar **vscrollbar);
int						ft_get_scrolled_height(t_vscrollbar vscrollbar);
void					ft_swing_scrollbar(t_vscrollbar *scrollbar, t_ixy xy);
int						nothing_on_click(t_vm *vm, t_button *this, t_ixy xy);
int						fight(t_vm *vm, t_button *this, t_ixy xy);

int						sort_score(t_vm *vm, t_button *this, t_ixy xy);
int						sort_alpha(t_vm *vm, t_button *this, t_ixy xy);

void					nothing_on_press(t_vm *vm, t_button *this);
void					ft_wheel_event(t_vm *vm, SDL_Event event);
void					ft_update_download_buttons_client_rect(t_vm *vm);
int						ft_render_download_button(t_vm *vm, t_button *this);
int						ft_render_vscrollbars(t_vm *vm);
void					ft_render_init_lines(t_vm *vm);
int						ft_render_crosses(t_vm *vm);
int						ft_render_phase(t_vm *vm);
int						ft_is_in_scrollbar_focus(t_vscrollbar vscrollbar);
void					ft_scroll_up(t_vm *vm, t_button *button);
void					ft_scroll_down(t_vm *vm, t_button *button);
void					ft_populate_drag_container_player(t_drag_container *dc,
							t_player *player, t_player_source source);
void					ft_populate_drag_container_vscrollbar(t_drag_container *dc,
							t_vscrollbar *vscrollbar);
void					ft_populate_drag_container_player_client_slot(
							t_drag_container *dc, t_client_slot *client_slot,
								t_xy player_pos, int scrolled_h);
void					ft_populate_drag_container_player_download(
							t_drag_container *dc, t_player *player,
								t_xy player_pos, int scrolled_h);
void					ft_populate_drag_container_player_slot(t_drag_container
							*dc, t_player *player, t_slot *slot,
								t_player_source source);
void					ft_fill_drag_container(t_drag_container *dc, t_ixy xy);
int						ft_is_on_scrollbars(t_vm *vm, t_ixy xy,
							t_drag_container *dc);
void					ft_copy(t_vm *vm, t_drop_container *dc);
void					ft_place(t_vm *vm, t_drop_container *dc);
void					ft_place_or_swap(t_vm *vm, t_drop_container *dc);
int						ft_is_on_player_scrollbar(t_vm *vm, t_ixy xy,
							t_xy player_xy, t_vscrollbar vscrollbar);
int						ft_is_on_client_players(t_vm *vm, t_ixy xy,
							t_drag_container *dc);
int						ft_is_on_download_players(t_vm *vm, t_ixy xy,
							t_drag_container *dc);
SDL_Surface				*ft_load_image(char *str);
TTF_Font				*ft_load_font(char *str, int quality);
int						ft_init_atlas(t_vm *vm, t_sdl *sdl);
void					ft_init_center(t_visu *v, t_center *c);
SDL_Surface				*ft_init_font_surface_sdl(char *str, t_sdl sdl);
int						ft_init_textures(t_visu *visu);
int						ft_init_cursors(t_visu *v);
void					ft_populate_upload_slot(t_vm *vm, t_visu *v);
void					ft_populate_slots_positions(t_vm *vm, t_visu *v);
void					ft_init_crosses(t_vm *vm);
void					ft_init_client_slot_surface(t_vm *vm);
void					ft_populate_closing_button(t_vm *vm, t_button *button,
							t_player *player, t_ixy xy);
int						ft_upload(t_vm *vm, t_button *this, t_ixy mouse);
int						ft_render_upload_button(t_vm *vm, t_button *this);
void					ft_init_buttons(t_vm *vm, t_visu *visu);
void					ft_get_dimensions(t_visu *v);
void					ft_init_sdl_to_null(t_visu *v);
int						ft_init_sdl(t_visu *v);
int						ft_is_in_rect(t_ixy xy, SDL_Rect rect);
void					ft_mouse_down(t_vm *vm, SDL_Event event);
void					ft_mouse_up(t_vm *vm, SDL_Event event);
void					ft_mouse_motion(t_vm *vm, SDL_Event event);
int						ft_process_button_pressed(t_vm *vm);
void					ft_render_dashboard_separator(t_vm *vm);
int						process(t_vm *vm);
int						ft_render_all_process(t_vm *vm);
int						ft_render_all_dead_process(t_vm *vm);
int						ft_render_all_lives(t_vm *vm);
int						start_fight(t_vm *vm);
int						clean_arena(t_vm *vm, t_button *this, t_ixy xy);
int						switch_local(t_vm *vm, t_button *this, t_ixy xy);
int						ft_render_trash_button(t_vm *vm, t_button *this);
int						ft_render_switch_button(t_vm *vm, t_button *this);
int						ft_process_upload(t_vm *vm, t_player player);
int						ft_get_new_cores(int nb_bytes, t_vm *vm);
void					ft_update_vscrollbar_server_compressed_size(t_vm *vm,
							t_visu *v);
void					ft_update_vscrollbar_downloads_compressed_size(t_vm *vm,
							t_visu *v);
int						ft_query_player_bin(t_vm *vm, t_client_slot *cs);
int						ft_render_notification(t_vm *vm);
void					ft_set_notification(t_vm *vm, int image_index);
int						ft_remove_notification(t_vm *vm, t_button *button,
							t_ixy xy);
int						ft_copy_str_to_surface_no_source(t_vm *vm, char *str,
							SDL_Rect rect, int color_index);
int						ft_render_entry(t_vm *vm, char *entry, char *value,
							int y);
int						ft_render_cycles_per_second(t_vm *vm, int y);
int						ft_render_cycle(t_vm *vm, int y);
int						ft_render_cycle_to_die(t_vm *vm, int y);
int						ft_render_cycle_delta(t_vm *vm, int y);
int						ft_render_ctd_countdown(t_vm *vm, int y);
int						ft_render_lives_current_period(t_vm *vm, int y);
int						ft_render_checks(t_vm *vm, int y);
int						process_cycle_all(t_vm *vm);
int						ft_render_play(t_vm *vm);
int						ft_render_entries(t_vm *vm);
int						ft_render_player_entries(t_vm *vm);
int						ft_render_last_live(t_vm *vm, t_player player, int y);
int						ft_render_nb_process(t_vm *vm, t_player player, int y);
int						ft_render_live_breakdown(t_vm *vm);
int						ft_render_live_breakdown_hp(t_vm *vm);
int						go_back(t_vm *vm, t_button *this, t_ixy xy);
int						ft_render_play_footer(t_vm *vm);
int						ft_render_nb_live(t_vm *vm, t_player p, int y);
int						ft_render_live_breakdown_title(t_vm *vm, SDL_Rect rect);
int						ft_init_hp_surface(t_visu *visu);
void					ft_copy_abbrev(char *abbrev, char *str);
int						ft_sort_score(void *p1, void *p2);
int						ft_sort_alpha(void *p1, void *p2);
int						ft_sort_alpha_cs(void *p1, void *p2);
int						ft_sort_score_cs(void *p1, void *p2);
void					ft_sort_client_slots(t_vm *vm);
int						ft_copied_char_surface_w(SDL_Rect rect, int len);
#endif
