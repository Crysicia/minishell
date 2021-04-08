/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finite_state_machine.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 03:07:23 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/08 03:07:23 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINITE_STATE_MACHINE_H
# define FINITE_STATE_MACHINE_H
# include "scanner.h" 

/*
** A Finite State Machine is an abstract machine that can be in one of a
** finite number of states at a given time. It can change transition from
** one state to a another in response to some input. 
*/

enum e_command
{
	error = -1,
	keyword = 0,
	option = 1,
	argument = 2,
	done = 3
};
enum e_command	command_state_transition(char character);
enum e_command	option_state_transition(char character);
enum e_command	scan_in_keyword_state(char *line);

#endif
