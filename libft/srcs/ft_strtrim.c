/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 20:08:22 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/26 21:25:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(char const *s)
{
	int i;

	i = 0;
	while (s[i] && ft_isseparator_light(s[i]))
		i++;
	return (i);
}

static int	ft_stop(char const *s)
{
	int i;
	int stop;

	i = 0;
	while (s[i] && ft_isseparator_light(s[i]))
		i++;
	while (s[i])
	{
		stop = i;
		while (ft_isseparator_light(s[i]))
			i++;
		if (s[i] == '\0')
			return (stop);
		i++;
	}
	return (i);
}

char		*ft_strtrim(char const *s)
{
	if (s == NULL)
		return (NULL);
	else
		return (ft_strsub(s, ft_start(s), ft_stop(s) - ft_start(s)));
}
