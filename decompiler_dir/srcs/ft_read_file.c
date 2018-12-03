/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:01:13 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/03 18:01:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

int		ft_is_of_extension(char *str, int length, char *extension,
			int ext_length)
{
	int i;
	int j;

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

int ft_switch_extension(char *str, char *ext_from, char *ext_to,
		char **new_name)
{
	char *name;
	int len;
	int len_ext_to;
	int len_ext_from;

	len = ft_strlen(str);
	len_ext_to = ft_strlen(ext_to);
	len_ext_from = ft_strlen(ext_from);
	if (ft_is_of_extension(str, len, ext_from, len_ext_from))
	{
		if ((!(name = ft_strndup(str, len - len_ext_from))))
			return (-1);
		if (!(*new_name = ft_strjoin_free(name, ext_to)))
			return (-1);
		ft_printf("%s\n", *new_name);
		return (0);
	}
	else
		return (1);
}
