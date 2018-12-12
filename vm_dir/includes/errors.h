/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:53:10 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/06 21:56:59 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define NB_MSG_TYPES	3
# define NB_MSG_PLAYER	5
# define NB_MSG_RESIZE	3
# define NB_MSG_TURN	3
# define NB_MSG_TOTAL	NB_MSG_PLAYER + NB_MSG_RESIZE + NB_MSG_TURN

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


/*
** GAME MESSAGES
*/

# define MSG_RESIZE	"New cycle length before checking if players are alive:"
# define MSG_NBR_LIVES_TURN	"Number of lives this turn "
# define MSG_NBR_TO_AUTORESIZE	"cycles to automatic resize"
# define MSG_CYCLES_REMAINING	"left to check lives"
# define MSG_VICTORY	"VICTORY FOR"
# define MSG_DEATH	"just died"
# define MSG_CYCLE_END	">>>END OF CYCLE "

# define LABEL_PLAYER	" PLAYER "
# define LABEL_CYCLE	" CYCLE "


enum 	e_msg_types
{
	PLAYER, RESIZE, TURN 
};

enum	e_msg_player_status
{
	PL_PC, PL_CYCLE, PL_LIVE, PL_DEATH, PL_VICTORY
};


enum 	e_msg_resize
{
	LIVES_TURN, AUTO_RESIZE, NEW_RESIZE
};

enum	e_msg_turn
{
	MOVE_ONE, CUR_CYCLE, CYCLE_END
	
}

/*
** GAME MSG DISPLAY
*/
void	display(t_vm *vm, t_process *proc, int type, int msg);
void	pl_death(void *content);
void	pl_live(void *content);
void	pl_victory(void *content);
void	pl_cycle(void *content);
void	pl_pc(void * content);
void	lives_turn(void *content);
void	cycles_to_autoresize(void *content);
void	resize(void *content);
void	cycle_end(void *content);
void	move_one(void *content);
void	cycle_nb(void *content);



#endif
