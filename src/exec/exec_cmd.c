/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <joel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:19:31 by joel              #+#    #+#             */
/*   Updated: 2023/11/14 15:45:38 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_status	g_exit_status;

static void	exec_cmd(t_cmd *cmd, char ***env)
{
	if (!cmd->args[0])
		return ;
	setup_redirect_in(cmd);
	setup_redirect_out(cmd);
	if (!is_builtin(cmd->args[0]))
		g_exit_status = exec_program(cmd->args, *env);
	else
		g_exit_status = exec_builtin(cmd->args, env);
	if (g_exit_status == STATUS_CMD_NOT_FOUND)
		print_err("command not found: ", cmd->args[0]);
	reset_redirection(cmd);
}

void	exec_pipe(t_cmd **cmds, char ***env)
{
	unsigned int	cidx;

	cidx = 0;
	while (cmds[cidx])
	{
		exec_cmd(cmds[cidx], env);
		cidx++;
	}
}
