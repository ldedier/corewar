/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:10:09 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/15 17:07:18 by cammapou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_init_champion(t_champion *champ, char *filename)
{
	champ->assembly_name = filename;
	champ->instructions = NULL;
	champ->labels = NULL;
	champ->header.magic = COREWAR_EXEC_MAGIC;
	champ->header.prog_size = 0;
	ft_bzero(champ->header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(champ->header.comment, COMMENT_LENGTH + 1);
}

void	ft_init_parser(t_parser *parser)
{
	parser->nb_line = 0;
	parser->column_offset = 0;
	parser->nb_warnings = 0;
	parser->nb_errors = 0;
	parser->parsed_name = 0;
	parser->parsed_comment = 0;
	parser->too_much_errors_displayed = 0;
}

void	ft_init_env(t_env *e, char *filename)
{
	ft_init_champion(&(e->champ), filename);
	ft_init_parser(&(e->parser));
}
