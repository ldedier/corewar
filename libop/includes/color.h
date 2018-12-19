/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:55:47 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/19 19:33:33 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <player.h>

#ifndef COLOR_H
# define COLOR_H

# define COL_DESIGNATOR		"brgwlmcyBRGWLMCYx"
# define DEFAULT_COLORS		"xgrlclmwM"
# define NB_DESIGNATOR		17
# define NB_COLORS			17
# define MAX_PL_COLOR		9
# define COREWAR_VAR_NAME	"CW_COLORS"
# define STR_COLOR_LEN		10

/*
** "pspcplpdpvrlrarrtmtctep0p1p2p3p4p5p6p7p8p9"
*/

/*
** PADDING
*/

# define PAD_PLNUM		4
# define PAD_PLNAME		30
# define PAD_PLCYCLE	7
# define PAD_PLPC		4
# define PAD_INS		30

/*
** STANDARD COLORS - FOREGROUND
*/

# define COLF_BLACK		"\033[22;30m"
# define COLF_RED		"\033[22;31m"
# define COLF_GREEN		"\033[22;32m"
# define COLF_BROWN		"\033[22;33m"
# define COLF_BLUE		"\033[22;34m"
# define COLF_MAGENTA	"\033[22;35m"
# define COLF_CYAN		"\033[22;36m"
# define COLF_GREY		"\033[22;37m"
# define COLF_BBLACK	"\033[01;30m"
# define COLF_BRED		"\033[01;31m"
# define COLF_BGREEN	"\033[01;32m"
# define COLF_BBROWN	"\033[01;33m"
# define COLF_BBLUE		"\033[01;34m"
# define COLF_BMAGENTA	"\033[01;35m"
# define COLF_BCYAN		"\033[01;36m"
# define COLF_BGREY		"\033[01;37m"
# define COLF_OFF		"\033[0m"

/*
** EQUIVALENT STANDARD COLORS FOR SDL
*/

# define COL_BLACK		0x000000
# define COL_GREEN		0x00FF00
# define COL_RED		0xFF0000
# define COL_BROWN		0x9A7D0A
# define COL_BLUE		0x0D47A1
# define COL_MAGENTA	0x62185B
# define COL_CYAN		0x1A5276
# define COL_GREY		0xABB2B9
# define COL_BBLACK		0x17202A
# define COL_BRED		0xE74C3C
# define COL_BGREEN		0x8BC34A
# define COL_BBROWN		0xFFCA28
# define COL_BBLUE		0x5DADE2
# define COL_BMAGENTA	0xF48FB1
# define COL_BCYAN		0x00BCDA
# define COL_BGREY		0xFFFFFF
# define COL_OFF		0xFFFFFF

typedef struct		s_color_type
{
	int		sdl;
	char	term[STR_COLOR_LEN];
}					t_color_type;
/*
enum				e_output
{
	TERM, SDL
};
*/
void		set_color(t_player *player, char *color);
void		color_on_term(char index);
int			get_color_sdl(char index);
void		color_off(void);
void		*get_term_color(char index);

int			get_envar(char **env, char ****env_var);
int			get_envar_index(char ***env_var, char *var, int nb_envar);
char		*init_color_ref(char **env);

#endif
