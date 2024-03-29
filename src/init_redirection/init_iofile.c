/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_iofile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <joel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:00:12 by joel              #+#    #+#             */
/*   Updated: 2023/10/13 15:41:21 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path(char **args, t_iomode mode)
{
	if (!args[1])
		return (ft_strdup(""));
	if (mode == HEREDOC_MODE)
		return (ft_strdup(HEREDOC_PATH));
	return (ft_strdup(args[1]));
}

char	*limit_str(char **args, t_iomode mode)
{
	if (!args[1])
		return (ft_strdup(""));
	if (mode == HEREDOC_MODE)
		return (ft_strdup(args[1]));
	return (ft_strdup(""));
}

t_iomode	mode(char **args)
{
	if (cmpstr(args[0], ">"))
		return (OUTPUT_MODE);
	else if (cmpstr(args[0], ">>"))
		return (APPEND_MODE);
	else if (cmpstr(args[0], "<"))
		return (INPUT_MODE);
	else
		return (HEREDOC_MODE);
}

t_iofile	*init_iofile(char **args)
{
	t_iofile	*iofile;

	iofile = (t_iofile *)malloc(sizeof(t_iofile));
	if (!iofile)
		return (NULL);
	iofile->mode = mode(args);
	iofile->path = path(args, iofile->mode);
	iofile->limit_str = limit_str(args, iofile->mode);
	return (iofile);
}
