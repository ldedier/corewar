/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 20:06:08 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/30 20:21:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_is_relevant(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isseparator(str[i]))
		i++;
	if (!str[i] || str[i] == COMMENT_CHAR)
		return (0);
	return (1);
}

int		ft_parse_line_source_code(char *str, t_env *e)
{
	(void)e;
	(void)str;
	return (0);
}

int		ft_parse_line(char *str, t_env *e)
{
	if (!e->parser.parsed_comment || !e->parser.parsed_name)
		return (ft_parse_line_header(str, e));
	else
		return (ft_parse_line_source_code(str, e));
}

int		ft_parse_asm(char *str, t_env *e)
{
	char *line;
	int fd;
	(void)e;

	if ((fd = open(str , O_RDONLY)) == -1)
	{
		ft_printf("bad file descriptor\n");
		return (0);
	}
	while (get_next_line(fd, &line))
	{
		e->parser.nb_line++;
		if (ft_is_relevant(line))
		{
		//	ft_printf("%s\n",line);
			ft_parse_line(str, e);
		}
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}
