/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 16:15:09 by ldedier           #+#    #+#             */
/*   Updated: 2018/07/09 20:59:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	int		length1;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	length1 = ft_strlen(s1);
	if (!(res = ft_strnew(length1 + ft_strlen(s2) + 1)))
	{
		ft_strdel(&s1);
		return (NULL);
	}
	ft_strclr(res);
	ft_strcat(res, s1);
	ft_strcat(&(res[length1]), s2);
	ft_strdel(&s1);
	return (res);
}
