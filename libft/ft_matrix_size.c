/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 16:08:59 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/05 18:59:19 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_matrix_size(void **matrix)
{
	int	size;

	size = 0;
	while ((matrix + size) && *(matrix + size))
		size++;
	return (size);
}
