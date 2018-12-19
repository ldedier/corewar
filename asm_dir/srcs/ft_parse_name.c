
#include "asm.h"


int check_name(char *str, t_env *env)
{
	char *name;

	name = NULL;
	if (str[0] == '.')
	{
		if (!(name = ft_strndup(str,  ft_strlen(NAME_CMD_STRING))))
			return (1);
		if (ft_strcmp(name, NAME_CMD_STRING) != 0)
			return (ft_log_error_no_line("Lexical error NAME", env));
	}
	else if (str[0] != '.')
		return (ft_log_error("Lexical error BEFORE NAME", 0, env));
	free(name);
	return (0);
}


static int read_name_continue(char *line, int i, t_env *env)
{
	if (line[i] != '"')
		return (ft_log_error("Lexical error", i - 1, env));
	if (line[i + 1] != '\0')
	{
		i += 1;
		while(line[i] || line[i] == ' ' || line[i] == '\t')
		{
			if (isprint(line[i]))
				return (ft_log_error("Syntax error at token AFTER NAME", i, env));
			i++;
		}
	}
	if (ft_strlen(env->champ.header.prog_name) > PROG_NAME_LENGTH)
		return (ft_log_error_no_line("Champ Name too long (Max length 128)", env));
	return (0);
}


int read_name(char *line, t_env *env, int i, int j)
{
	if (env->champ.header.prog_name[j])
		return (ft_log_error("Syntax error at token COMMAND_NAME", 0, env));
	i += ft_strlen(NAME_CMD_STRING);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '"')
		return (ft_log_error("Lexical error", i, env));
	while (line[i++])
	{
		env->champ.header.prog_name[j] = line[i];
		if (line[i] == '"')
			break;
		j++;
	}
	env->champ.header.prog_name[j] = '\0';
	if (read_name_continue(line, i, env) == 1)
		return (1);
	printf("%s\n", env->champ.header.prog_name);
	env->parser.parsed_name = 1;
	return (0);
}
