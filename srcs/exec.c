/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:13:51 by lpassera          #+#    #+#             */
/*   Updated: 2021/07/28 17:05:25 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	set_status_code(int code, bool from_builtin)
{
	if (from_builtin)
		return (g_globals->status = code);
	if (WIFEXITED(code))
		g_globals->status = WEXITSTATUS(code);
	if (WIFSIGNALED(code))
	{
		g_globals->status = WTERMSIG(code);
		if (g_globals->status != 131)
			g_globals->status += 131;
	}
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
		if (ptr->id == simple_command || ptr->id == only_redirections)
			ret = execute_single_command(ptr->kind.cmd);
		else if (ptr->id == pipeline)
			ret = pipeline_big_loop(ptr->kind.pipe);
		tmp = tmp->next;
	}
}

char	**prepare_command_and_do_redirections(t_simple_command *commands)
{
	t_list	*words;
	char	**arguments;
	int		res;

	arguments = NULL;
	look_for_heredoc(commands->redirections);
	res = handle_redirections(commands->redirections);
	words = commands->words;
	if (!res && words)
	{
		if (words)
			arguments = command_format(words);
		if (!arguments)
			return (NULL);
		res = apply_all_redirections(commands->redirections);
		if (!res)
			return (arguments);
		else
			ft_free_matrix((void **)arguments,
				ft_matrix_size((void **)arguments));
	}
	return (NULL);
}

int	execute_single_command(t_simple_command *commands)
{
	char	**arguments;
	int		in_and_out[2];
	char	*path;

	save_in_and_out(&in_and_out);
	arguments = prepare_command_and_do_redirections(commands);
	if (!arguments)
	{
		restore_in_and_out(&in_and_out);
		return (close_all_fds(commands->redirections));
	}
	path = find_exe_path(arguments[0]);
	if (is_builtin(arguments[0]))
		set_status_code(execute_builtin(arguments[0], &arguments[1]), true);
	else if (path)
	{
		free(path);
		path = NULL;
		execute_command(arguments);
	}
	else
	{
		display_error(arguments[0], "command not found");
		set_status_code(127, true);
	}
	restore_in_and_out(&in_and_out);
	free(path);
	ft_free_matrix((void **)arguments, ft_matrix_size((void **)arguments));
	return (0);
}

void	add_pid_to_global(int pid)
{
	int	i;
	int	j;
	int	*tmp;

	i = 0;
	j = 0;
	while (g_globals->pids && g_globals->pids[i])
		i++;
	tmp = malloc(sizeof(int) * (i + 2));
	if (!tmp)
		ft_malloc_error();
	while (j < i)
	{
		tmp[j] = g_globals->pids[j];
		j++;
	}
	tmp[j] = pid;
	tmp[j + 1] = 0;
	free(g_globals->pids);
	g_globals->pids = tmp;
}

void	reset_pids_from_global(void)
{
	free(g_globals->pids);
	g_globals->pids = malloc(sizeof(int));
	if (!g_globals->pids)
		ft_malloc_error();
	g_globals->pids[0] = 0;
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
		exit(1);
	}
	else
	{
		add_pid_to_global(pid);
		wait(&g_globals->status);
		set_status_code(g_globals->status, false);
		reset_pids_from_global();
	}
	return (-2);
}
