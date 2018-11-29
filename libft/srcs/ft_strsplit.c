/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:52:55 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 20:43:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_words(char const *s, char c)
{
	int res;
	int parseword;
	int i;

	res = 0;
	parseword = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && !parseword)
		{
			res++;
			parseword = 1;
		}
		else
		{
			if (s[i] == c && parseword)
				parseword = 0;
		}
		i++;
	}
	return (res);
}

static void	ft_init_values_to_0(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

static void	ft_update_values(int indlen[2], char const *s, int c, int indice)
{
	int nb_words;
	int parseword;
	int i;

	ft_init_values_to_0(&i, &parseword, &nb_words);
	while (s[i])
	{
		if (s[i] != c && !parseword)
		{
			if (indice == nb_words)
			{
				indlen[0] = i;
				while (s[i] && s[i] != c)
					i++;
				indlen[1] = i - indlen[0];
				return ;
			}
			parseword = 1;
			nb_words++;
		}
		if (s[i] == c && parseword)
			parseword = 0;
		i++;
	}
}

static char	*ft_word_dup(char const *s, int c, int indice)
{
	char	*res;
	int		indlen[2];
	int		i;

	indlen[0] = 0;
	indlen[1] = 0;
	i = 0;
	ft_update_values(indlen, s, c, indice);
	if (!(res = (char *)malloc(sizeof(char) * (indlen[1] + 1))))
		return (NULL);
	while (i < indlen[1])
	{
		res[i] = s[indlen[0] + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		nb_words;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	nb_words = ft_nb_words(s, c);
	if (!(res = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
	while (i < nb_words)
	{
		if (!(res[i] = ft_word_dup(s, c, i)))
		{
			while (i--)
				free(res[i]);
			free(res);
			return (NULL);
		}
		i++;
	}
	res[i] = 0;
	return (res);
}
