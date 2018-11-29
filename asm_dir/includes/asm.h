/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:49:37 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/29 20:42:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

/*
** l2:		sti r1,%:live,%1
** 			and r1,%0,r1
**
** live:	live %1
** 			zjmp %:live
**
**
** name = "l2" , address = 0
** name = "live" , address = 2
*/

typedef struct	s_label
{
	char		*name;
	int			address;
}				t_label;

typedef struct	s_champion
{
	t_list		*labels;
	char		*name;
	char		*comment;
}				t_champion;

typedef struct	s_parser
{
	int			nb_line;
	//...
}				t_parser;

typedef struct	s_env
{
	t_champion	champ;
	//...
}				t_env;


/*
** parse le file filename: print l'erreur et retourne 1, retourne 0 sinon
** (mets a jour le champion)
*/
int				ft_parse_asm(char *filename, t_env *e);

/*
** encode le 
*/
int				ft_encode_to_cor(char *file, t_env *e);

#endif
