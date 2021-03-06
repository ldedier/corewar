/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:55:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/08 18:37:56 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <player.h>

# define COL_DESIGNATOR		"brgwlmcyBRGWLMCYx"
# define DEFAULT_COLORS		"xGMCWrlyxGRCLMWY"
# define NB_DESIGNATOR		17
# define NB_COLORS			17
# define MAX_PL_COLOR		MAX_PLAYERS
# define COREWAR_VAR_NAME	"CW_COLORS"
# define STR_COLOR_LEN		10

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
# define COL_CYCLES		COLF_BGREY
# define COL_DEATH		COLF_BBLACK
# define COL_RESIZE		COLF_BCYAN

/*
** EQUIVALENT STANDARD COLORS FOR SDL
*/

# define COL_BLACK		0x000000
# define COL_BLUE		0x0D47A1
# define COL_CYAN		0x1A5276
# define COL_BRED		0xE74C3C
# define COL_GREEN		0x21F500
# define COL_BROWN		0xFFD707
# define COL_BBLUE		0x5DADE2
# define COL_RED		0xFF0461
# define COL_OFF		0xFFFFFF

#endif
