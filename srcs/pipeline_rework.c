/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_rework.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 09:25:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/06/20 09:25:29 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	execute_pipe_command(int pipe_fd[2], t_simple_command *commands)
{
	char	**arguments;
	t_list	*words;
	int		fork_ret;

	dprintf(2, "executing pipe command there hohoho\n");
	words = commands->words;
	arguments = command_format(words);
/*
	int		in_and_out[2];
	if (arguments)
	{
		save_in_and_out(&in_and_out);
		handle_redirections(commands->redirections);
		ft_run_builtin_or_cmd(arguments);
		restore_in_and_out(&in_and_out);
	}
*/
	int in_and_out[2];
	save_in_and_out(&in_and_out);
	if (find_exe_path(arguments[0]))
	{		
		fork_ret = fork();
		if (fork_ret == -1)
			display_error("while attempting to fork for pipeline", strerror(errno));
		else if (!fork_ret)
		{
			if (pipe_fd)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
			}
			if (commands->redirections)
			{
				dprintf(2, "redirection detected \n");
				handle_redirections(commands->redirections);
			}
			if (is_builtin(arguments[0]))
			{
				set_status_code(execute_builtin(arguments[0], &arguments[1]), true);
				exit(0);
			}
			else
			{
				char *path = find_exe_path(arguments[0]);
				if (!path)
					return (-1);
				execve(path, arguments, list_to_array(g_globals->env));
			}
		}
		else
		{
			if (pipe_fd)
				close(pipe_fd[1]);
			g_globals->current_pid = fork_ret;
			set_status_code(g_globals->status, false);
			g_globals->current_pid = 0;
			restore_in_and_out(&in_and_out);
		}
	}
	else
		printf("-Minishell: %s: command not found\n", arguments[0]);
	return (0);
}

void	*deallocate_pipe_tab(int **tab, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		close(tab[i][0]);
		close(tab[i][1]);
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

int	**allocate_pipe_tab(int	nb)
{
	int	i;
	int	**tab;

	if (nb > 255)
	{
		display_error("why don't you go fuck yourself", NULL);
		return (NULL);
	}
	tab = malloc(sizeof(int *) * (nb + 1));
	if (tab)
	{
		i = 0;
		while (i < nb)
		{
			tab[i] = malloc(sizeof(int) * 2);
			if (!tab[i])
				return (deallocate_pipe_tab(tab, i));
			i++;
		}
		tab[i] = NULL;
	}
	return (tab);
}

int	pipeline_big_loop(t_pipeline *pipeline)
{
	t_list				*scmd_list;
	int					index;
	int					**pipe_tab;
	int					in_and_out[2];

	save_in_and_out(&in_and_out);
	index = 0;
	pipe_tab = allocate_pipe_tab(pipeline->pipe_count - 1);
	if (!pipe_tab)
		ft_exit();
	scmd_list = pipeline->commands;
	while (scmd_list && scmd_list->next)
	{
		pipe(pipe_tab[index]);
		execute_pipe_command(pipe_tab[index], scmd_list->content);
		dup2(pipe_tab[index][0], STDIN_FILENO);
		scmd_list = scmd_list->next;
		index++;
	}
	dup2(in_and_out[0], STDOUT_FILENO);
	execute_single_command(scmd_list->content);
	wait_pipeline_end(pipeline->pipe_count - 1);
	deallocate_pipe_tab(pipe_tab, pipeline->pipe_count - 1);
	restore_in_and_out(&in_and_out);
	wait(NULL);
	return (0);
}

int	wait_pipeline_end(int pipe_count)
{
	int	ret;
	int	i;

	i = 0;
	while (i < pipe_count - 1)
	{
		ret = waitpid(-1, NULL, 0);
		if (ret == -1)
		{
			display_error("while waiting pipeline to end", strerror(errno));
			return (-1);
		}
		i++;
	}
	return (0);
}