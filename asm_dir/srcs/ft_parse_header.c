/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 20:04:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/11 15:12:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// j'ai change les char * en char[PROG_NAME] etc (voir struct s_champion)

int	isprint(int c)
{
	return (c >= 33 && c <= 126);
}
//devrait mettre a jour
//le parser sur has_comment, has_name

int	ft_parse_line_header(char *str, t_env *env, int i, int fd)
{
	if (ft_strstr(str, NAME_CMD_STRING))
	{
		if(check_name(str, env))
			return (1);
		if (read_name(str, env, i, 0) == 1)
			return (1);
	}
	else if (ft_strstr(str, COMMENT_CMD_STRING))
	{
		if(check_comment(str, env))
			return (1);
		if (read_comment(str, env, fd, 0) == 1)
			return (1);
	}
	else if (!ft_strcmp(env->champ.header.prog_name, ""))
		return (ft_log_error_no_line("Lexical error NAME", env));
	else if (!ft_strcmp(env->champ.header.comment, ""))
		return (ft_log_error_no_line("Lexical error COMMENT",env));
	return (0);
}
