/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:29:42 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/12 10:37:39 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

char *bool_to_str(char *buffer, bool boolean)
{
	memset(buffer, 0, 6);
	if (boolean)
		strcpy(buffer, "true");
	else
		strcpy(buffer, "false");
	return buffer;
}
