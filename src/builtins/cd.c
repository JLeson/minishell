/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <joel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:26:10 by joel              #+#    #+#             */
/*   Updated: 2023/12/08 14:10:21 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_envvar_name(char *name, char *envvar)
{
	unsigned int	len;

	len = lstrlen(envvar, "=", 0);
	return (!ft_strncmp(name, envvar, ft_max(len, ft_strlen(name))));
}

static char	*join_value(char *name, char *value)
{
	char	*envvar;
	char	*temp;

	temp = ft_strjoin(name, "=");
	envvar = ft_strjoin(temp, value);
	free(temp);
	return (envvar);
}

static void	mod_var(char *name, char *value, char **env)
{
	unsigned int	cidx;

	cidx = 0;
	while (env[cidx])
	{
		if (is_envvar_name(name, env[cidx]))
		{
			free(env[cidx]);
			env[cidx] = join_value(name, value);
			break ;
		}
		cidx++;
	}
}

static void	mod_pwd_vars(char *pwd, char *old_pwd, char **env)
{
	mod_var("OLDPWD", old_pwd, env);
	mod_var("PWD", pwd, env);
	free(pwd);
	free(old_pwd);
}

t_status	cmd_cd(char **args, char **env)
{
	char	*path;
	char	*old_pwd;
	char	*pwd;

	old_pwd = envvar("PWD", env);
	if (!old_pwd)
		return (ERROR);
	if (!args[1] || cmpstr(args[1], "~"))
		path = envvar("HOME", env);
	else if (cmpstr(args[1], "-"))
		path = envvar("OLDPWD", env);
	else
		path = ft_strdup(args[1]);
	if (chdir(path) == -1)
	{
		free(path);
		free(old_pwd);
		print_err("No such file or directory", args[1]);
		return (ERROR);
	}
	pwd = getcwd(NULL, 0);
	mod_pwd_vars(pwd, old_pwd, env);
	free(path);
	return (SUCCESS);
}
