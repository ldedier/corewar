/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:06:44 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/06 17:42:12 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAMPION_H
# define CHAMPION_H

typedef struct		s_champion
{
	t_header		header;
	t_list			*instructions;
	t_list			*labels;
	char			*cor_name;
	char			*assembly_name;
}					t_champion;

typedef struct		s_label
{
	int				address;
	char			*name;
}					t_label;

/*
** check if str is of extension ext_from, if not return 1
** then puts in new_name a newly allocated version of str with its extension 
** ext_from replaced with ext_to then return 0 or -1 if the allocation failed
*/
int					ft_switch_extension(char *str, char *ext_from, char *ext_to,
						char **new_name);
int					ft_is_of_extension(char *str, char *extension);
#endif
