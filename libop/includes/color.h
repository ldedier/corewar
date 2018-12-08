/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:55:47 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/28 13:57:27 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define COL				t_color
# define NB_DESIGNATOR		17
# define NB_COLTYPES		11
# define COL_FPL1		COLF_BLACK
# define COL_FPL2		COLF_BGREEN
# define COL_FPL3		COLF_MAGENTA
# define COL_FPL4		COLF_BROWN
# define COL_BPL1		COLB_BLACK
# define COL_BPL2		COLB_GREEN
# define COL_BPL3		COLB_BLUE
# define COL_BPL4		COLB_CYAN
# define COL_WAIT		COLF_RED
# define COL_BCYCLE		COLB_BGREY
# define COL_FCYCLE		COLF_BLACK
# define COL_BDEAD		COLB_BBLACK
# define COL_FDEAD		COLF_RED
# define COL_DESIGNATOR		"abcdefghABCDEFGHx"




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
** STANDARD COLORS - BACKGROUND
*/

# define COLB_BLACK		"\033[40m"
# define COLB_RED        "\033[41m"
# define COLB_GREEN      "\033[42m"
# define COLB_BROWN	    "\033[43m"
# define COLB_BLUE       "\033[44m"
# define COLB_MAGENTA    "\033[45m"
# define COLB_CYAN       "\033[46m"
# define COLB_GREY		"\033[47m"
# define COLB_BBLACK		"\033[100m"
# define COLB_BRED 		"\033[101m"
# define COLB_BGREEN		"\033[102m"
# define COLB_BBROWN		"\033[103m"
# define COLB_BBLUE		"\033[104m"
# define COLB_BMAGENTA	"\033[105m"
# define COLB_BCYAN   	"\033[106m"
# define COLB_BGREY		"\033[107m"
# define COLB_OFF		"\033[49m"

#endif
