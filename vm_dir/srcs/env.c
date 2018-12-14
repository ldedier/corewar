
/*
** Scan environment tab for a variable
** Input: variable as string
** Return : corresponding index if found, -1 otherwise
*/

static int			get_envvar_index(char ***env_var, char *var, int nb_envar)
{
	int		index;

	index = 0;
	while (env_var[index] && !ft_strequ(env_var[index][0], var))
		++index;
	return (index == nb_envvar ? -1 : index);
}

/*
** Split environment, store in char **tab by variable name
** Input: environment
** Return: 0 if malloc faile, total number of environment variables otherwise
*/

int				get_envvar(char **env, char ****envar)
{
	int	index;
	int	nb_envar;

	index = -1;
	nb_envar = ft_strarrlen(env);
	*env_var = (char ***)ft_memalloc(sizeof(char **) * (nb_envvar + 1));
	if (!*env_var)
		return (0);
	while (++index < nb_envvar)
		(*env_var)[index] = ft_strsplit(env[index], '=');
	return (nb_envar);
}
