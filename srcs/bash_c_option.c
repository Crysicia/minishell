/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_c_option.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:44:22 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/01 18:29:31 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	check_bash_c_option(char *argv)
{
	if (!ft_strncmp(argv, "-c", 3))
		return (true);
	else
		return (false);
}

int	bash_c_option(char *argv)
{
	t_list	*input_list;
	int		ret;

	input_list = parser_loop(argv);
	if (!check_syntax_error(input_list))
	{
		ret = evaluation_pass(input_list);
		if (!ret)
			execute_all_the_commands(input_list);
		ft_lstclear(&input_list, free_block);
	}
	return (0);
}
