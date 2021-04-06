/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:13:51 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/06 17:49:00 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int execute_command(t_command *command)
{
	char *argv[] = { "/bin/ls", "-la", ".", NULL };
	return execve(command->executable, argv, command->envp);
}
