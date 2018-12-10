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

#endif