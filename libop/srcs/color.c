/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 20:42:40 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/14 00:19:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void		color_off(void)
{
	ft_printf("%s", COLF_OFF);
}

void		color_on_term(char index)
{
	ft_printf("%s", (char *)(get_term_color(index) + sizeof(int)));
}

void	*get_color_ptr(char index)
{
	static t_color_type [NB_COLORS] = {
		{COL_BLACK, COLF_BLACK},
		{COL_RED, COLF_RED},
		{COL_GREEN, COLF_GREEN},
		{COL_BROWN, COLF_BROWN},
		{COL_BLUE, COLF_BLUE},
		{COL_MAGENTA, COLF_MAGENTA},
		{COL_CYAN, COLF_CYAN},
		{COL_GREY, COLF_GREY}, 
		{COL_BBLACK, COLF_BBLACK},
		{COL_BRED, COLF_BRED},
		{COL_BGREEN, COLF_BGREEN},
		{COL_BBROWN, COLF_BBROWN},
		{COL_BBLUE, COLF_BBLUE},
		{COL_BMAGENTA, COLF_BMAGENTA},
		{COL_BCYAN, COLF_BCYAN},
		{COL_BGREY, COLF_BGREY},
		{COL_OFF, COLF_OFF}};
	return ((void *)color[index];
}

void		set_color(t_player *player, char *color_index_ref, char index)
{
	int	ref_index;

	player->color.index = index;
	ref_index = ft_strichr(COL_DESIGNATOR, color[index]);
	player->color.value = get_color_ptr((char)ref_index);
}

static void	init_color_ref(char **env, char *color)
{
	char	***env_var;
	int	i;
	int	nb_envar;

	if (!color[2])
	{	
		nb_envar = get_envvar(env, &env->var);
		if (get_envvar_index(env_var, COREWAR_VAR_NAME, nb_envar)
			ft_strncpy(color, env_var[index][1], MAX_PL_COLOR);
		else
			ft_strncpy(color, DEFAULT_COLORS, MAX_PL_COLOR);
		i = -1;
		while (color[++i])
			color = ft_strichr(COL_DESIGNATOR, (int)color[i]);
	}
}
