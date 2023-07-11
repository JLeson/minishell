/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <joel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:56:40 by joel              #+#    #+#             */
/*   Updated: 2023/07/11 14:31:34 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	n_args(char	**args)
{
	unsigned int	n;

	n = 0;
	while (args[n])
		n++;
	return (n);
}

static char	*get_var_name(char *arg)
{
	char			*var_name;
	unsigned int	cidx;

	var_name = (char *)malloc(ft_strlen(arg) * sizeof(char));
	if (!var_name)
		return (NULL);
	cidx = 0;
	while (arg[cidx] && arg[cidx] != '\"')
	{
		var_name[cidx] = arg[cidx];
		cidx++;
	}
	var_name[cidx] = '\0';
	return (var_name);
}

static char	*expand_arg(char *arg, char **env)
{
	char	*expanded;
	char	*var_name;

	if (arg[0] == '$')
		expanded = env_var(arg + 1, env);
	else if (arg[0] == '\"' && arg[1] == '$')
	{
		var_name = get_var_name(arg + 2);
		expanded = env_var(var_name, env);
		free(var_name);
	}
	else
		expanded = ft_strdup(arg);
	return (expanded);
}

char	**expand_args(char **args, char **env, t_status status)
{
	char			**expanded;
	unsigned int	cidx;

	expanded = (char **)malloc((n_args(args) + 1) * sizeof(char *));
	if (!expanded)
		return (NULL);
	cidx = 0;
	while (args[cidx])
	{
		if (!ft_strncmp(args[cidx], "$?", 2))
			expanded[cidx] = ft_itoa((int) status);
		else if (!ft_strncmp(args[cidx], "\"$?\"", 4))
			expanded[cidx] = ft_itoa((int) status);
		else
			expanded[cidx] = expand_arg(args[cidx], env);
		cidx++;
	}
	expanded[cidx] = NULL;
	return (expanded);
}
