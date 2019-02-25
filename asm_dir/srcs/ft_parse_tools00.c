/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tools00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cammapou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:24:03 by cammapou          #+#    #+#             */
/*   Updated: 2019/02/25 16:15:21 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_update_co(char *str, t_env *e)
{
	int	i;

	i = 0;
	while (str[i] && ft_addco(str[i], e))
		i++;
}

char		*ft_get_str(char **line)
{
	int		i;
	char	*str;

	str = *line;
	i = 0;
	while (str[i] && !ft_isseparator(str[i]))
		i++;
	str = ft_strndup(*line, i);
	(*line) += i;
	return (str);
}

int			ft_is_relevant(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isseparator(str[i]))
		i++;
	if (!str[i] || str[i] == COMMENT_CHAR || str[i] == ';')
		return (0);
	return (1);
}

char		*ft_refine_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != COMMENT_CHAR && str[i] != ';')
		i++;
	return (ft_strndup(str, i));
}

int			ft_is_only_label(char *str)
{
	int	start;
	int	i;

	start = 0;
	while (ft_isseparator(str[start]))
		start++;
	i = start;
	while (str[i] && ft_is_in_str(LABEL_CHARS, str[i]))
		i++;
	if (!str[i])
		return (0);
	else if (str[i] == LABEL_CHAR)
	{
		i++;
		while (str[i])
		{
			if (!(ft_isseparator(str[i])))
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}
