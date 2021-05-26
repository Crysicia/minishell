/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:36:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/25 16:33:58 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "flag.h"

/* roadmap for quotes
 flagger to know if word is quoted 
 perform $expansion within double quotes and no quotes
 perform complex expqnsion within mixed quotes
 remove quotes
 eventually add the new words to the linked list
*/

/*
	Performing $expansion
	does it need to check if expansion can be done or is it already assumed ?
	strcpy() before after $var
	check var name (alphanumeric len, no \before)
	getenv(var)
	write in buffer (while adding \ to \ and "(why ?))

	remove quotes (now ?)
	remove antislash (now ?)
*/

void	dollar_expansion(t_token *tok)
{
	char	buffer[1024];
	char	*word_ptr;
	char	*buffer_ptr;

	if (tok->role == word && (!(tok->flag) || (tok->flag == DOUBLE_QUOTES)))
	{
		word_ptr = tok->cmd;
		ft_bzero(buffer, 1024);
		buffer_ptr = &buffer[0];
		while (*word_ptr)
		{
			if (*word_ptr == '\\')
				copy_escaped_character(&word_ptr, &buffer_ptr);
			else if (*word_ptr == '$')
				expand_env_variable(&word_ptr, &buffer_ptr);
			else
				*buffer_ptr++ = *word_ptr++;
		}
		free(tok->cmd);
		tok->cmd = ft_strdup(&buffer[0]);
	}
}
	/*	free(word_ptr); (makes cr segf)*/

char	*get_variable_name(char **str)
{
	char	*var_name;
	size_t	index;

	index = 1;
	while (*(*str + index) && ft_isalnum(*(*str + index)))
		index++;
	var_name = ft_strndup(*str + 1, index - 1);
	*str += index;
	return (var_name);
}

void	expand_exit_status(char **str, char **buffer)
{
	char	*exit_status;

	exit_status = ft_itoa((unsigned char)g_globals->status);
	ft_strlcpy(*buffer, exit_status, ft_strlen(exit_status) + 1);
	*str += 1;
	free(exit_status);
	exit_status = NULL;
}

void	expand_env_variable(char **str, char **buffer)
{
	t_dict	*env_var;
	char	*name;

	name = get_variable_name(str);
	if (name && *name)
	{
		env_var = ft_getenv(name);
		if (env_var)
		{
			ft_strlcpy(*buffer, env_var->value, ft_strlen(env_var->value) + 1);
			*buffer += ft_strlen(env_var->value);
		}
		free(name);
		name = NULL;
	}
	else if (**str == '?')
		expand_exit_status(str, buffer);
}

void	copy_escaped_character(char **str, char **buffer)
{
	**buffer = *(*str + 1);
	*buffer += 1;
	*str += 2;
}
