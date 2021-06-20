/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_c_option.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:44:22 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/26 16:16:33 by lpassera         ###   ########.fr       */
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

void	execute_all_the_commands(t_list *list)
{
	t_list		*tmp;
	t_block		*ptr;
	int			ret;

	ret = 0;
	tmp = list;
	while (tmp && (ret != -1))
	{
		ptr = tmp->content;
		if ((ptr->id == simple_command) || (ptr->id == only_redirections))
			ret = execute_single_command(ptr->kind.cmd);
		else if (ptr->id == pipeline)
			ret = pipeline_big_loop(ptr->kind.pipe);
		tmp = tmp->next;
	}
}
