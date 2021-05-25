/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:17:41 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/24 12:16:03 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# define PIPE_READ 0
# define PIPE_WRITE 1
# define IN_PIPELINE 0
# define FIRST_IN_PIPELINE 1
# define LAST_IN_PIPELINE 2
# define NOT_IN_PIPELINE 4

typedef struct s_pipes {
	int			previous[2];
	int			current[2];
}				t_pipes;

void	close_pipes(t_pipes *pipes);
void	dup_pipes(t_pipes *pipes, int command_flag);
void	close_relevant_pipes(t_pipes *pipes, int command_flag);
void	swap_pipes(t_pipes *pipes);
bool	create_pipes(t_pipes *pipes);
int		get_pipeline_placement(int current, int total);
int		execute_pipeline(t_pipeline *pipeline);
int		execute_pipeline_loop(t_pipes *pipes, t_list *commands, int pipe_count);
int		execute_pipe(t_simple_command *command,
			t_pipes *pipes, int command_flag);
#endif