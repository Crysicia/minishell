/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:36:53 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/12 19:09:25 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_malloc_error(void)
{
	int		swap;
	char	*error;

	swap = errno;
	errno = ENOMEM;
	error = strerror(errno);
	printf("Malloc error %s_n", error);
	errno = swap;
}

int	parser_error(t_token *tok)
{
	ft_putstr_fd("Minishell : unexpected syntax error near `", STDERR_FILENO);
	ft_putstr_fd(tok->cmd, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (-1);
}

bool	check_first_node_cmd(t_simple_command *cmd)
{
	t_token	*tok;

	tok = cmd->words->content;
	if (tok && tok->role == operator)
	{
		parser_error(tok);
		return (true);
	}
	else
		return (false);
}

bool	check_syntax_error(t_list *list)
{
	t_list	*tmp;
	t_list	*pipeline_tmp;
	t_block	*block;

	tmp = list;
	while (tmp)
	{
		block = tmp->content;
		if ((block->id == simple_command)
			&& (check_first_node_cmd(block->kind.cmd)))
			return (true);
		else if (block->id == pipeline)
		{
			pipeline_tmp = block->kind.pipe->commands;
			while (pipeline_tmp)
			{
				if (check_first_node_cmd(pipeline_tmp->content))
					return (true);
				pipeline_tmp = pipeline_tmp->next;
			}
			return (false);
		}
		tmp = tmp->next;
	}
	return (false);
}
