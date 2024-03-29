/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <joel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:13:37 by joel              #+#    #+#             */
/*   Updated: 2023/11/30 17:28:33 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_iofile(t_iofile *iofile)
{
	free(iofile->path);
	free(iofile->limit_str);
	free(iofile);
}

void	free_iofilearr(t_iofile **iofiles)
{
	unsigned int	cidx;

	cidx = 0;
	while (iofiles[cidx])
	{
		free_iofile(iofiles[cidx]);
		cidx++;
	}
	free(iofiles);
}

t_iofile	*copy_iofile(t_iofile *iofile)
{
	t_iofile	*copy;

	copy = (t_iofile *)malloc(sizeof(t_iofile));
	if (!copy)
		return (NULL);
	copy->path = ft_strdup(iofile->path);
	copy->mode = iofile->mode;
	copy->limit_str = ft_strdup(iofile->path);
	return (copy);
}

char	*iofile_name(unsigned int idx)
{
	char	*c_idx;
	char	*join;

	c_idx = ft_itoa(idx);
	join = ft_strjoin("/tmp/.minishell_pipe_", c_idx);
	free(c_idx);
	return (join);
}
