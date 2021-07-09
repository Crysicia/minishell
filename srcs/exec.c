/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:13:51 by lpassera          #+#    #+#             */
/*   Updated: 2021/07/09 14:36:49 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	set_status_code(int code, bool from_builtin)
{
	if (from_builtin)
		return (g_globals->status = code);
	g_globals->status = WEXITSTATUS(code);
	return (g_globals->status);
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

int	execute_single_command(t_simple_command *commands)
{
	char	**arguments;
	t_list	words;
	int		in_and_out[2];
	char	*path;

	words = *commands->words;
	arguments = command_format(&words);
	if (!arguments)
		return (2);
	save_in_and_out(&in_and_out);
	path = find_exe_path(arguments[0]);
	if (handle_redirections(commands->redirections))
		return (1);
	if (is_builtin(arguments[0]))
		set_status_code(execute_builtin(arguments[0], &arguments[1]),
			true);
	else if (path)
	{
		free(path);
		execute_command(arguments);
	}
	else
		display_error(arguments[0], "command not found");
	restore_in_and_out(&in_and_out);
	ft_free_matrix((void **)arguments, ft_matrix_size((void **)arguments));
	return (0);
}

int	execute_command(char **command)
{
	int		pid;
	char	*path;

	pid = fork();
	if (pid < 0)
		display_error("Error", "Could not fork child process");
	else if (pid == 0)
	{
		path = find_exe_path(command[0]);
		if (!path)
			return (-1);
		execve(path, command, list_to_array(g_globals->env));
	}
	else
	{
		g_globals->current_pid = pid;
		wait(&g_globals->status);
		set_status_code(g_globals->status, false);
		g_globals->current_pid = 0;
	}
	return (-2);
}
