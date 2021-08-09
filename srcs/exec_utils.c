/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 20:05:27 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/09 13:08:08 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	save_in_and_out(int (*saved)[])
{
	ft_bzero(*saved, 2 * sizeof(int));
	(*saved)[0] = dup(STDOUT_FILENO);
	if ((*saved)[0] == -1)
		return (false);
	dprintf(2, "dup for stdout %d\n", (*saved)[0]);
	(*saved)[1] = dup(STDIN_FILENO);
	dprintf(2, "dup for stdin %d\n", (*saved)[1]);
	if ((*saved)[1] == -1)
	{
		close((*saved)[0]);
		return (false);
	}
	return (true);
}

bool	restore_in_and_out(int (*saved)[])
{
	bool	ret;

	ret = true;
	if (dup2((*saved)[0], STDOUT_FILENO) == -1
			|| dup2((*saved)[1], STDIN_FILENO) == -1)
		ret = false;
//	int	close_wr
	close((*saved)[0]);
	close((*saved)[1]);
	return (ret);
}
