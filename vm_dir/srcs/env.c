/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 18:19:03 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/04 14:36:09 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	ft_strarrlen(char **str)
{
	int i;

	i = 0;
	if (!(*str))
		return (-1);
	while (*str)
	{
		++i;
		++str;
	}
	return (i);
}


/*
 ** Scan environment tab for a variable
 ** Input: variable as string
 ** Return : corresponding index if found, -1 otherwise
 */

int			get_envar_index(char ***env_var, char *var, int nb_envar)
{
	int		index;

	index = 0;
	while (env_var[index] && !ft_strequ(env_var[index][0], var))
		++index;
	return (index == nb_envar ? -1 : index);
}

/*
 ** Split environment, store in char **tab by variable name
 ** Input: environment
 ** Return: 0 if malloc fail, total number of environment variables otherwise
 */

int				get_envar(char **env, char ****env_var)
{
	int	index;
	int	nb_envar;

	index = -1;
	nb_envar = ft_strarrlen(env);
	*env_var = (char ***)ft_memalloc(sizeof(char **) * (nb_envar + 1));
	if (!*env_var)
		return (0);
	while (++index < nb_envar)
		(*env_var)[index] = ft_strsplit(env[index], '=');
	return (nb_envar);
}
