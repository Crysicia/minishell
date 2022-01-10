/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 08:53:01 by lpassera          #+#    #+#             */
/*   Updated: 2021/07/05 18:58:59 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_matrix(void **matrix, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		free(matrix[index]);
		matrix[index] = NULL;
		index++;
	}
	free(matrix);
	return (NULL);
}
