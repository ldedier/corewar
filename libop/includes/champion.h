/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:06:44 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/04 14:41:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAMPION_H
# define CHAMPION_H

typedef struct		s_label
{
	int				address;
	char			*name;
}					t_label;

typedef struct		s_parameter
{
	t_arg_type		type; //T_REG || T_DIR || T_IND || T_LAB
	unsigned int	value;
	char			*label_name;
	int				source_code_col;
	int				nb_bytes;
}					t_parameter;

typedef struct		s_instruction
{
	t_op			op;
	t_parameter		params[3];
	unsigned int	address;
	int				nb_line;
	int				ocp;
	char			*source_code_line;
}					t_instruction;

typedef struct		s_champion
{
	t_header		header;
	t_list			*instructions;
	t_list			*labels;
	char			*cor_name;
	char			*assembly_name;
}					t_champion;


/*
** check if str is of extension ext_from, if not return 1
** then puts in new_name a newly allocated version of str with its extension 
** ext_from replaced with ext_to then return 0 or -1 if the allocation failed
*/
int					ft_switch_extension(char *str, char *ext_from, char *ext_to,
						char **new_name);
#endif
