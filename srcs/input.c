/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 20:31:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/19 15:53:08 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include <stdbool.h>

void	print_token_list(t_list *list)
{
	t_token	*token;

	while (list)
	{
		token = list->content;
		printf("(cmd: [%s], Role: [%d])", token->cmd, token->role);
		if (list->next)
			printf(" -> ");
		list = list->next;
	}
	printf("\n");
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
