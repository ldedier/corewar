/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 01:04:49 by ldedier           #+#    #+#             */
/*   Updated: 2018/07/09 20:58:52 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin_free(char *s1, char *s2, size_t n)
{
	char *res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(res = ft_strnew(ft_strlen(s1) + ft_min(ft_strlen(s2), n) + 1)))
	{
		ft_strdel(&s1);
		return (NULL);
	}
	ft_strclr(res);
	ft_strcat(res, s1);
	ft_strncat(res, s2, n);
	ft_strdel(&s1);
	return (res);
}
