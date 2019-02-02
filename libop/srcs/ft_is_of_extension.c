/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_of_extension.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:33:36 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/30 17:57:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_of_extension(char *str, char *extension)
{
	int	i;
	int	j;
	int	length;
	int	ext_length;

	length = ft_strlen(str);
	ext_length = ft_strlen(extension);
	if (length < ext_length)
		return (0);
	i = length - ext_length;
	j = 0;
	while (i < length)
	{
		if (str[i] != extension[j])
			return (0);
		i++;
		j++;
	}
	return (1);
}
