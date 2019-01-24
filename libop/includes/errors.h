/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:53:10 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/24 19:46:26 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define NB_GAME_MSG 7

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
# define INVALID_PORT	"Invalid port for the corehub server"
# define INSUF_INFO_CH	"Port and address of the corehub server are needed"
# define ERR_HEADER "Header global error"
# define RD_ERROR "Error while reading file"
# define INIT_PROC_ERROR "Error while initializing player's process"
# define ERR_SIZE "Champion comment too long (Max length 2048"
# define ERR_LX "Lexical error"
# define ERR_LXC "Lexical error COMMENT"
# define ERR_LXN "Lexical error NAME"
# define ERR_SIZEN "Name too long Max length 128"
# define ERR_SXC "Syntax error AFTER COMMENT"
# define ERR_SXN "Syntax error token AFTER NAME"

/*
** PLAYER MESSAGES
*/

# define FILE_TOO_BIG	"Size of the given file is too large to be handled"
# define INVALID_CHARS	"Incorrect characters were used in the .cor file"
# define MAX_CHAMP		"Given champion is too large to be handled"
# define WRG_HEAD_SIZE	"Header size does not match file's code size"


#endif
