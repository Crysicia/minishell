/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 20:31:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/15 15:40:15 by lpassera         ###   ########.fr       */
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

void	get_command(char *envp[])
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
	lexer(line, envp);
}

int	lexer(char *line, char *envp[])
{
	t_command	command;

	command.executable = NULL;
	command.args = NULL;
	command.envp = envp;
	if (line == NULL)
	{
		printf("lexer error : line is NULL at line %d of %s\n",
			__LINE__, __FILE__);
		return (-1);
	}
	printf("valid line is [%s]\n", line);
	print_token_list(command_parse(line));
	command.args = ft_split(line, ' ');
	execute_command(&command);
	return (0);
}

void	skip_spaces(char **line)
{
	while (line && *line && (**line == ' ' || **line == '\t'))
		*line += 1;
}
