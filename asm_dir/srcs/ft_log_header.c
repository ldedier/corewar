/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 01:41:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/15 01:41:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_log_error_name_len(int offset, t_env *e)
{
	char *str_nb;
	char *str;

	if (!(str_nb = ft_itoa(PROG_NAME_LENGTH)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(str = ft_strjoin("name too long: max = ", str_nb)))
	{
		free(str_nb);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	free(str_nb);
	ft_log_error(str, offset, e);
	free(str);
	return (1);
}

int		ft_log_error_comment_len(int offset, t_env *e)
{
	char *str_nb;
	char *str;

	if (!(str_nb = ft_itoa(COMMENT_LENGTH)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(str = ft_strjoin("comment too long: max = ", str_nb)))
	{
		free(str_nb);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	free(str_nb);
	ft_log_error(str, offset, e);
	free(str);
	return (1);
}

int		ft_log_error_too_long_parsing(int offset, t_env *e)
{
	if (e->parser.parsing_comment)
		return (ft_log_error_comment_len(offset, e));
	else
		return (ft_log_error_name_len(offset, e));
}
