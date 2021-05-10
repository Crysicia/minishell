/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 20:31:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/10 17:19:41 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include <stdbool.h>

void	print_simple_command_node(t_list *list)
{
	t_simple_command	*command;
	t_list				*node;
	t_token				*tmp;
	t_redirection		*tmp2;

	command = list->content;
	puts("printing words list");
	node = command->words;
	while (node)
	{
		tmp = node->content;
		printf("[%s]---", tmp->cmd);
		node = node->next;
	}
	puts("\nprinting redirection list");
	node = command->redirections;
	while (node)
	{
		tmp2 = node->content;
		printf("[%s] [%s]--", tmp2->operator->cmd, tmp2->file->cmd);
		node = node->next;
	}
	printf("\n");
}

void	print_command_list(t_list *list)
{
	t_list				*node;
	t_simple_command	*command;
	int					i;

	node = list;
	i = 0;
	while (node)
	{
		printf("\nNODE [%d]\n", i++);
		command = list->content;
		if (command->type == simple_command)
			print_simple_command_node(node);
		node = node->next;
	}
}

bool	gnl_loop_function(char *line)
{
	int		ret;
	char	*swap;
	char	*tmp;

	ret = 0;
	while (ret == 0)
	{
		ret = get_next_line(0, &tmp);
		swap = gnl_join(line, tmp);
		free(line);
		free(tmp);
		line = swap;
	}
	return (true);
}

char	*get_command(void)
{
	char	*line;
	int		ret;

	line = ft_calloc(512, 1);
	ret = get_next_line(0, &line);
	if (ret == -1 || line == NULL)
	{
		puts("gnl error");
		exit(-1);
	}
	else if (!ft_strlen(line))
	{
		write(1, "\n", 1);
		exit (0);
	}
	else if (ret == 0)
		gnl_loop_function(line);
	return (line);
}

void	skip_spaces(char **line)
{
	while (line && *line && (**line == ' ' || **line == '\t'))
		*line += 1;
}
