/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parraylen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <joel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:10:35 by fsarkoh           #+#    #+#             */
/*   Updated: 2023/11/13 20:05:23 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	parraylen(char **array)
{
	unsigned int	cidx;

	cidx = 0;
	while (array[cidx])
		cidx++;
	return (cidx);
}
