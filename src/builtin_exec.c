/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarkoh <fsarkoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:06:16 by joel              #+#    #+#             */
/*   Updated: 2023/07/12 16:17:41 by fsarkoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_cmd(char *arg, char *cmd)
{
	return (!ft_strncmp(arg, cmd, ft_max(ft_strlen(arg), ft_strlen(cmd))));
}

t_status	exec_builtin(char **args, char **env)
{
	if (is_cmd(args[0], CMD_EXIT))
		return (cmd_exit());
	else if (is_cmd(args[0], CMD_ENV))
		return (cmd_env(env));
	else if (is_cmd(args[0], CMD_ECHO))
		return (cmd_echo(args));
	else if (is_cmd(args[0], CMD_PWD))
		return (cmd_pwd(env));
	else
		return (CMD_NOT_FOUND_STATUS);
}
