/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_states.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 03:27:46 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/08 03:27:46 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/finite_state_machine.h"

/*
	Tests
	echo bonjour
	"    "
	
*/
enum e_command	keyword_state_transition(char character)
{
	enum e_command	state;

	if (!character
		|| is_control_operator(character))
		state = done;
	else if (is_space(character))
		state = option;
	else
		state = error;
	return (state);
}

enum e_command	option_state_transition(char character)
{
	enum e_command	state;

	if (!character
		|| is_control_operator(character))
		state = done;
	else if (is_space(character))
		state = argument;
	else
		state = error;
	return (state);
}

enum e_command	scan_in_keyword_state(char *line)
{
	int				index;
	enum e_command	state;

	index = 0;
	while (line[index]
		&& is_space(line[index]))
		index++;
	if (is_control_operator(line[index]) == true)
		return (-1);
	while (line[index]
		&& ft_is_lowercase(line[index]))
		index++;
	state = keyword_state_transition(line[index]);
	return (state);
}
