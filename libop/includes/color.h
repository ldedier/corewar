/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:55:47 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/14 00:19:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

/*
** "pspcplpdpvrlrarrtmtctep0p1p2p3p4p5p6p7p8p9"
*/
# define DEFAULT_COLORS 	
# define COL				t_color

# define NB_DESIGNATOR		17
# define NB_COLORS		17
# define COL_DESIGNATOR		"brgwlmcyBRGWLMCYx"
# define MAX_PL_COLOR		9
# define DEFAULT_COLORS		"xRZMGCgw"

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
# define COLF_WHITE		"\x1B[37m"

/*
** EQUIVALENT STANDARD COLORS FOR SDL
*/

# define COL_BLACK		0x212F3D
# define COL_RED		0xA993226	
# define COL_GREEN		0x196F3D
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
# define COL_BGREY		0xEEEEEE
# define COL_WHITE		0xFFFFFF


typedef struct		s_color
{
	void	*value;
	int	index;
}			t_color;

typedef struct		s_color_type
{
	int	sdl
	char	*term;
			s_color_type;

enum				e_output
{
	TERM, SDL
};

void		set_colors(char	*color);
int			color_on(char *color, int type, int output);
void		color_off(void);

#endif
