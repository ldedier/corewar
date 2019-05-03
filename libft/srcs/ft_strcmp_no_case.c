/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_no_case.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 20:57:10 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/09 20:18:46 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp_no_case(char const *s1, char const *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (ft_tolower(s1[i]) != ft_tolower(s2[i]))
			return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
		i++;
	}
	return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
}
