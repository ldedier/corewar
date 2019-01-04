/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:53:10 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/04 13:24:48 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define NB_GAME_MSG 13

/*
** ERROR MESSAGES
*/

# define USAGE "Usage: ./corewar [-dump nb] [-v|-w] [-n nb] <champ1.cor> <...>"
# define WRG_FILE_TYPE "File type invalid"
# define WRG_DUMP "Wrong arguments after -dump"
# define MAX_DUMP "[-dump nbr_cycle]: nbr_cycle can't exceed INT_MAX"
# define WRG_N_FLAG "Wrong arguments after -n"
# define MAX_N_FLAG "[-n nb] :  nb can't exceed INT_MAX or -INT_MAX"
# define WRG_P_NUM "Trying to assign a player number already taken"
# define FILE_ISSUE "Issue while handling file"
# define MAX_P_NUM "Number of players exceeded max amount"
# define INVALID_PORT	"invalid port for the corehub server"
# define INSUF_INFO_CH	"port and address of the corehub server are needed"
# define ERR_HEADER "Header global error"

/*
** PLAYER MESSAGES
*/

# define FILE_TOO_BIG	"Size of the given file is too large to be handled"
# define INVALID_CHARS	"Incorrect characters were used in the .cor file"
# define MAX_CHAMP		"Given champion is too large to be handled"
# define WRG_HEAD_SIZE	"Header size does not match file's code size"

/*
** GAME MESSAGES
*/

# define MSG_RESIZE	"New cycle length before checking if players are alive:"
# define MSG_NBR_LIVES_TURN	"Number of lives this turn "
# define MSG_NBR_TO_AUTORESIZE	"cycles to automatic resize"
# define MSG_CYCLES_REMAINING	"cycles left to check lives"
# define MSG_VICTORY	"VICTORY FOR"
# define MSG_DEATH	"just died"
# define MSG_CYCLE_END	">>>END OF CYCLE "
# define MSG_MOVE_ONE	"Move forward..."

# define LABEL_PLAYER	" PLAYER "
# define LABEL_CYCLE	" CYCLE "

enum	e_game_msg
{
	PL_PC, PL_CYCLE, PL_LIVE, PL_DEATH, PL_VICTORY,
	LIVES_TURN, AUTO_RESIZE, NEW_RESIZE,
	MOVE_ONE, LAST_LIVE, CYCLE_NBR, CYCLE_END, TURN_PLAYER
};

#endif
